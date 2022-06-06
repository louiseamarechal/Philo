/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:38:04 by lmarecha          #+#    #+#             */
/*   Updated: 2022/06/06 17:34:20 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NB_OF_PHILOSOPHERS 3

typedef struct s_philosopher {
	int	philosopher_nb;
	int	fork_nb;
} t_philosopher;

typedef struct s_args {
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
} t_args;

typedef struct mutex_data {
	t_list	*philosophers;
	t_args	arguments;
	pthread_mutex_t	mutex;
} mutex_data;
