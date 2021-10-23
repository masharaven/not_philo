/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 19:52:08 by vbackyet          #+#    #+#             */
/*   Updated: 2021/10/22 19:52:10 by vbackyet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_thread(int argc, pthread_t *bugaga, \
	t_ph_and_mut *bag, pthread_mutex_t *mutexes)
{
	if (argc < 5 || argc > 6 )
	{
		write(1, "Wrong number of arguments\n", 30);
		exit(1);
	}
	if (!(bugaga || bag || mutexes))
	{
		write(1, "Malloc error\n", 15);
		exit(1);
	}
	return (0);
}

void	make_join_and_free(pthread_t *threads, \
t_game *game, t_ph_and_mut *bag, pthread_mutex_t *m)
{
	int	i;

	i = 0;
	while (i < game->num)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	i = 0;
	while (i < game->num)
	{
		pthread_mutex_destroy(&m[i]);
		i++;
	}
	free(game->the_turn);
	free(threads);
	free(bag);
	free(m);
}

char	*ft_strdup(char *src)
{
	int		i;
	int		len;
	char	*str;

	len = 0;
	while (src[len])
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

int	ft_printf(pthread_mutex_t *mutex, int who, long int time, int text)
{
	char	*textic;

	pthread_mutex_lock(mutex);
	if (text == 1)
		textic = ft_strdup("is thinking");
	else if (text == 2)
		textic = ft_strdup("is dead");
	else if (text == 3)
		textic = ft_strdup("has taken forks");
	else if (text == 4)
		textic = ft_strdup("is eating");
	else if (text == 5)
		textic = ft_strdup("is sleeping");
	else
		textic = ft_strdup("круги закончились");
	printf("%li - %i %s\n", get_time_ms() - time, who, textic);
	free(textic);
	if (text == 2 || text == 0)
	{
		if (text == 2)
			pthread_mutex_destroy(mutex);
		exit(0);
	}
	pthread_mutex_unlock(mutex);
	return (0);
}

int	ft_printf_for_bonus(sem_t *sem, int who, long int time, int text)
{
	char	*textic;

	sem_wait(sem);
	if (text == 1)
		textic = ft_strdup("is thinking");
	else if (text == 2)
		textic = ft_strdup("is dead");
	else if (text == 3)
		textic = ft_strdup("has taken forks");
	else if (text == 4)
		textic = ft_strdup("is eating");
	else if (text == 5)
		textic = ft_strdup("is sleeping");
	else
		textic = ft_strdup("круги закончились");
	printf("%li - %i %s\n", get_time_ms() - time, who, textic);
	free(textic);
	if (text == 2)
	{
		sem_close(sem);
		exit(0);
	}
	sem_post(sem);
	return (0);
}
