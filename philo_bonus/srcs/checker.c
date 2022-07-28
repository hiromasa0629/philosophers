/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:43:49 by hyap              #+#    #+#             */
/*   Updated: 2022/07/27 16:51:52 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	finish_checker(t_table *table, int i, int *all_ate)
{
	unsigned long long	diff;

	sem_wait(table->dead_sem);
	diff = get_time() - table->philos[i].last_meal;
	if ((int)diff > table->die_time)
	{
		table->has_dead = 1;
		sem_post(table->dead_sem);
		print_all(&table->philos[i], STATUS_DEAD);
		return (1);
	}
	if (table->specified)
		if (table->philos[i].ate_num < table->eat_min)
			*all_ate = 0;
	sem_post(table->dead_sem);
	return (0);
}

void	*checker(void *t)
{
	t_table				*table;
	int					i;
	int					all_ate;

	table = (t_table *)t;
	while (table->count > 1)
	{
		i = 0;
		all_ate = 0;
		if (table->specified)
			all_ate = 1;
		while (i < table->count)
		{
			if (finish_checker(table, i++, &all_ate))
			{
				sem_post(table->dead_sem);
				return (NULL);
			}
		}
		if (all_ate)
			break ;
	}
	return (NULL);
}
