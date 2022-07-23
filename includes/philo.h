/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:18:42 by hyap              #+#    #+#             */
/*   Updated: 2022/07/23 18:27:36 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# define STATUS_THINKING 0
# define STATUS_EATING 1
# define STATUS_SLEEPING 2
# define STATUS_DEAD 3
# define STATUS_TAKEN_FORK 4
# define BLUE "\033[0;34m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define CYAN "\033[0;36m"
# define PURPLE "\033[0;35m"

typedef struct timeval	t_timeval;
typedef struct s_table  t_table;
typedef struct s_fork	t_fork;

typedef struct s_philo {
	t_fork				*left;
	t_fork				*right;
	pthread_mutex_t		started_mutex;
	pthread_mutex_t		eat_mutex;
	int					is_started;
	int					ate_num;
	int					is_dead;
	int					numth;
	unsigned long long	last_meal;
	unsigned long long	start_time;
	pthread_t			tid;
	pthread_t			checker_tid;
	t_table				*table;
}				t_philo;

typedef struct s_fork {
	pthread_mutex_t	mutex;
	int				id;
}				t_fork;

typedef struct s_table {
	pthread_t			checker_tid;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		eating_mutex;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		start_mutex;
	int					is_started;
	int					count;
	int					has_dead;
	t_philo				*philos;
	t_fork				*forks;
	int					specified;
	int					eat_min;
	int					die_time;
	int					eat_time;
	unsigned long long	start_time;
	int					sleep_time;
}				t_table;

void				*routine(void *ph);
void				*checker(void *t);
int					validate(int ac, char **av);
long long			ft_atoi(char *s);
unsigned long long	calc_ms(t_timeval tv);
unsigned long long	calc_us(int ms);
void				good_sleep(int ms);
int					is_dead(t_philo *ph);
unsigned long long	get_time();
void				print_all(t_philo *ph, int status);

#endif
