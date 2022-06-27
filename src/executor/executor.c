/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:32:49 by lmarecha          #+#    #+#             */
/*   Updated: 2022/06/27 18:27:23 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
//
void	philosopher_eats(t_args *args, int id)
{
	if (args->philosophers[id].nb_meal == args->number_must_eat || args->died == 1)
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
	// pthread_mutex_lock(&args->print_philo_state);
	// printf("\033[0;33mphilo %d ate %d times \033[0m\n", id, args->philosophers[id].nb_meal);
	// pthread_mutex_unlock(&args->print_philo_state);
}


void	is_anyone_dead_or_full(t_args *args, int id)
{
//-> si un philo n'a pas commence a manger time_to_die millisec apres le debut de son precedent repas ou du debut de la similuation il meurt
	pthread_mutex_lock(&args->print_philo_state);
	printf("t_die = %d\n", args->t_die);
	printf("philo[%d] timestamp = %lld\n", id, timestamp());
	printf("first timestamp = %lld\n", args->first_timestamp);
	printf("philo[%d].started_meal = %lld\n", id, args->philosophers[id].started_meal);
	printf("timestamp - started_meal = %lld\n", diff_time_in_msec(args->philosophers[id].started_meal, timestamp()));
	// printf("started_meal - first_timestamp = %lld\n", diff_time_in_msec(args->first_timestamp, args->philosophers[id].started_meal));
	pthread_mutex_unlock(&args->print_philo_state);
	if (args->number_must_eat != -1 && args->philosophers[id].nb_meal == args->number_must_eat)
	{
		pthread_mutex_lock(&args->meal_state);
		args->all_ate += 1;
		pthread_mutex_unlock(&args->meal_state);
	}
	//pb ici ?
	// if (args->number_must_eat != -1 && args->philosophers[id].nb_meal < args->number_must_eat)
	// {
	if (diff_time_in_msec(args->philosophers[id].started_meal, timestamp()) > args->t_die)
	{
		print_state(args, id, "died waited too long since last meal");
		args->died = 1;
	}
	if (args->philosophers[id].nb_meal == 1 && diff_time_in_msec(args->first_timestamp, args->philosophers[id].started_meal) > args->t_die)
	{
		print_state(args, id, "died haven't eaten since begining");
		args->died = 1;
	}
	// }
}

static void	*print_thread(void *philo)
{
	t_philosopher	*philosopher;
	struct s_args	*args;

	philosopher = (t_philosopher *)philo;
	args = philosopher->args;
	while (args->died != 1 && philosopher->nb_meal != args->number_must_eat)
	{
		philosopher_eats(args, philosopher->id);
		is_anyone_dead_or_full(args, philosopher->id);
		// if (args->all_ate >= args->nb_philo)
		// 	break ;
		print_state(args, philosopher->id, "is sleeping");
		sleep_mode(args, args->t_sleep);
		print_state(args, philosopher->id, "is thinking");

	}
	return (NULL);
}

int	executor(t_args *args)
{
	int				i;
	int				max_meals;
	t_philosopher	*philo;

	i = 1;
	max_meals = 0;
	philo = args->philosophers;
	while (i <= args->nb_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, print_thread, &(philo[i])) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < args->nb_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	// philo_death_checker();
	// destroy_all();
	return (1);
	// je cree les thread de chaque philosophe qui m'envoit vers la fonction qui s'execute dans le thread
	// je check si quelu'un doit mourir
	// je finis avec la fonction qui va join mes threads + destroy les mutex fourchettes et ecriture
}
