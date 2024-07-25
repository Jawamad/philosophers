/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmuller <flmuller@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:18:19 by flmuller          #+#    #+#             */
/*   Updated: 2024/07/25 09:36:40 by flmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		id;
	int				index;
	int				nb_eat;
	long int		t_to_die;
	long int		t_to_eat;
	long int		t_to_sleep;
	int				nb_must_eat;
	long int		last_eating_time;
	int				has_finish;
	pthread_mutex_t	check_modif;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*print;
	struct s_table	*spaghetti;
}	t_philo;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_t		monitor;
	pthread_mutex_t	check_finish;
	pthread_mutex_t	print;
	int				finish;
	int				death;
	int				nb_philo;
	long int		start_time;
}	t_table;

/* init.c */
int			init_philo(int argc, char **argv, t_philo *philo);
int			init_spaghetti(int argc, char **argv, t_table *spaghetti);
int			init_sit(int argc, char **argv, t_table *spaghetti);
int			init_fork(t_table *spaghetti);
void		init_phil_carac(char **argv, t_philo *philo);

/* error.c */
void		ft_error(int code);

/* routine_state.c */

int			pickup_forks(t_philo *philo, t_table *spaghetti);
int			eat(t_philo *philo, t_table *spaghetti);
int			ph_sleep(t_philo *philo, long int start_time, t_table *spaghetti);
void		lockfirstfork(t_philo *philo);
int			locksecfork(t_philo *philo, t_table *spaghetti);

/* utils.c */
int			ft_atoi(const char *nptr);
long int	conv_time(struct timeval time);
void		free_all(t_table *spaghetti);
void		printlock(t_philo *philo, int code, long int start_time);
void		unlockfork(t_philo *philo);
/* launch.c */

void		start_thread(t_table *spaghetti);
void		*routine(void *param);
void		*monitor(void *param);
int			classic_routine(t_table *spaghetti, t_philo *currphilo);

/* checker.c */
int			check_finish(t_table *spaghetti);
int			check_death(t_philo *philo);
int			checkup_death(t_table *spaghetti);
void		ft_usleep(long int time_in_ms);
long int	actual_time(void);

#endif