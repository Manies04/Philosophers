/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 22:48:33 by tiade-al          #+#    #+#             */
/*   Updated: 2025/07/16 17:59:34 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/** @brief Waits for all threads to be created before proceeding.
 * @param table Pointer to the table structure.
 * @return Void
 */
void	wait_for_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_created))
		;
}

/** @brief Desynchronizes philosophers to prevent deadlock.
 * @param philo Pointer to the philosopher structure.
 * @return Void
 */
void	desync_philos(t_philo *philo)
{
	if (philo->table->total_philos % 2 == 0 && philo->id % 2 == 0)
		precise_usleep(30000, philo->table);
	else if (philo->table->total_philos % 2 != 0 && philo->id % 2 != 0)
		ft_think(philo, true);
}

/** @brief Checks if all philosopher threads are running.
 * @param mutex Pointer to the mutex for synchronization.
 * @param nbr_thrds Pointer to the number of running threads.
 * @param total_philos Total number of philosophers.
 * @return Returns true if all threads are running, false otherwise.
 */
bool	all_threads_running(t_mutex *mutex, long *nbr_thrds, long total_philos)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mutex);
	if (*nbr_thrds == total_philos)
		ret = true;
	pthread_mutex_unlock(mutex);
	return (ret);
}
