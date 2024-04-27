/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:01:29 by kethouve          #+#    #+#             */
/*   Updated: 2024/04/19 15:56:47 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_data
{
	int				n_philo;
	int				t_life;
	int				t_eat;
	int				t_sleep;
	int				objective;
	int				death_flag;
	pthread_mutex_t	access;
	pthread_mutex_t	death;
	pthread_mutex_t	write;
}	t_data;

typedef struct s_philo
{
	pthread_t		th;
	int				th_nbr;
	int				start;
	int				last_meal;
	int				n_meal;
	pthread_mutex_t	fork_l;
	pthread_mutex_t	*fork_r;
	t_data			*data;
}	t_philo;

int				main(int argc, char **argv);
long long int	ft_atoi(const char *nptr);
int				ft_usleep(size_t ms);
int				get_current_time(void);
void			free_all(t_philo **philo, t_data *data);
void			eat_time(t_philo *philo);
void			sleep_time(t_philo *philo);
int				death_check(t_philo *philo, t_data *data);
int				death_in_sleep(t_philo *philo);
int				death_meal2(t_philo *philo, t_data *data);
void			*routine(void *arg);
void			*routine_one(void *arg);
void			print_msg(t_philo *philo, char *s);

#endif