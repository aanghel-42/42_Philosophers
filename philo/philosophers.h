/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 18:49:55 by aanghel           #+#    #+#             */
/*   Updated: 2022/07/11 21:55:39 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define BLU "\x1b[34m"
# define CLOSE_COLOR "\x1b[0m"

typedef struct s_info
{
	int				stop;
	int				time_to_eat;
	int				time_to_die;
	int				philo_finish;
	int				time_to_sleep;
	int				number_of_philo;
	int				time_to_eat_philo;
	long int		start_time;
	pthread_mutex_t	dead;
	pthread_mutex_t	write;
	pthread_mutex_t	finish;
	pthread_mutex_t	time_eat;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				finish;
	long int		ms_eat;
	unsigned int	nb_eat;
	t_info			*info;
	pthread_t		thread_id;
	pthread_t		thread_id_death;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	left_fork;
}	t_philo;

typedef struct s_p
{
	t_info	info;
	t_philo	*philo;
}	t_p;

// utils.h
int				ft_atoi(const char *str);
void			ft_write(char *str, t_philo *p);
void			ft_usleep(long int time_in_ms);
size_t			ft_strlen(const char *s);
long int		ft_time(void);

// parsing.h
int				ft_parsing(int argc, char **argv, t_p *p);
int				ft_take_info(int argc, char **argv, t_p *p);

// threads.h
int				ft_initialize(t_p *p);
int				ft_thread(t_p *p);
void			ft_mutex_init(t_p *p);
void			*ft_routine(void *data);
void			*ft_is_dead(void *data);

// activity.c
int				ft_check_death(t_philo *p, int i);
void			ft_sleep_and_think(t_philo *p);
void			ft_start_activity(t_philo *p);

//philo.c
int				ft_check_death2(t_p *p);
void			ft_close(t_p *p);
void			ft_close(t_p *p);
#endif