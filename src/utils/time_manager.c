/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:09:00 by lmarecha          #+#    #+#             */
/*   Updated: 2022/06/30 14:26:56 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// long long int	diff_time_in_msec(long long int t1, long long int t2)
// {
// 	return (t2 - t1);
// }

long long int	get_time(void)
{
	struct timeval	time;
	long long int	timeofday;

	timeofday = 0;
	gettimeofday(&time, NULL);
	timeofday += time.tv_sec * 1000;
	timeofday += time.tv_usec / 1000;
	return (timeofday);
}

void	sleep_mode(t_args *args, long long received_time)
{
	long long	i;

	i = get_time();
	while (is_dead(args) == 0)
	{
		if ((get_time() - i) >= received_time)
			break ;
		usleep(50);
	}
}

void	print_state(t_args *args, int philo_id, char *state)
{
	long long	i;

	i = get_time();
	pthread_mutex_lock(&args->global_block);
	if (args->died != 1)
		printf("%lld %d %s\n", i - args->start_simu, philo_id + 1, state);
	pthread_mutex_unlock(&args->global_block);
}

// int	main(void)
// {
// 	struct timeval t1;
// 	struct timeval t2;
//
// 	gettimeofday(&t1, NULL);
// 	usleep(1000000);
// 	gettimeofday(&t2, NULL);
// 	printf("%ld\n", diff_time_in_msec(t2, t1));
//
// 	return (0);
// }
