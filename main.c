/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:15:38 by lmarecha          #+#    #+#             */
/*   Updated: 2022/06/07 13:26:22 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_args	args;

	if (argc != 5 || argc != 6)
	{
		printf("Wrong number of arguments !");
		return (1);
	}
	initialize(&args);
//		----------------------PARSER---------------
//		1. verifier que je n'ai pas trop d'arguments
//		2. verifier si il y a 'number_of_times_each_philosopher_must_eat'
//			-> ajuster le code en fonction
//		3. recuperer les donnees de chaque arguments
//		4. transformer les time_to en milliseconds
//		5. initialiser la structure
//		6. envoyer a l'executor

// 		--------------------EXECUTOR--------------------
// 		THREAD
// 			->creer un thread par philosophers

// 		EAT
//		 1. Verifier si le philosopher peut manger
//			 -> philosophers paires commencent par la fourchette de droite
//			 -> philosophers impaires prennent la fourchette de gauche first
//				 si l'une des deux n'est pas dispo il ne peut pas manger
//
//
//
//		 SLEEP
//		 Quand le philosopher a fini de manger il se met a dormir
//			 -> il dort time_to_sleep millisec apres la fin de son repas (ou apres le debut de sa sieste)
//
//		 THINK
//		 Quand le philosophe a fini de dormir il se met a penser
//			-> il pense jusqu'a ce qu'il puisse manger || qu'il meurt
//
//		 PROMPT INFO
//		 Des qu'un philosopher fait une action l'ecrire sur le prompt
//			 -> avec l'actual timestamp auquel l'action a eu lieu
//				-> convertir le timestamp en milliseconds
}
