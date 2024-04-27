/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:15:24 by kethouve          #+#    #+#             */
/*   Updated: 2024/04/19 14:08:29 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_one(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	philo->last_meal = philo->start;
	print_msg(philo, "is thinking      \U0001F914\n");
	pthread_mutex_lock(&philo->fork_l);
	print_msg(philo, "has taken a fork \U0001F374\n");
	pthread_mutex_unlock(&philo->fork_l);
	ft_usleep(philo->data->t_life);
	print_msg(philo, "is dead     \U0001F480\n");
	return (NULL);
}

void	eat_time(t_philo *philo)
{
	if (philo->th_nbr < philo->data->n_philo)
	{
		pthread_mutex_lock(&philo->fork_l);
		print_msg(philo, "has taken a fork \U0001F374\n");
		pthread_mutex_lock(philo->fork_r);
		print_msg(philo, "has taken a fork \U0001F374\n");
		print_msg(philo, "is eating        \U0001F35D\n");
		philo->last_meal = get_current_time();
		ft_usleep(philo->data->t_eat);
		pthread_mutex_unlock(&philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
	}
	else
	{
		pthread_mutex_lock(philo->fork_r);
		print_msg(philo, "has taken a fork \U0001F374\n");
		pthread_mutex_lock(&philo->fork_l);
		print_msg(philo, "has taken a fork \U0001F374\n");
		print_msg(philo, "is eating        \U0001F35D\n");
		philo->last_meal = get_current_time();
		ft_usleep(philo->data->t_eat);
		pthread_mutex_unlock(philo->fork_r);
		pthread_mutex_unlock(&philo->fork_l);
	}
	philo->n_meal++;
}

void	sleep_time(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->access);
	print_msg(philo, "is sleeping      \U0001F634\n");
	ft_usleep(philo->data->t_sleep);
}

int	routine_next(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->access);
	if (philo->data->death_flag == 1)
	{
		pthread_mutex_unlock(&philo->data->access);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->access);
	if (death_in_sleep(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->data->access);
	if (philo->data->death_flag == 1)
	{
		pthread_mutex_unlock(&philo->data->access);
		return (1);
	}
	sleep_time(philo);
	pthread_mutex_lock(&philo->data->access);
	if (philo->data->death_flag == 1)
	{
		pthread_mutex_unlock(&philo->data->access);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->access);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	philo->last_meal = philo->start;
	if (philo->th_nbr % 2 == 0 || philo->th_nbr == philo->data->n_philo)
		ft_usleep(10);
	while (1)
	{
		print_msg(philo, "is thinking      \U0001F914\n");
		pthread_mutex_lock(&philo->data->access);
		if (death_check(philo, philo->data) == 1
			|| death_meal2(philo, philo->data) == 1)
		{
			pthread_mutex_unlock(&philo->data->access);
			break ;
		}
		pthread_mutex_unlock(&philo->data->access);
		eat_time(philo);
		if (philo->n_meal == philo->data->objective)
			break ;
		if (routine_next(philo) == 1)
			break ;
	}
	return (NULL);
}
