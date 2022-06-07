/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 08:43:37 by lmarecha          #+#    #+#             */
/*   Updated: 2022/06/07 09:48:07 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	initialize_philosophers(t_pihlosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < argc)
	{

		i++;
	}
}

void	intitialize(t_args *rules, char **argv, int argc)
{
	rules.nb_philosophers = ft_atoi(argv[1]);
		if (rules.nb_philosophers < 2)
			return (0);
	rules.time_to_die = ft_atoi(argv[2]);
	rules.time_to_eat = ft_atoi(argv[3]);
	rules.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules.number_must_eat = ft_atoi(argv[5]);
	else
		rules.number_must_eat = 0;
	rules.died = 0;
	rules.all_ate = 0;
	rules.philosophers = intialialize_philosophers(rules.philosophers);
}
