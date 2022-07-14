/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:02:37 by aanghel           #+#    #+#             */
/*   Updated: 2022/07/14 17:08:59 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_check_death2(t_p *p)
{
	pthread_mutex_lock(&p->info.dead);
	if (p->info.stop)
	{
		pthread_mutex_unlock(&p->info.dead);
		return (1);
	}
	pthread_mutex_unlock(&p->info.dead);
	return (0);
}

void	ft_close(t_p *p)
{
	int	i;

	i = -1;
	if (!ft_check_death2(p))
		ft_usleep(1);
	while (++i < p->info.number_of_philo)
		pthread_join(p->philo[i].thread_id, NULL);
	pthread_mutex_destroy(&p->info.write);
	i = -1;
	while (++i < p->info.number_of_philo)
		pthread_mutex_destroy(&p->philo[i].left_fork);
	if (p->info.stop == 2)
		printf("Each philosopher ate %d time(s)\n", p->info.time_to_eat_philo);
	free(p->philo);
}

int	main(int argc, char **argv)
{
	t_p	p;

	if (!ft_parsing(argc, argv, &p))
	{
		printf(RED "Error: Invalid Arguments\n" CLOSE_COLOR);
		return (0);
	}
	p.philo = malloc(sizeof(t_philo) * p.info.number_of_philo);
	if (!p.philo)
		return (0);
	if (!ft_initialize(&p) || !ft_thread(&p))
	{
		free(p.philo);
		return (0);
	}
	ft_close(&p);
	return (0);
}
