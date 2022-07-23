;/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:46:18 by hyap              #+#    #+#             */
/*   Updated: 2022/07/23 16:28:05 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	lonely_philo(t_philo *philo)
{
	while (philo->table->count == 1)
	{
		if ((int)get_time() - (int)philo->table->start_time > philo->table->die_time)
		{
			print_all(philo, STATUS_DEAD);
			return (1);
		}
	}
	return (0);
}

void	routine_loop(t_philo *philo)
{
	// printf("%llu wtf is going on\n", get_time() - philo->table->start_time);
	pthread_mutex_lock(&philo->left->mutex);
	pthread_mutex_lock(&philo->table->dead_mutex);
	if (philo->table->has_dead)
	{
		pthread_mutex_unlock(&philo->table->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->table->dead_mutex);
	// printf("%llu did you take the left fork !!!\n", get_time() - philo->table->start_time);
	print_all(philo, STATUS_TAKEN_FORK);
	if (lonely_philo(philo))
		return ;
	pthread_mutex_lock(&philo->right->mutex);
	print_all(philo, STATUS_TAKEN_FORK);
	pthread_mutex_lock(&philo->table->dead_mutex);
	print_all(philo, STATUS_EATING);
	philo->last_meal = get_time();
	philo->ate_num++;
	pthread_mutex_unlock(&philo->table->dead_mutex);
	good_sleep(philo->table->eat_time);
	pthread_mutex_unlock(&philo->left->mutex);
	pthread_mutex_unlock(&philo->right->mutex);
	pthread_mutex_lock(&philo->table->dead_mutex);
	if (philo->table->has_dead)
	{
		pthread_mutex_unlock(&philo->table->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->table->dead_mutex);
	print_all(philo, STATUS_SLEEPING);
	good_sleep(philo->table->sleep_time);
	print_all(philo, STATUS_THINKING);
}

void	*routine(void *ph)
{
	t_philo		*philo;
	int					i;

	philo = (t_philo *)ph;
	i = 0;
	if ((philo->numth + 1) % 2 == 0)
		usleep(15000);
	if (philo->table->specified)
	{
		// printf("%llu philo[%d]\n", get_time() - philo->table->start_time, philo->numth);
		pthread_mutex_lock(&philo->table->dead_mutex);
		// printf("%llu philo[%d] ...\n",get_time() - philo->table->start_time, philo->numth);
		while (!philo->table->has_dead && i++ < philo->table->eat_min)
		{	
			// printf("%llu philo[%d] in loop ...\n", get_time() - philo->table->start_time, philo->numth);
			pthread_mutex_unlock(&philo->table->dead_mutex);
			// printf("%llu philo[%d] in loop unlocked ...\n", get_time() - philo->table->start_time, philo->numth);
			routine_loop(philo);
			pthread_mutex_lock(&philo->table->dead_mutex);
			if (philo->table->count == 1)
				break ;
		}
	}
	else if (!philo->table->specified)
	{
		pthread_mutex_lock(&philo->table->dead_mutex);
		while (!philo->table->has_dead)
		{
			pthread_mutex_unlock(&philo->table->dead_mutex);
			routine_loop(philo);
			pthread_mutex_lock(&philo->table->dead_mutex);
		}
	}
	pthread_mutex_unlock(&philo->table->dead_mutex);
	return (NULL);
}

void	*checker(void *t)
{
	t_table				*table;
	unsigned long long	diff;
	int					i;
	int					all_ate;

	table = (t_table *)t;
	while (table->count > 1)
	{
		i = 0;
		all_ate = 1;
		while (i < table->count)
		{
			pthread_mutex_lock(&table->dead_mutex);
			diff = (get_time() - table->start_time) - table->philos[i].last_meal;
			if ((int)diff > table->die_time)
			{
				table->has_dead = 1;
				print_all(&table->philos[i], STATUS_DEAD);
				pthread_mutex_unlock(&table->dead_mutex);
				return (NULL);
			}
			if (table->philos[i].ate_num < table->eat_min)
				all_ate = 0;
			pthread_mutex_unlock(&table->dead_mutex);
			i++;
		}
		if (all_ate)
			break ;
	}
	return (NULL);
}
