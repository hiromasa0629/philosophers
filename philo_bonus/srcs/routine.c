/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:46:18 by hyap              #+#    #+#             */
/*   Updated: 2022/08/25 14:46:59 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	routine_loop(t_philo *philo)
{
	sem_wait(philo->table->forks_sem);
	print_all(philo, STATUS_TAKEN_FORK);
	if (lonely_philo(philo))
		return ;
	sem_wait(philo->table->forks_sem);
	print_all(philo, STATUS_TAKEN_FORK);
	routine_eat(philo);
	print_all(philo, STATUS_SLEEPING);
	good_sleep(philo->table->sleep_time, philo);
	print_all(philo, STATUS_THINKING);
}

void	routine_runner(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->table->specified)
	{
		while (!philo->table->has_dead && i++ < philo->table->eat_min)
		{
			routine_loop(philo);
			if (philo->table->count == 1)
				break ;
		}
	}
	else if (!philo->table->specified)
	{
		while (!philo->table->has_dead)
		{
			routine_loop(philo);
			if (philo->table->count == 1)
				break ;
		}
	}
}

void	*exit_thread(void *t)
{
	t_table	*table;

	table = (t_table *)t;
	sem_wait(table->dead_sem);
	sem_post(table->dead_sem);
	sem_post(table->finish_sem);
	exit(1);
	return (NULL);
}

void	*checker_thread(void *ph)
{
	unsigned long long	diff;
	t_philo				*philo;

	philo = (t_philo *)ph;
	while (1)
	{
		diff = get_time() - philo->last_meal;
		if ((int)diff > philo->table->die_time && \
			philo->ate_num < philo->table->eat_min)
		{
			print_all(philo, STATUS_DEAD);
			sem_post(philo->table->dead_sem);
			exit(1);
		}
		if (philo->ate_num > philo->table->eat_min)
		{
			sem_post(philo->table->finish_sem);
			break ;
		}
	}
	return (NULL);
}

void	*routine(void *ph)
{
	t_philo		*philo;
	int			i;
	pthread_t	tid;
	pthread_t	tid2;

	philo = (t_philo *)ph;
	i = 0;
	if ((philo->numth + 1) % 2 == 0)
		usleep(15000);
	pthread_create(&tid2, NULL, &checker_thread, philo);
	pthread_create(&tid, NULL, &exit_thread, philo->table);
	routine_runner(philo);
	pthread_join(tid, NULL);
	pthread_join(tid2, NULL);
	return (NULL);
}
