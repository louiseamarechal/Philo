/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:38:04 by lmarecha          #+#    #+#             */
/*   Updated: 2022/06/24 12:13:57 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_philosopher {
	int				id;
	int				nb_meal; // to keep track of the nb of meal of a philo (args optionnel)
	int				left_fork;
	int				right_fork;
	struct s_args	*args;
	long long		started_meal;
	pthread_t		thread_id; // un thread par philo, pour executer la fonction
} t_philosopher;

typedef struct s_args {
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				number_must_eat;
	int				died;
	int				all_ate; // pour checker si tous les philo ont manger (args optionnel)
	long long int	first_timestamp;
	t_philosopher	philosophers[200];
	pthread_mutex_t	print_philo_state;
	pthread_mutex_t	forks[200]; // une fourchette par philo
} t_args;

// src
int	initialize(t_args *args, char **argv, int argc);
int	executor(t_args *args);

// utils
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
void	sleep_mode(t_args *args, long long time_to);
void	print_state(t_args *args, int philo_id, char *state);
long long int	timestamp(void);

// typedef struct s_mutex_data {
	// 	t_list	*philosophers;
	// 	t_args	arguments;
	// 	pthread_mutex_t	mutex;
	// } t_mutex_data;
