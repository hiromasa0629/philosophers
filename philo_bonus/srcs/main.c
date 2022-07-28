/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:23:25 by hyap              #+#    #+#             */
/*   Updated: 2022/07/27 17:03:22 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_semaphores(t_table *table)
{
	table->forks_sem = sem_open("/forks", O_CREAT | O_EXCL, 0664, table->count);
	if (table->forks_sem == SEM_FAILED)
	{
		sem_unlink("/forks");
		table->forks_sem = sem_open("/forks", O_CREAT, 0664, table->count);
	}
	table->print_sem = sem_open("/print", O_CREAT | O_EXCL, 0664, 1);
	if (table->print_sem == SEM_FAILED)
	{
		sem_unlink("/print");
		table->print_sem = sem_open("/print", O_CREAT, 0664, 1);
	}
	table->dead_sem = sem_open("/dead", O_CREAT | O_EXCL, 0664, 1);
	if (table->dead_sem == SEM_FAILED)
	{
		sem_unlink("/dead");
		table->dead_sem = sem_open("/dead", O_CREAT, 0664, 1);
	}
}

void	init_philo(t_table *table, int i)
{
	table->philos[i].numth = i;
	table->philos[i].ate_num = 1;
	table->philos[i].table = table;
	table->philos[i].is_started = 0;
	table->philos[i].last_meal = get_time();
	table->philos[i].is_dead = 0;
}

void	init_threads(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = get_time();
	while (i < table->count)
	{
		init_philo(table, i);
		pthread_create(&table->philos[i].tid, NULL, &routine, \
			(void *)&table->philos[i]);
		i++;
	}
	pthread_create(&table->checker_tid, NULL, &checker, (void *)table);
	i = 0;
	while (i < table->count)
		pthread_join(table->philos[i++].tid, NULL);
	pthread_join(table->checker_tid, NULL);
}

void	init_table(t_table *table, char **av, int count, int ac)
{
	table->count = count;
	table->die_time = ft_atoi(av[2]);
	table->eat_time = ft_atoi(av[3]);
	table->sleep_time = ft_atoi(av[4]);
	table->specified = 0;
	if (ac == 6)
	{
		table->specified = 1;
		table->eat_min = ft_atoi(av[5]);
	}
	table->has_dead = 0;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->count);
	init_semaphores(table);
	init_threads(table);
}

int	main(int ac, char **av)
{
	t_table		table;
	long long	num;

	if (!validate(ac, av))
		return (1);
	num = ft_atoi(av[1]);
	if (num > __INT_MAX__ || num < -__INT_MAX__ - 1 || num == 0)
		return (0);
	init_table(&table, av, (int)num, ac);
	return (0);
}
