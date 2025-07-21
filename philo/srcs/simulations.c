/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:56:04 by tiade-al          #+#    #+#             */
/*   Updated: 2025/07/21 15:16:42 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/** @brief Checks if the simulation has ended.
 * @param table Pointer to the table structure.
 * @return Returns true if the simulation has ended, false otherwise.
 */
bool	simulation_ended(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}

/** @brief Simulates a philosopher dining with others.
 * @param arg Pointer to the philosopher structure.
 * @return Returns NULL.
 */
void	*dine_w_friends(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECONDS));
	increment_long(&philo->table->table_mutex,
		&philo->table->nbr_running_threads);
	desync_philos(philo);
	while (!simulation_ended(philo->table))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo, false);
	}
	return (NULL);
}

/** @brief Simulates a single philosopher dining alone.
 * @param arg Pointer to the philosopher structure.
 * @return Returns NULL.
 */
void	*dine_alone(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECONDS));
	increment_long(&philo->table->table_mutex,
		&philo->table->nbr_running_threads);
	print_status(philo, FIRST_FORK);
	while (!simulation_ended(philo->table))
		usleep(200);
	return (NULL);
}

/** @brief Checks if a philosopher has died due to starvation.
 * @param philo Pointer to the philosopher structure.
 * @return Returns true if the philosopher has died, false otherwise.
 */
static bool	philo_died(t_philo *philo)
{
	long	elapsed;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = get_time(MILLISECONDS) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	return (elapsed > (philo->table->time_to_die / 1000));
}

/** @brief Monitors philosophers for death or simulation end.
 * @param arg Pointer to the table structure.
 * @return Returns NULL.
 */
void	*monitoration(void *arg)
{
	int		i;
	t_table	*table;

	table = (t_table *)arg;
	while (!all_threads_running(&table->table_mutex,
			&table->nbr_running_threads, table->total_philos))
		usleep(30);
	while (!simulation_ended(table))
	{
		i = -1;
		while (++i < table->total_philos && !simulation_ended(table))
		{
			if (philo_died(table->philos + i))
			{
				print_status(table->philos + i, DIED);
				set_bool(&table->table_mutex, &table->end_simulation, true);
			}
		}
	}
	return (NULL);
}
