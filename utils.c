/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:11:19 by kethouve          #+#    #+#             */
/*   Updated: 2024/04/12 15:33:16 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		free(philo[i]);
		i++;
	}
	free(philo);
}

int	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("time error");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < ms)
		usleep(ms / 10);
	return (0);
}

long long int	ft_atoi(const char *nptr)
{
	int				i;
	long long int	result;
	long long int	valeur;
	int				count;

	i = 0;
	valeur = 1;
	result = 0;
	count = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	while (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			valeur = -1;
		i++;
		count++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9' && count < 2)
	{
		result = result * 10 + nptr[i] - 48;
		i++;
	}
	return (result * valeur);
}
