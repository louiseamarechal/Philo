/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:32:49 by lmarecha          #+#    #+#             */
/*   Updated: 2022/06/30 13:45:21 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	philosopher_eats(t_args *args, int id)
{
	pthread_mutex_lock(&args->meal_state);
	if (args->all_ate == 1 || args->died == 1)
		return (pthread_mutex_unlock(&args->meal_state), (void)NULL);
	pthread_mutex_unlock(&args->meal_state);
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
	args->philosophers[id].started_meal = get_time();
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
	if (philosopher->id % 2 != 0)
		usleep(100);
	while (is_dead(args) == 0)
	{
		philosopher_eats(args, philosopher->id);
		pthread_mutex_lock(&args->meal_state);
		if (args->all_ate == 1)
			return (pthread_mutex_unlock(&args->meal_state), NULL);
		pthread_mutex_unlock(&args->meal_state);
		print_state(args, philosopher->id, "is sleeping");
		sleep_mode(args, args->t_sleep);
		print_state(args, philosopher->id, "is thinking");
	}
	return (NULL);
}

int	is_anyone_dead_or_full(t_args *args, t_philosopher *philo)
{
	int	i;

	while (args->all_ate != 1)
	{
		i = 0;
		while (is_dead(args) == 0 && i < args->nb_philo)
		{
			death_condition(args, philo[i], i);
			i++;
		}
		if (is_dead(args) == 1)
			break;
		i = 0;
		pthread_mutex_lock(&args->meal_state);
		while (args->number_must_eat != -1 && i < args->nb_philo && philo[i].nb_meal >= args->number_must_eat)
			i++;
		if (i == args->nb_philo)
			args->all_ate = 1;
			// return (2);
		pthread_mutex_unlock(&args->meal_state);
		usleep(1000);
	}
	return (0);
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
	// if (is_anyone_dead_or_full(args, philo) == 1)
	// 	args->died = 1;
	// if (is_anyone_dead_or_full(args, philo) == 2)
	// 	args->all_ate = 1;
	i = 0;
	while (i < args->nb_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	kill_everything(args);
	return (1);
}
