/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:16:15 by tiade-al          #+#    #+#             */
/*   Updated: 2025/07/16 17:53:12 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/** @brief Sets a boolean value in a thread-safe manner.
 * @param mutex Pointer to the mutex for synchronization.
 * @param value Pointer to the boolean value to set.
 * @param new_value The new boolean value.
 * @return Void
 */
void	set_bool(t_mutex *mutex, bool *value, bool new_value)
{
	pthread_mutex_lock(mutex);
	*value = new_value;
	pthread_mutex_unlock(mutex);
}

/** @brief Gets a boolean value in a thread-safe manner.
 * @param mutex Pointer to the mutex for synchronization.
 * @param value Pointer to the boolean value to retrieve.
 * @return Returns the boolean value.
 */
bool	get_bool(t_mutex *mutex, bool *value)
{
	bool	boolean;

	pthread_mutex_lock(mutex);
	boolean = *value;
	pthread_mutex_unlock(mutex);
	return (boolean);
}

/** @brief Sets a long integer value in a thread-safe manner.
 * @param mutex Pointer to the mutex for synchronization.
 * @param value Pointer to the long integer value to set.
 * @param new_value The new long integer value.
 * @return Void
 */
void	set_long(t_mutex *mutex, long *value, long new_value)
{
	pthread_mutex_lock(mutex);
	*value = new_value;
	pthread_mutex_unlock(mutex);
}

/** @brief Gets a long integer value in a thread-safe manner.
 * @param mutex Pointer to the mutex for synchronization.
 * @param value Pointer to the long integer value to retrieve.
 * @return Returns the long integer value.
 */
long	get_long(t_mutex *mutex, long *value)
{
	long	safe_value;

	pthread_mutex_lock(mutex);
	safe_value = *value;
	pthread_mutex_unlock(mutex);
	return (safe_value);
}

/** @brief Increments a long integer value in a thread-safe manner.
 * @param mutex Pointer to the mutex for synchronization.
 * @param value Pointer to the long integer value to increment.
 * @return Void
 */
void	increment_long(t_mutex *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}
