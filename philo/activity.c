/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:44:19 by aanghel           #+#    #+#             */
/*   Updated: 2022/07/14 17:15:08 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// funzione che fa un controllo e nel caso imposta lo stop

int	ft_check_death(t_philo *p, int i)
{
	pthread_mutex_lock(&p->info->dead);
	if (i)
		p->info->stop = i;
	if (p->info->stop)
	{
		pthread_mutex_unlock(&p->info->dead);
		return (1);
	}
	pthread_mutex_unlock(&p->info->dead);
	return (0);
}

// funzione che gestisce il dormire e il pensare

void	ft_sleep_and_think(t_philo *p)
{
	pthread_mutex_lock(&p->info->write);
	ft_write(BLU "is sleeping" CLOSE_COLOR, p);
	pthread_mutex_unlock(&p->info->write);
	ft_usleep(p->info->time_to_sleep);
	pthread_mutex_lock(&p->info->write);
	ft_write(BLU "is thinking" CLOSE_COLOR, p);
	pthread_mutex_unlock(&p->info->write);
}

// funzione che inizia le varie attività che deve svolgere il filosofo
// mangiare, dormire e pensare

void	ft_start_activity(t_philo *p)
{
	pthread_mutex_lock(&p->left_fork);
	pthread_mutex_lock(&p->info->write);
	ft_write(BLU "has taken a fork" CLOSE_COLOR, p);
	pthread_mutex_unlock(&p->info->write);
	if (!p->right_fork)
	{
		ft_usleep(p->info->time_to_die * 2);
		pthread_mutex_unlock(&p->left_fork);
		return ;
	}
	pthread_mutex_lock(p->right_fork);
	pthread_mutex_lock(&p->info->write);
	ft_write(BLU "has taken a fork" CLOSE_COLOR, p);
	pthread_mutex_unlock(&p->info->write);
	pthread_mutex_lock(&p->info->write);
	ft_write(GREEN "is eating" CLOSE_COLOR, p);
	pthread_mutex_lock(&p->info->time_eat);
	p->ms_eat = ft_time();
	pthread_mutex_unlock(&p->info->time_eat);
	pthread_mutex_unlock(&p->info->write);
	ft_usleep(p->info->time_to_eat);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(&p->left_fork);
	ft_sleep_and_think(p);
}
