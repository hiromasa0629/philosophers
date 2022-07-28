/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:46:18 by hyap              #+#    #+#             */
/*   Updated: 2022/07/25 17:51:16 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	routine_loop(t_philo *philo)
{
	pthread_mutex_lock(&philo->left->mutex);
	if (end_routine_loop(philo))
		return ;
	print_all(philo, STATUS_TAKEN_FORK);
	if (lonely_philo(philo))
		return ;
	pthread_mutex_lock(&philo->right->mutex);
	if (end_routine_loop(philo))
		return ;
	print_all(philo, STATUS_TAKEN_FORK);
	routine_eat(philo);
	if (end_routine_loop(philo))
		return ;
	print_all(philo, STATUS_SLEEPING);
	good_sleep(philo->table->sleep_time);
	if (end_routine_loop(philo))
		return ;
	print_all(philo, STATUS_THINKING);
}

void	routine_runner_shoes(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->dead_mutex);
	routine_loop(philo);
	pthread_mutex_lock(&philo->table->dead_mutex);
}

void	routine_runner(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->table->specified)
	{
		pthread_mutex_lock(&philo->table->dead_mutex);
		while (!philo->table->has_dead && i++ < philo->table->eat_min)
		{
			routine_runner_shoes(philo);
			if (philo->table->count == 1)
				break ;
		}
	}
	else if (!philo->table->specified)
	{
		pthread_mutex_lock(&philo->table->dead_mutex);
		while (!philo->table->has_dead)
		{
			routine_runner_shoes(philo);
			if (philo->table->count == 1)
				break ;
		}
	}
	pthread_mutex_unlock(&philo->table->dead_mutex);
}

void	*routine(void *ph)
{
	t_philo		*philo;
	int			i;

	philo = (t_philo *)ph;
	i = 0;
	if ((philo->numth + 1) % 2 == 0)
		usleep(15000);
	routine_runner(philo);
	return (NULL);
}
