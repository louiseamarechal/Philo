/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:38:04 by lmarecha          #+#    #+#             */
/*   Updated: 2022/06/30 14:29:28 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_philosopher {
	int				id;
	int				nb_meal;
	int				left_fork;
	int				right_fork;
	struct s_args	*args;
	long long		started_meal;
	pthread_t		thread_id;
}	t_philosopher;

typedef struct s_args {
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				number_must_eat;
	int				died;
	int				all_ate;
	long long int	start_simu;
	t_philosopher	philosophers[200];
	pthread_mutex_t	global_block;
	pthread_mutex_t	forks[200];
}	t_args;

// src
int				initialize(t_args *args, char **argv, int argc);
int				executor(t_args *args);

// utils
int				ft_atoi(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
void			kill_everything(t_args *args);
int				is_dead(t_args *args);
int				is_full(t_args *args);
void			death_condition(t_args *args, t_philosopher philosopher, int i);
void			all_ate_checker(t_args *args, t_philosopher *philo);

// timestamp
long long int	get_time(void);
void			sleep_mode(t_args *args, long long time_to);
void			print_state(t_args *args, int philo_id, char *state);
// long long int	diff_time_in_msec(long long int t1, long long int t2);
#endif
