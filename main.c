/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:00:54 by kethouve          #+#    #+#             */
/*   Updated: 2024/04/15 15:30:43 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, char **argv, int argc)
{
	data->n_philo = ft_atoi(argv[1]);
	data->t_life = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->access, NULL);
	if (argc == 6)
		data->objective = ft_atoi(argv[5]);
	else
		data->objective = -1;
	data->death_flag = 0;
}

void	thread_creat(t_philo **philo)
{
	int	i;

	i = 0;
	while (i < philo[0]->data->n_philo)
	{
		if (i == 0)
			philo[i]->fork_r = &philo[philo[0]->data->n_philo - 1]->fork_l;
		else
			philo[i]->fork_r = &philo[i - 1]->fork_l;
		if (philo[0]->data->n_philo < 2
			&& pthread_create(&philo[i]->th, NULL, &routine_one, philo[i]))
			return ;
		else if (philo[0]->data->n_philo > 1
			&& pthread_create(&philo[i]->th, NULL, &routine, philo[i]))
			return ;
		i++;
	}
	i = 0;
	while (i < philo[0]->data->n_philo)
	{
		if (pthread_join(philo[i]->th, NULL))
			return ;
		i++;
	}
}

void	init_philo(t_data *data)
{
	t_philo	**philo;
	int		i;

	i = 0;
	philo = malloc((data->n_philo) * sizeof(t_philo *));
	while (i < data->n_philo)
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->data = data;
		philo[i]->n_meal = 0;
		philo[i]->th_nbr = i + 1;
		philo[i]->start = get_current_time();
		pthread_mutex_init(&philo[i]->fork_l, NULL);
		i++;
	}
	thread_creat(philo);
	free_all(philo, data);
	exit(0);
}

int	verif_arg(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) > 2147483647 || ft_atoi(argv[i]) < 1)
			return (1);
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (printf("Number of arguments incorrect\n"), 1);
	if (verif_arg(argv) == 1)
	{
		printf("Arguments must be numbers: numbers of philosophers, ");
		printf("time to die, time to eat, time to sleep, ");
		return (printf("optionnal: number each philosophers need to eat\n"), 1);
	}
	init_data(&data, argv, argc);
	init_philo(&data);
	return (0);
}
