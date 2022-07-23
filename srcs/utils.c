/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:30:38 by hyap              #+#    #+#             */
/*   Updated: 2022/07/23 16:25:08 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	ft_atoi(char *s)
{
	long long	num;

	num = 0;
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			num = (num * 10) + (*s - '0');
		s++;
	}
	return (num);
}

unsigned long long	calc_ms(t_timeval tv)
{
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

unsigned long long	calc_us(int ms)
{
	return ((unsigned long long)ms * 1000);
}

void	good_sleep(int ms)
{
	unsigned long long	time_enter;
	int					diff;
	t_timeval			tv;

	gettimeofday(&tv, NULL);
	time_enter = calc_ms(tv);
	diff = 0;
	while (diff < ms)
	{
		gettimeofday(&tv, NULL);
		diff = calc_ms(tv) - time_enter;
		usleep(50);
	}
}

unsigned long long	get_time()
{
	t_timeval	tv;

	gettimeofday(&tv, NULL);
	return calc_ms(tv);
}
