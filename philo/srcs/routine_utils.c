/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:49:41 by hyap              #+#    #+#             */
/*   Updated: 2022/07/25 17:52:14 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	lonely_philo(t_philo *philo)
{
	int	ms;

	while (philo->table->count == 1)
	{
		ms = (int)get_time() - (int)philo->table->start_time;
		if (ms > philo->table->die_time)
		{
			print_all(philo, STATUS_DEAD);
			return (1);
		}
	}
	return (0);
}

int	end_routine_loop(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dead_mutex);
	if (philo->table->has_dead)
	{
		pthread_mutex_unlock(&philo->table->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->dead_mutex);
	return (0);
}

void	routine_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dead_mutex);
	print_all(philo, STATUS_EATING);
	philo->last_meal = get_time();
	philo->ate_num++;
	pthread_mutex_unlock(&philo->table->dead_mutex);
	good_sleep(philo->table->eat_time);
	pthread_mutex_unlock(&philo->left->mutex);
	pthread_mutex_unlock(&philo->right->mutex);
}
