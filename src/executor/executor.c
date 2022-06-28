/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:32:49 by lmarecha          #+#    #+#             */
/*   Updated: 2022/06/28 11:42:04 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
//
void	philosopher_eats(t_args *args, int id)
{
	if (args->all_ate == 1 || args->died == 1)
		return ;
	if (id % 2 == 0)
	{
		pthread_mutex_lock(&args->forks[args->philosophers[id].right_fork]);
		pthread_mutex_lock(&args->forks[args->philosophers[id].left_fork]);
	}
	else
	{
		pthread_mutex_lock(&args->forks[args->philosophers[id].left_fork]);
		pthread_mutex_lock(&args->forks[args->philosophers[id].right_fork]);
	}
	print_state(args, id, "has taken a fork");
	print_state(args, id, "has taken a fork");
	print_state(args, id, "is eating");
	pthread_mutex_lock(&args->meal_state);
	args->philosophers[id].started_meal = timestamp();
	args->philosophers[id].nb_meal += 1;
	pthread_mutex_unlock(&args->meal_state);
	sleep_mode(args, args->t_eat);
	pthread_mutex_unlock(&args->forks[args->philosophers[id].right_fork]);
	pthread_mutex_unlock(&args->forks[args->philosophers[id].left_fork]);
	pthread_mutex_lock(&args->print_philo_state);
	printf("\033[0;33mphilo %d ate %d times \033[0m\n", id, args->philosophers[id].nb_meal);
	pthread_mutex_unlock(&args->print_philo_state);
}

static void	*print_thread(void *philo)
{
	t_philosopher	*philosopher;
	struct s_args	*args;

	philosopher = (t_philosopher *)philo;
	args = philosopher->args;
	while (args->died != 1)
	{
		philosopher_eats(args, philosopher->id);
		if (args->all_ate == 1)
			break ;
		print_state(args, philosopher->id, "is sleeping");
		sleep_mode(args, args->t_sleep);
		print_state(args, philosopher->id, "is thinking");

	}
	return (NULL);
}

void	is_anyone_dead_or_full(t_args *args, t_philosopher *philo)
{
	int	id;

	id = 0;
	while (args->all_ate != 1)
	{
		id = 1;
		while (args->died != 1 && id <= args->nb_philo)
		{
			pthread_mutex_lock(&args->meal_state);
			if (diff_time_in_msec(philo[id].started_meal, timestamp()) > args->t_die)
			{
				print_state(args, id, "died");
				args->died = 1;
			}
			pthread_mutex_unlock(&args->meal_state);
			id++;
		}
		if (args->died == 1)
			break;
		id = 1;
		while (id <= args->nb_philo && philo[id].nb_meal == args->number_must_eat)
			id++;
		if (id == args->nb_philo)
			args->all_ate = 1;
		usleep(1000);
	}
}

int	executor(t_args *args)
{
	int				i;
	t_philosopher	*philo;

	i = 1;
	philo = args->philosophers;
	while (i <= args->nb_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, print_thread, &(philo[i])) != 0)
			return (0);
		i++;
	}
	is_anyone_dead_or_full(args, philo);
	i = 1;
	while (i <= args->nb_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	// destroy_all();
	return (1);
	// je cree les thread de chaque philosophe qui m'envoit vers la fonction qui s'execute dans le thread
	// je check si quelu'un doit mourir
	// je finis avec la fonction qui va join mes threads + destroy les mutex fourchettes et ecriture
}
