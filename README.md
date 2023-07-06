# Philo
42

In this project, we learned the basics of threading a process.
We created threads and you discovered mutexes.

## Rules of the dinning Philosophers problem :
One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.
The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.
There are also forks on the table. There are as many forks as philosophers.
Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.
When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
philosopher dies of starvation.
Every philosopher needs to eat and should never starve.
Philosophers don’t speak with each other.
Philosophers don’t know if another philosopher is about to die.

## Launch it from you Terminal :
$ make</br>
$ ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] (optional)[number_of_times_each_philosopher_must_eat]

## Test it :
$ ./philo 1 800 200 200 </br>
Philosopher should not eat (only one fork) and die </br></br>
$ ./philo 5 800 200 200 </br>
No one should die</br></br>
$ ./philo 4 310 200 100 </br>
A philosopher should die</br>

## Arguments :
1. number_of_philosophers: The number of philosophers and also the numberof forks. </br>
2. time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die. </br>
3. time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.</br>
4. time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.</br>
5. number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.
