/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 22:35:22 by tiade-al          #+#    #+#             */
/*   Updated: 2025/07/16 17:34:07 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/** @brief Cleans up resources by destroying mutexes and freeing memory.
 * @param table Pointer to the table structure.
 * @return Void
 */
void	clean(t_table *table)
{
	int	i;

	i = -1;
	if (table->philos)
	{
		while (++i < table->total_philos)
			if (table->philos[i].philo_mutex_init)
				pthread_mutex_destroy(&table->philos[i].philo_mutex);
		free(table->philos);
		table->philos = NULL;
	}
	i = -1;
	if (table->forks)
	{
		while (++i < table->total_philos)
			if (table->forks[i].fork_mutex_init)
				pthread_mutex_destroy(&table->forks[i].fork);
		free(table->forks);
		table->forks = NULL;
	}
	if (table->table_mutex_init)
		pthread_mutex_destroy(&table->table_mutex);
	if (table->print_mutex_init)
		pthread_mutex_destroy(&table->print_mutex);
}

/** @brief Prints an error message and cleans up resources.
 * @param error_message The error message to print.
 * @param table Pointer to the table structure.
 * @return Returns -1 to indicate failure.
 */
int	error_free(char	*error_message, t_table *table)
{
	printf("%s\n", error_message);
	clean(table);
	return (-1);
}
