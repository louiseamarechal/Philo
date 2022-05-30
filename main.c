#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NB_OF_PHILOSOPHERS 3

typedef struct s_philosopher {
	int	philosopher;
	int	fork;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
} t_philosopher;

typedef struct mutex_data {
	t_list	*philosophers;
	pthread_mutex_t	mutex;
} mutex_data;

void	*print_thread(void *arg)
{
	mutex_data	*md;
	int			thread_id;

	thread_id = pthread_self();
	md = (mutex_data *)arg;
	pthread_mutex_lock(&(*md).mutex);
	printf("thread [ %d ]\n", thread_id);
	pthread_mutex_unlock(&(*md).mutex);
	return (NULL);
}

int	main(void)
{
	pthread_t	threads[NB_OF_PHILOSOPHERS];
	mutex_data	md; // creation du mutex
	int			i;
	int			err;
	int			time;

	i = 0;
	md.data = 0;

	// initialisation mutex
	if (pthread_mutex_init(&md.mutex, NULL) != 0)
	{
		printf("mutex init failed\n");
		return (EXIT_FAILURE);
	}
	while (i < NB_OF_PHILOSOPHERS)
	{
		// creation des thread
		err = pthread_create(&threads[i], NULL, print_thread, &md);
		if (err != 0)
		{
			printf("echec de la creation du thread\n");
			break ;
		}
		printf("creation du thread numero %ld\n", threads[i]);
		i++;
	}

	// attends les threads
	i = 0;
	while (i < NB_OF_PHILOSOPHERS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
}
