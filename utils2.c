/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:32:20 by kethouve          #+#    #+#             */
/*   Updated: 2024/04/19 15:59:28 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_philo *philo, char *s)
{
	int	time;

	time = get_current_time() - philo->start;
	pthread_mutex_lock(&philo->data->write);
	printf("[%d] philo %d %s", time, philo->th_nbr, s);
	pthread_mutex_unlock(&philo->data->write);
}

int	death_meal2(t_philo *philo, t_data *data)
{
	long long int	n;
	long long int	n2;

	n = philo->start - philo->last_meal;
	n2 = get_current_time() - philo->last_meal;
	if (philo->n_meal >= 1
		&& (get_current_time() - philo->last_meal >= data->t_life
			|| n + (data->t_eat * 2) > data->t_life))
	{
		ft_usleep(data->t_life - n2);
		if (data->death_flag == 1)
			return (1);
		data->death_flag = 1;
		pthread_mutex_lock(&philo->data->death);
		ft_usleep(1);
		print_msg(philo, "is dead          \U0001F480\n");
		pthread_mutex_unlock(&philo->data->death);
		return (1);
	}
	return (0);
}

int	death_check(t_philo *philo, t_data *data)
{
	long long int	n;

	n = get_current_time() - philo->last_meal;
	if ((n >= data->t_life || n + data->t_eat >= n + data->t_life))
	{
		ft_usleep(data->t_life);
		if (data->death_flag == 1)
			return (1);
		data->death_flag = 1;
		pthread_mutex_lock(&philo->data->death);
		ft_usleep(1);
		print_msg(philo, "is dead          \U0001F480\n");
		pthread_mutex_unlock(&philo->data->death);
		return (1);
	}
	return (0);
}

int	death_in_sleep(t_philo *philo)
{
	long long int	n;

	n = get_current_time() - philo->last_meal;
	if (n >= philo->data->t_life
		|| n + philo->data->t_sleep >= philo->data->t_life)
	{
		pthread_mutex_lock(&philo->data->access);
		if (philo->data->death_flag == 1)
		{
			pthread_mutex_unlock(&philo->data->access);
			return (1);
		}
		philo->data->death_flag = 1;
		pthread_mutex_unlock(&philo->data->access);
		ft_usleep(philo->data->t_life - n);
		pthread_mutex_lock(&philo->data->death);
		ft_usleep(1);
		print_msg(philo, "is dead 	       \U0001F480\n");
		pthread_mutex_unlock(&philo->data->death);
		return (1);
	}
	return (0);
}
