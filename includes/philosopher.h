/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:38:04 by lmarecha          #+#    #+#             */
/*   Updated: 2022/06/07 09:48:10 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_philosopher {
	int			id;
	int			lfork_id;
	int			rfork_id;
	long long	last_meal;
} t_philosopher;

typedef struct s_args {
	int				nb_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_must_eat;
	int				died;
	int				all_ate;
	t_philosopher	*philosophers;
} t_args;

typedef struct mutex_data {
	t_list	*philosophers;
	t_args	arguments;
	pthread_mutex_t	mutex;
} mutex_data;
