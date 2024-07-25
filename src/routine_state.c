/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmuller <flmuller@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:22:46 by flmuller          #+#    #+#             */
/*   Updated: 2024/07/25 13:47:58 by flmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	pickup_forks(t_philo *philo, t_table *spaghetti)
{
	int	nbphilo;

	pthread_mutex_lock(&spaghetti->check_finish);
	nbphilo = spaghetti->nb_philo;
	printlock(philo, 0, spaghetti->start_time);
	pthread_mutex_unlock(&spaghetti->check_finish);
	lockfirstfork(philo);
	if (checkup_death(spaghetti))
	{
		if (philo->index % 2 == 0)
			pthread_mutex_unlock(philo->right_fork);
		else
			pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	pthread_mutex_lock(&spaghetti->check_finish);
	printlock(philo, 1, spaghetti->start_time);
	pthread_mutex_unlock(&spaghetti->check_finish);
	if (nbphilo == 1)
		ft_usleep((philo->t_to_die));
	if (!locksecfork(philo, spaghetti))
		return(0);
	return (1);
}

int	eat(t_philo *philo, t_table *spaghetti)
{
	struct timeval	time;

	if (checkup_death(spaghetti))
	{
		unlockfork(philo);
		return (0);
	}
	pthread_mutex_lock(&spaghetti->check_finish);
	printlock(philo, 1, spaghetti->start_time);
	pthread_mutex_unlock(&spaghetti->check_finish);
	pthread_mutex_lock(&philo->check_modif);
	gettimeofday(&time, NULL);
	philo->last_eating_time = conv_time(time);
	pthread_mutex_unlock(&philo->check_modif);
	pthread_mutex_lock(&spaghetti->check_finish);
	printlock(philo, 2, spaghetti->start_time);
	pthread_mutex_unlock(&spaghetti->check_finish);
	ft_usleep(philo->t_to_eat);
	pthread_mutex_lock(&philo->check_modif);
	philo->nb_eat++;
	if (philo->nb_eat == philo->nb_must_eat)
		philo->has_finish = 1;
	pthread_mutex_unlock(&philo->check_modif);
	unlockfork(philo);
	return (1);
}

int	ph_sleep(t_philo *philo, long int start_time, t_table *spaghetti)
{
	pthread_mutex_lock(&spaghetti->check_finish);
	if (spaghetti->death)
	{
		pthread_mutex_unlock(&spaghetti->check_finish);
		return (0);
	}
	printlock(philo, 3, start_time);
	pthread_mutex_unlock(&spaghetti->check_finish);
	ft_usleep(philo->t_to_sleep);
	return (1);
}

void	lockfirstfork(t_philo *philo)
{
	if (philo->index % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
}

int	locksecfork(t_philo *philo, t_table *spaghetti)
{

	if (checkup_death(spaghetti))
	{
		if (philo->index % 2 == 0)
			pthread_mutex_unlock(philo->right_fork);
		else
			pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	if (philo->index % 2 == 0)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	return (1);
}
