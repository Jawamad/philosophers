/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmuller <flmuller@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:07:59 by flmuller          #+#    #+#             */
/*   Updated: 2024/07/29 13:03:59 by flmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	init_philo(int argc, char **argv, t_philo *philo)
{
	if (!ft_atoi(argv[2]) || !ft_atoi(argv[3]) || !ft_atoi(argv[4]))
	{
		ft_error(2);
		return (0);
	}
	philo->nb_must_eat = -1;
	if (argc == 6)
	{
		if (ft_atoi(argv[5]))
			philo->nb_must_eat = ft_atoi(argv[5]);
		else
		{
			ft_error(3);
			return (0);
		}
	}
	init_phil_carac(argv, philo);
	return (1);
}

void	init_phil_carac(char **argv, t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	philo->t_to_die = ft_atoi(argv[2]);
	philo->t_to_eat = ft_atoi(argv[3]);
	philo->t_to_sleep = ft_atoi(argv[4]);
	philo->last_eating_time = conv_time(time);
	philo->nb_eat = 0;
	philo->has_finish = 0;
	pthread_mutex_init(&philo->check_modif, NULL);
}

int	init_spaghetti(int argc, char **argv, t_table *spaghetti)
{
	struct timeval	time;

	if (!ft_atoi(argv[1]))
		return (0);
	spaghetti->nb_philo = ft_atoi(argv[1]);
	spaghetti->forks = malloc(sizeof(pthread_mutex_t)
			* (spaghetti->nb_philo + 1));
	if (!spaghetti->forks)
		return (0);
	if (!init_fork(spaghetti))
		return (0);
	spaghetti->philos = malloc(sizeof(t_philo) * (spaghetti->nb_philo + 1));
	if (!spaghetti->philos)
		return (0);
	pthread_mutex_init(&spaghetti->print, NULL);
	if (!init_sit(argc, argv, spaghetti))
		return (0);
	pthread_mutex_init(&spaghetti->check_finish, NULL);
	spaghetti->finish = 0;
	gettimeofday(&time, NULL);
	spaghetti->start_time = conv_time(time);
	spaghetti->death = 0;
	return (1);
}

int	init_sit(int argc, char **argv, t_table *spaghetti)
{
	int	i;
	int	nb_philo;

	i = 0;
	while (i < spaghetti->nb_philo)
	{
		nb_philo = spaghetti->nb_philo;
		if (!init_philo(argc, argv, &spaghetti->philos[i]))
			return (0);
		spaghetti->philos[i].print = &spaghetti->print;
		spaghetti->philos[i].right_fork = &spaghetti->forks[i];
		if (i == 0)
			spaghetti->philos[i].left_fork = &spaghetti->forks[nb_philo - 1];
		else
			spaghetti->philos[i].left_fork = &spaghetti->forks[i - 1];
		spaghetti->philos[i].index = i + 1;
		spaghetti->philos[i].spaghetti = spaghetti;
		i++;
	}
	return (1);
}

int	init_fork(t_table *spaghetti)
{
	int	i;

	i = 0;
	while (i < spaghetti->nb_philo)
	{
		if (pthread_mutex_init(&spaghetti->forks[i], NULL))
		{
			ft_error(4);
			return (0);
		}
		i++;
	}
	return (1);
}
