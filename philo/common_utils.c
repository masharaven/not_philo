/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:34:21 by vbackyet          #+#    #+#             */
/*   Updated: 2021/10/22 19:50:36 by vbackyet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tmp_time;
	long			ms;

	gettimeofday(&tmp_time, NULL);
	ms = tmp_time.tv_sec * 1000;
	ms += tmp_time.tv_usec / 1000;
	return (ms);
}

void	ft_usleep(size_t time)
{	
	long	r_time;

	r_time = get_time_ms() + time;
	while (get_time_ms() < r_time)
		usleep(50);
}

static int	skip_spaces(char *s, int i)
{
	while (s[i] == ' ' || (9 <= s[i] && s[i] <= 13) || s[i] == '\n')
		++i;
	return (i);
}

int	f_a(char *str)
{
	int	i;
	int	n;
	int	sign;

	n = 0;
	i = 0;
	sign = 1;
	i = skip_spaces(str, i);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '+')
			sign = 1;
		else
			sign = -1;
		++i;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		++i;
	}
	n = sign * n;
	return (n);
}

int	*create_turn_for_bonus(int num)
{
	int	*the_turn;
	int	n;

	n = 0;
	the_turn = malloc(num * sizeof(int));
	while (n < num)
	{
		the_turn[n] = n + 1;
		n++;
	}
	return (the_turn);
}
