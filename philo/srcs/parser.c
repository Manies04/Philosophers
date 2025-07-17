/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:07:15 by tiade-al          #+#    #+#             */
/*   Updated: 2025/07/16 18:04:06 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/** @brief This function checks if the string is a valid number.
 * @param str The string to check.
 * @return Returns true if the string is a valid number, false otherwise.
 */
static bool	valid_num(const char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!(*str >= '0' && *str <= '9'))
		return (false);
	while (str[i] == '0')
	{
		i++;
		j++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	return ((i - j) <= 10);
}

/** @brief This function converts a string to a long int.
 * @param str The string to convert.
 * @return Returns the converted long integer, or -1 if the string is not 
 * a valid number.
 */
static long	ft_atol(const char *str)
{
	long	nbr;

	nbr = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	if (!valid_num(str))
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	if (nbr > INT_MAX || *str != '\0')
		return (-1);
	else
		return (nbr);
}

/** @brief Parses command-line arguments and initializes the table structure.
 * @param table Pointer to the table structure to initialize.
 * @param argv Array of command-line arguments.
 * @return Returns 0 on success, or -1 on invalid arguments.
 */
int	parser(t_table *table, char **argv)
{
	table->total_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argv[5])
	{
		table->limit_meals = ft_atol(argv[5]);
		if (table->limit_meals == -1)
			table->limit_meals = INVALID_MAX_MEALS;
	}
	else
		table->limit_meals = INFINITE_MEALS;
	if (table->time_to_die < (60 * 1000) || table->time_to_eat < (60 * 1000)
		|| table->time_to_sleep < (60 * 1000) || table->total_philos <= 0
		|| table->limit_meals == -2)
	{
		printf("Invalid arguments to start the simulation\n");
		return (-1);
	}
	return (0);
}
