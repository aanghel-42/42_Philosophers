/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:55:28 by aanghel           #+#    #+#             */
/*   Updated: 2022/07/11 20:32:51 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* ft_atoi semplificato rispetto a Libft, non fa nessun tipo di controllo */

int	ft_atoi(const char *str)
{
	int	i;
	int	r;

	i = 0;
	while ((str[i]) == ' ')
		i++;
	r = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	return (r);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

// funzione che acquisisce il time attuale 

long int	ft_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
	{
		printf(RED "Gettimeofday returned -1\n" CLOSE_COLOR);
		exit(0);
	}
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_write(char *str, t_philo *p)
{
	long int	time;

	time = 0;
	time = ft_time() - p->info->start_time;
	if (time >= 0 && time <= 2147483647 && !ft_check_death(p, 0))
		printf(GREEN "[%ld] " CLOSE_COLOR " Philo %d %s\n", time, p->id, str);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = ft_time();
	while ((ft_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}
