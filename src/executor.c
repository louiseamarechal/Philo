/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:32:49 by lmarecha          #+#    #+#             */
/*   Updated: 2022/06/07 13:45:35 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	philosopher_eats_even(t_args *args)
{
	// 2. - si le philosophe peut manger il mange
	// //		-> lock fourchette droite
	// 			-> j'imprime l'action sur le PROMPT
	// 			-> lock fourchette gauche
	// 			-> j'imprime l'action sur le PROMPT
	// 			-> je lock le meal de mon philosophe pour etre sur qu'il meurt pas en meme temps
	// 			-> j'imprime l'action sur le PROMPT
	// 			-> je save le timestamp started_meal (pour checker plus tard si il doit mourir)
	// 			-> je unlock le meal
	// 			-> je sleep le temps de t_eat
	// 			-> j'augmente nb_meal pour notifier que mon philosopher a deja mange au moins une fois
	// 			-> je unlock mes deux fourchettes
	// //	- sinon il continue de penser
	// //		-> si un philo n'a pas commence a manger time_to_die millisec apres le debut de son precedent repas ou du debut de la similuation il meurt
	// //		-> il finit de manger time_to_eat millisec apres le debut de son repas
}

void	philosopher_eats_odd(t_args *args)
{
	// 2. - si le philosophe peut manger il mange
	// //		-> lock fourchette gauche
	// 			-> j'imprime l'action sur le PROMPT
	// 			-> lock fourchette droite
	// 			-> j'imprime l'action sur le PROMPT
	// 			-> je lock le meal de mon philosophe pour etre sur qu'il meurt pas en meme temps
	// 			-> j'imprime l'action sur le PROMPT
	// 			-> je save le timestamp started_meal (pour checker plus tard si il doit mourir)
	// 			-> je unlock le meal
	// 			-> je sleep le temps de t_eat
	// 			-> j'augmente nb_meal pour notifier que mon philosopher a deja mange au moins une fois
	// 			-> je unlock mes deux fourchettes
	// //	- sinon il continue de penser
	// //		-> si un philo n'a pas commence a manger time_to_die millisec apres le debut de son precedent repas ou du debut de la similuation il meurt
	// //		-> il finit de manger time_to_eat millisec apres le debut de son repas
}

void	print_thread(void *philo)
{
	t_philosopher	*philosopher;
	t_args			*args;

	args = philosopher->args;
	philosopher = (t_philosopher *)philo;
	while (args.died != 1)
	{
		if (philo.id % 2 == 0)
			philosopher_eats_even(args);
		else
			philosopher_eats_odd(args);
		if (args.all_ate == 1)
			break ;
		print_state(timestamp(), "is sleeping");
		change_state(args.t_sleep);
		print_state(timestamp(), "is thinking");
	}
	// 1. si philo_id %2 -> fonction eat_even
	// 2. si philo non %2 -> fonction eat_odd
	//		fonction va print le timestamp fourchette + lunch
	// 3. si all_ate == true -> je break
	// 4. Philo commence a dormir pour t_sleep
	// 5. je print le timestamp + etat sleep
	// 6. le philosophe THINK
	// 7. print le timestamp et son etat
}

int	executor(t_args *args)
{
	int				i;
	t_philosopher	philo;

	i = 0;
	philo = args.philosophers;
	while (i < args.nb_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, print_thread, &(philo[i])) != 0)
			return (0);
		i++;
	}
	philo_death_checker();
	destroy_all();
	return (1);
	// je cree les thread de chaque philosophe qui m'envoit vers la fonction qui s'execute dans le thread
	// je check si quelu'un doit mourir
	// je finis avec la fonction qui va join mes threads + destroy les mutex fourchettes et ecriture
}
