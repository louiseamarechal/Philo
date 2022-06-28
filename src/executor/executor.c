/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:32:49 by lmarecha          #+#    #+#             */
/*   Updated: 2022/06/28 16:41:36 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	philosopher_eats(t_args *args, int id)
{
	if (args->all_ate == 1 || args->died == 1)
		return ;
	if (id % 2 == 0)
	{
		pthread_mutex_lock(&args->forks[args->philosophers[id].right_fork]);
		print_state(args, id, "has taken a fork");
		pthread_mutex_lock(&args->forks[args->philosophers[id].left_fork]);
		print_state(args, id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&args->forks[args->philosophers[id].left_fork]);
		print_state(args, id, "has taken a fork");
		pthread_mutex_lock(&args->forks[args->philosophers[id].right_fork]);
		print_state(args, id, "has taken a fork");
	}
	print_state(args, id, "is eating");
	pthread_mutex_lock(&args->meal_state);
	args->philosophers[id].started_meal = timestamp();
	args->philosophers[id].nb_meal += 1;
	pthread_mutex_unlock(&args->meal_state);
	sleep_mode(args, args->t_eat);
	pthread_mutex_unlock(&args->forks[args->philosophers[id].right_fork]);
	pthread_mutex_unlock(&args->forks[args->philosophers[id].left_fork]);
	// pthread_mutex_lock(&args->print_philo_state);
	// printf("\033[0;33mphilo %d ate %d times \033[0m\n", id, args->philosophers[id].nb_meal);
	// pthread_mutex_unlock(&args->print_philo_state);
}

static void	*print_thread(void *philo)
{
	t_philosopher	*philosopher;
	struct s_args	*args;

	philosopher = (t_philosopher *)philo;
	args = philosopher->args;
	if (philosopher->id % 2 == 0)
		usleep(100);
	while (is_dead(args) == 0 && args->all_ate != 1)
	{
		philosopher_eats(args, philosopher->id);
		print_state(args, philosopher->id, "is sleeping");
		sleep_mode(args, args->t_sleep);
		print_state(args, philosopher->id, "is thinking");
	}
	return (NULL);
}

void	is_anyone_dead_or_full(t_args *args, t_philosopher *philo)
{
	int	i;

	while (args->all_ate != 1)
	{
		i = 0;
		while (is_dead(args) == 0 && i < args->nb_philo)
		{
			pthread_mutex_lock(&args->meal_state);
			if (diff_time_in_msec(philo[i].started_meal, timestamp()) > args->t_die)
			{
				print_state(args, i, "\033[31mdied\033[0m");
				args->died = 1;
			}
			pthread_mutex_unlock(&args->meal_state);
			i++;
		}
		if (args->died == 1)
			break;
		i = 0;
		pthread_mutex_lock(&args->meal_state);
		while (args->number_must_eat != -1 && i < args->nb_philo && philo[i].nb_meal >= args->number_must_eat)
			i++;
		if (i == args->nb_philo)
			args->all_ate = 1;
		pthread_mutex_unlock(&args->meal_state);
		usleep(1000);
	}
}

int	executor(t_args *args)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	philo = args->philosophers;
	while (i < args->nb_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, print_thread, &(philo[i])) != 0)
			return (0);
		i++;
	}
	is_anyone_dead_or_full(args, philo);
	i = 0;
	while (i < args->nb_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	kill_everything(args);
	return (1);
}
