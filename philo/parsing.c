/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:07:12 by aanghel           #+#    #+#             */
/*   Updated: 2022/07/12 00:13:58 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* prese informazioni sui tempi da argv */

int	ft_take_info(int argc, char **argv, t_p *p)
{
	if (argc == 5 || argc == 6)
	{
		p->info.number_of_philo = ft_atoi(argv[1]);
		p->info.time_to_die = ft_atoi(argv[2]);
		p->info.time_to_eat = ft_atoi(argv[3]);
		p->info.time_to_sleep = ft_atoi(argv[4]);
		p->info.time_to_eat_philo = -1;
		if (argc == 6)
			p->info.time_to_eat_philo = ft_atoi(argv[5]);
		if (p->info.time_to_die <= 0 || p->info.time_to_eat <= 0 \
		|| p->info.time_to_sleep <= 0 || p->info.number_of_philo <= 0)
			return (0);
		return (1);
	}
	return (0);
}

/* controllo sul argv, che siano solo numeri */

int	ft_parsing(int argc, char **argv, t_p *p)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9' || \
				ft_strlen(&argv[i][j]) > 10)
				return (0);
			j++;
		}
		i++;
	}
	if (ft_take_info(argc, argv, p) == 0)
		return (0);
	return (1);
}
