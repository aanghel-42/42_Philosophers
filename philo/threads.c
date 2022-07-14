/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:17:33 by aanghel           #+#    #+#             */
/*   Updated: 2022/07/14 17:19:22 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* inizializza i mutex */

void	ft_mutex_init(t_p *p)
{
	pthread_mutex_init(&p->info.write, NULL);
	pthread_mutex_init(&p->info.dead, NULL);
	pthread_mutex_init(&p->info.finish, NULL);
	pthread_mutex_init(&p->info.time_eat, NULL);
}

/* inizializza le funzioni e richiama inizializzazione dei mutex */

int	ft_initialize(t_p *p)
{
	int		i;

	i = 0;
	p->info.start_time = ft_time();
	p->info.philo_finish = 0;
	p->info.stop = 0;
	ft_mutex_init(p);
	while (i < p->info.number_of_philo)
	{
		p->philo[i].id = i + 1;
		p->philo->ms_eat = p->info.start_time;
		p->philo->nb_eat = 0;
		p->philo->finish = 0;
		p->philo[i].right_fork = NULL;
		pthread_mutex_init(&p->philo[i].left_fork, NULL);
		if (p->info.number_of_philo == 1)
			return (1);
		if (i == p->info.number_of_philo - 1)
			p->philo[i].right_fork = &p->philo[0].left_fork;
		else
			p->philo[i].right_fork = &p->philo[i + 1].left_fork;
		i++;
	}
	return (1);
}

//funzione per il controllo se ci sono stati morti
void	*ft_is_dead(void *data)
{
	t_philo	*p;

	p = (t_philo *)data;
	ft_usleep(p->info->time_to_die);
	pthread_mutex_lock(&p->info->time_eat);
	pthread_mutex_lock(&p->info->finish);
	if (!ft_check_death(p, 0) && !p->finish \
		&& ((ft_time() - p->ms_eat) >= (long)(p->info->time_to_die)))
	{
		pthread_mutex_unlock(&p->info->time_eat);
		pthread_mutex_unlock(&p->info->finish);
		pthread_mutex_lock(&p->info->write);
		ft_write(RED "died" CLOSE_COLOR, p);
		ft_check_death(p, 1);
		exit(0);
	}
	pthread_mutex_unlock(&p->info->time_eat);
	pthread_mutex_unlock(&p->info->finish);
	return (NULL);
}

// funzione di routine per i tread

void	*ft_routine(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	if (ph->id % 2 == 0)
		ft_usleep(ph->info->time_to_eat / 10);
	while (!ft_check_death(ph, 0))
	{
		pthread_create(&ph->thread_id_death, NULL, ft_is_dead, data);
		ft_start_activity(ph);
		pthread_detach(ph->thread_id_death);
		if ((int)++ph->nb_eat == ph->info->time_to_eat_philo)
		{
			pthread_mutex_lock(&ph->info->finish);
			ph->finish = 1;
			ph->info->philo_finish++;
			if (ph->info->philo_finish == ph->info->number_of_philo)
			{
				pthread_mutex_unlock(&ph->info->finish);
				ft_check_death(ph, 2);
			}
			pthread_mutex_unlock(&ph->info->finish);
			return (NULL);
		}
	}
	return (NULL);
}

// creazione dei thread

int	ft_thread(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->info.number_of_philo)
	{
		p->philo[i].info = &p->info;
		if (pthread_create(&p->philo[i].thread_id, NULL, \
			ft_routine, &p->philo[i]) != 0)
		{
			printf("Error: Problem with pthread creation\n");
			return (0);
		}
		i++;
	}
	return (1);
}
