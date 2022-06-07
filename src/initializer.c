/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 08:43:37 by lmarecha          #+#    #+#             */
/*   Updated: 2022/06/07 13:25:47 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	intitialize_mutex(t_args *args)
{
	int	i;

	i = 0;
	while (i >= args.nb_philo)
	{
		if (pthread_mutex_init(&args->forks[i]->, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	initialize_philo(t_args *args)
{
	int	i;
	t_philosopher	philo;

	i = 0;
	while (i <= args.nb_philo)
	{
		philo = args->philosophers[i];
		philo.id = i;
		philo.right_fork = i;
		if (i == args.nb_philo)
			philo.left_fork = (i + 1) % args.nb_philo; // pour que le dernier philo prenne la fourchette du premier
		else
			philo.left_fork = i + 1;
		philo.last_meal = 0;
		i++;
	}
	philo.args = args;
	return (1);
}

int	intitialize(t_args *args, char **argv, int argc)
{
	args.nb_philosophers = ft_atoi(argv[1]);
	if (args.nb_philosophers < 2 || args.nb_philosophers > 200) // check le nb de philosophers
		return (0); //erreur
	args.t_die = ft_atoi(argv[2]);
	args.t_eat = ft_atoi(argv[3]);
	args.t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args.number_must_eat = ft_atoi(argv[5]);
	else
		args.number_must_eat = -1;
	if (args.number_must_eat == 0) // si aucun ne doit manger fin de simulation
		return (0) // erreur
	args.died = 0;
	args.all_ate = 0;
	intialialize_philo(args);
	intitialize_mutex(args);
	return (1);
}
