/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:12:22 by tiade-al          #+#    #+#             */
/*   Updated: 2025/07/16 18:23:53 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/** @brief Prints the status of a philosopher during the simulation.
 * @param philo Pointer to the philosopher structure.
 * @param status The status to print (e.g., FIRST_FORK, EATING, etc.).
 * @return Void
 */
void	print_status(t_philo *philo, t_status status)
{
	long	elapsed;

	if (simulation_ended(philo->table) || get_bool(&philo->philo_mutex,
			&philo->full))
		return ;
	elapsed = get_time(MILLISECONDS) - philo->table->start_of_simulation;
	pthread_mutex_lock(&philo->table->print_mutex);
	if (status == FIRST_FORK)
		printf(WHT"%-6ld "BLU"%d has taken a fork\t\t\t[fork %d]\n"RST,
			elapsed, philo->id, philo->first_fork->id);
	else if (status == SECOND_FORK)
		printf(WHT"%-6ld "BLU"%d has taken a fork\t\t\t[fork %d]\n"RST,
			elapsed, philo->id, philo->second_fork->id);
	else if (status == EATING)
		printf(WHT"%-6ld "CYN"%d is eating\t\t\t[meal %ld]\n"RST,
			elapsed, philo->id, philo->meals_taken);
	else if (status == SLEEPING)
		printf(WHT"%-6ld "MGT"%d is sleeping\n"RST, elapsed, philo->id);
	else if (status == THINKING)
		printf(WHT"%-6ld "GRN"%d is thinking\n"RST, elapsed, philo->id);
	else if (status == DIED)
		printf(WHT"%-6ld "RED"%d died\n"RST, elapsed, philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

/** @brief Simulates a philosopher eating by acquiring forks and updating state.
 * @param philo Pointer to the philosopher structure.
 * @return Void
 */
void	ft_eat(t_philo	*philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	print_status(philo, FIRST_FORK);
	pthread_mutex_lock(&philo->second_fork->fork);
	print_status(philo, SECOND_FORK);
	set_long(&philo->philo_mutex,
		&philo->last_meal_time, get_time(MILLISECONDS));
	print_status(philo, EATING);
	philo->meals_taken++;
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->limit_meals > 0
		&& philo->meals_taken == philo->table->limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

/** @brief Simulates a philosopher sleeping for a specified duration.
 * @param philo Pointer to the philosopher structure.
 * @return Void
 */
void	ft_sleep(t_philo *philo)
{
	print_status(philo, SLEEPING);
	precise_usleep(philo->table->time_to_sleep, philo->table);
}

/** @brief Simulates a philosopher thinking, with a delay for odd-numbered
 *  philosopher groups.
 * This function prints the thinking status (unless in pre-simulation mode)
 *  and introduces
 * a delay when the total number of philosophers is odd to prevent 
 * deadlock. The delay is used to desynchronize philosopher actions.
 * @param philo Pointer to the philosopher structure.
 * @param pre_simulation Boolean indicating if called before simulation
 *  starts.
 * @return Void
 */
void	ft_think(t_philo *philo, bool pre_simulation)
{
	int	t_think;

	if (!pre_simulation)
		print_status(philo, THINKING);
	if ((philo->table->total_philos % 2) == 0)
		return ;
	t_think = (philo->table->time_to_eat * 2) - philo->table->time_to_sleep;
	if (t_think > 0)
		precise_usleep(t_think * 0.42, philo->table);
}
