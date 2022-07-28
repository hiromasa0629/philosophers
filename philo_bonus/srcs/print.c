/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 13:00:33 by hyap              #+#    #+#             */
/*   Updated: 2022/07/27 16:56:56 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_all(t_philo *ph, int status)
{
	unsigned long long	ms;

	sem_wait(ph->table->print_sem);
	ms = get_time() - ph->table->start_time;
	if (status == STATUS_THINKING)
		printf("%s%llu philo[%d] is thinking\n", BLUE, ms, ph->numth);
	if (status == STATUS_EATING)
		printf("%s%llu philo[%d] is eating (%d/%d)\n", \
			GREEN, ms, ph->numth, ph->ate_num, ph->table->eat_min);
	if (status == STATUS_SLEEPING)
		printf("%s%llu philo[%d] is sleeping\n", CYAN, ms, ph->numth);
	if (status == STATUS_TAKEN_FORK)
		printf("%s%llu philo[%d] has taken a fork\n", PURPLE, ms, ph->numth);
	if (status == STATUS_DEAD)
		printf("%s%llu philo[%d] died\n", RED, ms, ph->numth);
	sem_post(ph->table->print_sem);
}
