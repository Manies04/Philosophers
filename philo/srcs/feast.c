/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:26:05 by tiade-al          #+#    #+#             */
/*   Updated: 2025/07/16 17:41:52 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/** @brief Launches threads for philosophers and the monitor.
 * @param table Pointer to the table structure.
 * @return Returns 0 on success, or -1 on thread creation failure.
 */
static int	launch_threads(t_table *table)
{
	int	i;

	i = -1;
	if (table->total_philos == 1)
	{
		if (pthread_create(&table->philos[0].thr_id, NULL,
				dine_alone, &table->philos[0]) != 0)
			return (-1);
	}
	else
	{
		while (++i < table->total_philos)
			if (pthread_create(&table->philos[i].thr_id, NULL,
					dine_w_friends, &table->philos[i]) != 0)
				return (-1);
	}
	if (pthread_create(&table->monitor, NULL, monitoration, table) != 0)
		return (-1);
	return (0);
}

/** @brief Joins threads for philosophers and the monitor.
 * @param table Pointer to the table structure.
 * @return Returns 0 on success, or -1 on thread join failure.
 */
static int	join_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->total_philos)
		if (pthread_join(table->philos[i].thr_id, NULL) != 0)
			return (-1);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	if (pthread_join(table->monitor, NULL) != 0)
		return (-1);
	return (0);
}

/** @brief Runs the dining philosophers simulation.
 * @param table Pointer to the table structure.
 * @return Returns 0 on success, or -1 on failure (with error message).
 */
int	feast(t_table *table)
{
	if (table->limit_meals == 0)
		return (0);
	if (launch_threads(table) == -1)
		return (error_free("Error: Failed to create threads", table));
	table->start_of_simulation = get_time(MILLISECONDS);
	set_bool(&table->table_mutex, &table->all_threads_created, true);
	if (join_threads(table) == -1)
		return (error_free("Error: Failed to join threads", table));
	return (0);
}
