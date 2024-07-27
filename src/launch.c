/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmuller <flmuller@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:17:55 by flmuller          #+#    #+#             */
/*   Updated: 2024/07/28 00:15:13 by flmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	start_thread(t_table *spaghetti)
{
	int	i;

	i = 0;
	while (i < spaghetti->nb_philo)
	{
		pthread_create(&spaghetti->philos[i].id,
			NULL, routine, &spaghetti->philos[i]);
		i++;
	}
	pthread_create(&spaghetti->monitor, NULL, monitor, spaghetti);
	i = 0;
	while (i < spaghetti->nb_philo)
	{
		pthread_join(spaghetti->philos[i].id, NULL);
		i++;
	}
	pthread_join(spaghetti->monitor, NULL);
	free_all(spaghetti);
}

void	*routine(void *param)
{
	t_philo	*currphilo;
	t_table	*spaghetti;
	int		philofinish;

	philofinish = 0;
	currphilo = (t_philo *) param;
	spaghetti = currphilo->spaghetti;
	while (!philofinish && !checkup_death(spaghetti))
	{
		if (!classic_routine(spaghetti, currphilo))
			return (NULL);
		pthread_mutex_lock(&currphilo->check_modif);
		philofinish = currphilo->has_finish;
		pthread_mutex_unlock(&currphilo->check_modif);
		if (philofinish)
			printlock(currphilo, 4);
		if (!philofinish)
			ph_sleep(currphilo, spaghetti);
	}
	return (NULL);
}

void	*monitor(void *param)
{
	t_table	*spaghetti;
	int		i;
	int		check_meal;

	i = 0;
	spaghetti = (t_table *) param;
	check_meal = 0;
	while (!check_meal && !checkup_death(spaghetti))
	{
		pthread_mutex_lock(&spaghetti->check_finish);
		spaghetti->finish = check_finish(spaghetti);
		check_meal = spaghetti->finish;
		spaghetti->death = check_death(&spaghetti->philos[i]);
		pthread_mutex_unlock(&spaghetti->check_finish);
		if (checkup_death(spaghetti))
			printlock(&spaghetti->philos[i], 5);
		i++;
		if (i == spaghetti->nb_philo)
			i = 0;
		ft_usleep(1);
	}
	return (NULL);
}

int	classic_routine(t_table *spaghetti, t_philo *currphilo)
{
	if (checkup_death(spaghetti))
		return (0);
	if (!pickup_forks(currphilo, spaghetti))
		return (0);
	if (checkup_death(spaghetti))
	{
		unlockfork(currphilo);
		return (0);
	}
	if (!eat(currphilo, spaghetti) || checkup_death(spaghetti))
		return (0);
	return (1);
}
