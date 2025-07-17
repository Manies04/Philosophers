/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 00:54:51 by tiade-al          #+#    #+#             */
/*   Updated: 2025/07/16 18:46:43 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>

#define INFINITE_MEALS -1
#define INVALID_MAX_MEALS -2

#define RED		"\033[31m"
#define GRN		"\033[32m"
#define MGT		"\033[35m"
#define CYN		"\033[36m"
#define RST		"\033[0m"
#define BLU		"\033[34m"
#define WHT		"\033[37m"

typedef pthread_mutex_t	t_mutex;

typedef struct s_table	t_table;

typedef enum e_time
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS,
}				t_e_time;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	FIRST_FORK,
	SECOND_FORK,
	DIED,
}				t_status;

typedef struct s_fork
{
	int		id;
	t_mutex	fork;//prevents race condition, allowing 1 philo to have said fork
	bool	fork_mutex_init;//checks if its init, prevents destruct un-init ones
}			t_fork;

typedef struct s_philo
{
	int			id;
	pthread_t	thr_id;//used to wait for that thread
	t_fork		*first_fork;//1st fork the philo attempts to pick up
	t_fork		*second_fork;//2nd fork the philosopher needs to eat
	t_mutex		philo_mutex;//protects the philosopher’s state
	bool		philo_mutex_init;//initialized?, prevents destruct un-init ones
	long		last_meal_time;//see if they starved
	long		meals_taken;//meal counter
	bool		full;//if all meals indicated have been consumed
	t_table		*table;//interaction w the table
}				t_philo;

typedef struct s_table
{
	long		total_philos;//total num of philos
	long		time_to_die;//time before a philo dies if no food
	long		time_to_eat;//time it takes to eat a meal
	long		time_to_sleep;//time it takes to sleep after eating
	long		limit_meals;//max meals a philo can eat before full
	long		start_of_simulation;//timestamp of the start of the simulation
	bool		end_simulation;//if the sim has ended, used to stop threads
	t_fork		*forks;//array of forks, one for each philo
	t_philo		*philos;//array of philos structs, each represents a philo state
	long		nbr_running_threads;//nbr of philos ready to execute
	bool		all_threads_created;//if all threads have been created
	pthread_t	monitor;//checks for philo deaths and the sim end
	t_mutex		print_mutex;//thread-safe printing of status messages
	bool		print_mutex_init;//if print mutex is init
	t_mutex		table_mutex;//protection of shared states(end_simulation...)
	bool		table_mutex_init;// if table mutex is init
}				t_table;

int		parser(t_table *table, char **argv);
int		init(t_table *table);
int		feast(t_table *table);
void	set_bool(t_mutex *mutex, bool *value, bool new_value);
bool	get_bool(t_mutex *mutex, bool *value);
void	set_long(t_mutex *mutex, long *value, long new_value);
long	get_long(t_mutex *mutex, long *value);
void	increment_long(t_mutex *mutex, long *value);
void	wait_for_threads(t_table *table);
long	get_time(t_e_time time_code);
void	precise_usleep(long usleep_time, t_table *table);
void	*dine_alone(void *arg);
void	*dine_w_friends(void *arg);
void	desync_philos(t_philo *philo);
void	ft_eat(t_philo	*philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo, bool pre_simulation);
void	*monitoration(void *arg);
bool	simulation_ended(t_table	*table);
void	print_status(t_philo *philo, t_status status);
void	clean(t_table *table);
int		error_free(char	*error_message, t_table *table);
bool	all_threads_running(t_mutex *mutex, long *nbr_thrds, long total_philos);
