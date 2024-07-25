/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmuller <flmuller@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:11:36 by flmuller          #+#    #+#             */
/*   Updated: 2024/07/25 11:17:07 by flmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		res = res * 10 + nptr[i++] - '0';
	return (res * sign);
}

long int	conv_time(struct timeval time)
{
	long int	res;

	res = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (res);
}

void	free_all(t_table *spaghetti)
{
	int	i;

	i = 0;
	while (i < spaghetti->nb_philo)
	{
		pthread_mutex_destroy(&spaghetti->forks[i]);
		pthread_mutex_destroy(&spaghetti->philos[i].check_modif);
		i++;
	}
	pthread_mutex_destroy(&spaghetti->check_finish);
	pthread_mutex_destroy(&spaghetti->print);
	free(spaghetti->forks);
	free(spaghetti->philos);
}

void	printlock(t_philo *philo, int code, long int start_time)
{
	struct timeval	time;

	pthread_mutex_lock(philo->print);
	gettimeofday(&time, NULL);
	if (code == 0)
		printf("%ld %d is thinking\n",
			conv_time(time) - start_time, philo->index);
	if (code == 1)
		printf("%ld %d has taken a fork\n",
			conv_time(time) - start_time, philo->index);
	if (code == 2)
		printf("%ld %d is eating\n",
			conv_time(time) - start_time, philo->index);
	if (code == 3)
		printf("%ld %d is sleeping\n",
			conv_time(time) - start_time, philo->index);
	if (code == 4)
		printf("%ld %d has finish to eat\n",
			conv_time(time) - start_time, philo->index);
	if (code == 5)
		printf("%ld %d died\n", conv_time(time) - start_time, philo->index);
	pthread_mutex_unlock(philo->print);
}

void	unlockfork(t_philo *philo)
{
	/* if (philo->index % 2 == 0)
	{ */
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	/* } */
/* 	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	} */
}
