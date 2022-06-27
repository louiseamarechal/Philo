/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:32:49 by lmarecha          #+#    #+#             */
/*   Updated: 2022/06/27 09:19:36 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
//
void	philosopher_eats(t_args *args, int id)
{
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
	// 			-> je lock le meal de mon philosophe pour etre sur qu'il meurt pas en meme temps
	// 			-> j'imprime l'action sur le PROMPT
	print_state(args, id, "is eating");
	// 			-> je save le timestamp started_meal (pour checker plus tard si il doit mourir)
	args->philosophers[id].started_meal = timestamp();
	// 			-> je unlock le meal
	// 			-> je sleep le temps de t_eat
	sleep_mode(args, args->t_eat);
	// 			-> j'augmente nb_meal pour notifier que mon philosophers a deja mange au moins une fois
	args->philosophers[id].nb_meal += 1;
	// 			-> je unlock mes deux fourchettes
	pthread_mutex_unlock(&args->forks[args->philosophers[id].right_fork]);
	pthread_mutex_unlock(&args->forks[args->philosophers[id].left_fork]);
	printf("philo %d ate %d times\n", id, args->philosophers[id].nb_meal);
	// //	- sinon il continue de penser
	// //		-> si un philo n'a pas commence a manger time_to_die millisec apres le debut de son precedent repas ou du debut de la similuation il meurt
	// //		-> il finit de manger time_to_eat millisec apres le debut de son repas
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
		// 3. si all_ate == true -> je break
		if (args->all_ate == 1)
		{
			printf("diner is over, we all ate !!!!!!!!");
			break ;
		}
		// 4. Philo commence a dormir pour t_sleep
		// 5. je print le timestamp + etat sleep
		print_state(args, philosopher->id, "is sleeping");
		sleep_mode(args, args->t_sleep);
		// 6. le philosophe THINK
		// 7. print le timestamp et son etat
		print_state(args, philosopher->id, "is thinking");
	}
	return (NULL);
}

void	diner_is_over(t_args *args)
{
	int	i;
	int	max_meals;

	i = 1;
	max_meals = 0;
	while (i <= args->nb_philo)
	{
		if (args->philosophers[i].nb_meal == args->number_must_eat)
			max_meals++;
		i++;
	}
	printf("max meals = %d\n", max_meals);
	if (max_meals == args->nb_philo)
		args->all_ate = 1;
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
		if (philo[i].nb_meal == args->number_must_eat)
			max_meals++;
		printf("------------------------philo[%d].nb_meal = %d\n", i, philo[i].nb_meal);
		printf("------------------------max_meals = %d\n", max_meals);
		printf("------------------------args->number_must_eat = %d\n", args->number_must_eat);
		printf("------------------------args->nb_philo = %d\n", args->nb_philo);
		if (max_meals == args->nb_philo)
			args->all_ate = 1;
		i++;
	}
	i = 0;
	while (i < args->nb_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	while (i != 0)
	{
		pthread_mutex_destroy(&args->forks[philo[i].right_fork]);
		i--;
	}
	// diner_is_over(args);
	// philo_death_checker();
	// destroy_all();
	return (1);
	// je cree les thread de chaque philosophe qui m'envoit vers la fonction qui s'execute dans le thread
	// je check si quelu'un doit mourir
	// je finis avec la fonction qui va join mes threads + destroy les mutex fourchettes et ecriture
}
