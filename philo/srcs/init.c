/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 22:30:05 by tiade-al          #+#    #+#             */
/*   Updated: 2025/07/16 18:19:14 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/** @brief Initializes the forks for each philosopher preventing deadlock.
 * The function assigns the first and second fork to each philosopher based 
 * on their position.
 * If the philosopher's ID is even, they take the left fork first and then the
 *  right fork.
 * If the philosopher's ID is odd, they take the right fork first and then the
 *  left fork.
 * This ensures that no two adjacent philosophers will try to pick up the same
 *  fork at the same time,
 * thus preventing deadlock.
 * @param philo Pointer to the philosopher structure.
 * @param forks Array of forks.
 * @param philo_pos Position of the philosopher in the array.
 * @return Void
*/
static void	get_fork(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	total_philos;

	total_philos = philo->table->total_philos;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % total_philos];
	}
	else
	{
		philo->first_fork = &forks[(philo_pos + 1) % total_philos];
		philo->second_fork = &forks[philo_pos];
	}
}

/** @brief Initializes the philosophers in the table structure.
 * This function sets up each philosopher's ID, meal count, fullness status, and
 *  mutex for
 * protecting individual state variables. It also assigns forks to each 
 * philosopher based on their position.
 * @param table Pointer to the table structure containing the philosophers.
 * @return 0 on success, or -1 on failure (mutex initialization error).
 */
static int	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->total_philos)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->meals_taken = 0;
		philo->full = false;
		philo->table = table;
		get_fork(philo, table->forks, i);
		if (pthread_mutex_init(&philo->philo_mutex, NULL) != 0)
			return (error_free("Error: Failed to init philo mutex", table));
		philo->philo_mutex_init = true;
	}
	return (0);
}

/** @brief Initializes the table structure and allocates memory for philosophers
 *  and forks.
 * This function sets up the initial state of the table, including the number 
 * of running threads,
 * whether all threads have been created, and whether the simulation has ended.
 *  It also allocates
 * memory for the philosophers and forks, initializing their mutexes to prevent
 *  concurrent access issues.
 * @param table Pointer to the table structure to be initialized.
 * @return 0 on success, or -1 on failure (memory allocation error).
 */
static int	table_init(t_table *table)
{
	int	i;

	i = -1;
	table->nbr_running_threads = 0;
	table->all_threads_created = false;
	table->end_simulation = false;
	table->table_mutex_init = false;
	table->print_mutex_init = false;
	table->philos = NULL;
	table->forks = NULL;
	table->philos = malloc(sizeof(t_philo) * table->total_philos);
	table->forks = malloc(sizeof(t_fork) * table->total_philos);
	if (!table->forks || !table->philos)
		return (-1);
	while (++i < table->total_philos)
	{
		table->philos[i].philo_mutex_init = false;
		table->forks[i].fork_mutex_init = false;
	}
	return (0);
}

/** @brief Initializes the table and philosophers for the simulation.
 * This function allocates memory for the table and its components, initializes
 *  mutexes for
 * synchronization, and sets up the philosophers with their respective forks.
 *  It handles errors
 * related to memory allocation and mutex initialization, ensuring that 
 * resources are properly cleaned up.
 * @param table Pointer to the table structure to be initialized.
 * @return 0 on success, or -1 on failure (error message printed and resources
 *  freed).
 */
int	init(t_table *table)
{
	int	i;

	i = -1;
	if (table_init(table) == -1)
		return (error_free("Error: Memory allocation failed", table));
	if (pthread_mutex_init(&table->table_mutex, NULL) != 0)
		return (error_free("Error: Failed to init table mutex", table));
	table->table_mutex_init = true;
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (error_free("Error: Failed to init write mutex", table));
	table->print_mutex_init = true;
	while (++i < table->total_philos)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
			return (error_free("Error: Failed to init fork mutex", table));
		table->forks[i].fork_mutex_init = true;
		table->forks[i].id = i;
	}
	return (philo_init(table));
}
