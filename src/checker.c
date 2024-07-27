/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmuller <flmuller@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 08:57:00 by flmuller          #+#    #+#             */
/*   Updated: 2024/07/28 00:14:48 by flmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	check_death(t_philo *philo)
{
	long int		diff;
	struct timeval	time;
	int				res;

	res = 0;
	pthread_mutex_lock(&philo->check_modif);
	gettimeofday(&time, NULL);
	diff = conv_time(time) - philo->last_eating_time;
	if (philo->t_to_die < diff && !philo->has_finish)
		res = 1;
	pthread_mutex_unlock(&philo->check_modif);
	return (res);
}

int	check_finish(t_table *spaghetti)
{
	int	i;

	i = 0 ;
	while (i < spaghetti->nb_philo)
	{
		pthread_mutex_lock(&spaghetti->philos[i].check_modif);
		if (!spaghetti->philos[i].has_finish)
		{
			pthread_mutex_unlock(&spaghetti->philos[i].check_modif);
			return (0);
		}
		pthread_mutex_unlock(&spaghetti->philos[i].check_modif);
		i++;
	}
	return (1);
}

int	checkup_death(t_table *spaghetti)
{
	int	res;

	pthread_mutex_lock(&spaghetti->check_finish);
	res = spaghetti->death;
	pthread_mutex_unlock(&spaghetti->check_finish);
	return (res);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

long int	actual_time(void)
{
	long int		time;
	struct timeval	current_time;

	time = 0;
	gettimeofday(&current_time, NULL);
	time = ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
	return (time);
}
