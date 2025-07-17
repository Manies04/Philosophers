/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:38:59 by tiade-al          #+#    #+#             */
/*   Updated: 2025/07/16 17:35:57 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/** @brief Gets the current time in specified units.
 * @param time_code The unit of time (SECONDS, MILLISECONDS, or MICROSECONDS).
 * @return Returns the time in the specified unit, or -1 on error.
 */
long	get_time(t_e_time time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	if (time_code == SECONDS)
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (time_code == MILLISECONDS)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (time_code == MICROSECONDS)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	else
		return (-1);
}

/** @brief Pauses execution for a specified duration with precision.
 * @param usleep_time The duration to sleep in microseconds.
 * @param table Pointer to the table structure.
 * @return Void
 */
void	precise_usleep(long usleep_time, t_table *table)
{
	long	start;
	long	current;
	long	remaining;

	start = get_time(MICROSECONDS);
	current = start;
	while ((current - start) < usleep_time)
	{
		if (simulation_ended(table))
			break ;
		current = get_time(MICROSECONDS);
		remaining = usleep_time - (current - start);
		if (remaining > 1000)
			usleep(remaining / 2);
		else
			while ((get_time(MICROSECONDS) - start) < usleep_time)
				;
	}
}
