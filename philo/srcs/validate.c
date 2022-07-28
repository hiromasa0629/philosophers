/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:27:41 by hyap              #+#    #+#             */
/*   Updated: 2022/07/19 14:45:30 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	validate_av(char **av)
{
	int		index;
	char	*s;
	int		is_error;

	index = 1;
	is_error = 0;
	while (av[index])
	{
		s = av[index];
		while (*s)
		{
			if (!(*s >= '0' && *s <= '9'))
			{
				is_error = 1;
				break ;
			}
			s++;
		}
		if (is_error == 1)
			break ;
		index++;
	}
	return (is_error == 0);
}

int	validate(int ac, char **av)
{
	int	is_error;

	is_error = 0;
	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./philo [number_of_philosophers] \
[time_to_die] [time_to_eat] [time_to_sleep] \
<number_of_times_each_philosopher_must_eat>");
		is_error = 1;
	}
	if (!validate_av(av))
	{
		printf("Invalid arguments");
		is_error = 1;
	}
	return (is_error == 0);
}
