/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:49:41 by hyap              #+#    #+#             */
/*   Updated: 2022/07/27 17:03:53 by hyap             ###   ########.fr       */
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
	sem_wait(philo->table->dead_sem);
	if (philo->table->has_dead)
	{
		sem_post(philo->table->dead_sem);
		return (1);
	}
	sem_post(philo->table->dead_sem);
	return (0);
}

void	routine_eat(t_philo *philo)
{
	sem_wait(philo->table->dead_sem);
	print_all(philo, STATUS_EATING);
	philo->last_meal = get_time();
	philo->ate_num++;
	sem_post(philo->table->dead_sem);
	good_sleep(philo->table->eat_time);
	sem_post(philo->table->forks_sem);
	sem_post(philo->table->forks_sem);
}
