/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:33:53 by vbackyet          #+#    #+#             */
/*   Updated: 2021/10/22 19:38:47 by vbackyet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*helloWorld(void *mutexe_and_philosophers)
{
	t_ph_and_mut	*mp;

	mp = (t_ph_and_mut *)mutexe_and_philosophers;
	mp->philo.time_of_last_action_end = get_time_ms();
	while (1)
	{
		eat_the_food(&mp->philo, mp->mutexes, mp->game);
		if (mp->game.number_of_each_philosopher_must_eat != -1)
			mp->game.number_of_each_philosopher_must_eat--;
		sleeping(&mp->philo, mp->game, mp->mutexes);
		ft_printf(&mp->mutexes[mp->game.num], mp->philo.num_of_philo, \
	mp->game.time_strt, 1);
	}
	return (NULL);
}

void	*philosoph_podoh(void *mutexe_and_philosophers)
{
	int				i;
	t_ph_and_mut	*mp;

	mp = (t_ph_and_mut *)mutexe_and_philosophers;
	while (1)
	{
		i = 0;
		while (i < mp[0].game.num)
		{
			if ((get_time_ms() - \
			mp[i].philo.time_of_last_action_end) > mp[0].game.time_to_die)
			{
				ft_printf(&mp->mutexes[mp->game.num], mp[i].philo.num_of_philo, \
	mp->game.time_strt, 2);
				exit(0);
			}
			i++;
		}
	}
	return (NULL);
}

void	*ph_round(void *mutexe_and_philosophers)
{
	t_ph_and_mut	*mp;
	int				i;
	int				flag;

	mp = (t_ph_and_mut *)mutexe_and_philosophers;
	if (mp[0].game.number_of_each_philosopher_must_eat != -1)
	{
		while (1)
		{
			i = -1;
			flag = 1;
			while (++i < mp[0].game.num)
			{
				if (mp[i].game.number_of_each_philosopher_must_eat > 0)
					flag = 0;
			}
			if (flag)
			{
				ft_printf(&mp->mutexes[mp->game.num], 9, \
				 mp->game.time_strt, 0);
			}
		}
	}
	return (NULL);
}

t_player	init_the_philo(int philo, int number_of_all)
{
	t_player	player;	
	int			num_ph;
	int			prev;
	int			next;

	player.num_of_philo = philo;
	num_ph = philo;
	if ((num_ph == number_of_all) || (num_ph == 1))
	{
		prev = num_ph - 1;
		next = num_ph;
		if (num_ph == 1)
			prev = number_of_all;
	}
	else
	{
		prev = num_ph - 1;
		next = num_ph;
	}
	player.prev = prev;
	player.next = next;
	player.flag = 1;
	return (player);
}

int	main(int argc, char **argv)
{
	pthread_t			*threads;
	t_ph_and_mut		*bag;
	pthread_mutex_t		*m;
	t_game				game;

	init_the_game(argc, argv, &game, 0);
	threads = (pthread_t *)malloc((f_a(argv[1]) + 2) * sizeof(pthread_t));
	m = (pthread_mutex_t *)malloc((f_a(argv[1]) + 1) * sizeof(pthread_mutex_t));
	bag = (t_ph_and_mut *)malloc((f_a(argv[1])) * sizeof(t_ph_and_mut));
	check_thread(argc, threads, bag, m);
	while (++game.philo <= game.num)
		pthread_mutex_init(&m[game.philo], NULL);
	while (++game.i <= game.num - 1)
	{
		bag[game.i].philo = init_the_philo(game.the_turn[game.i], game.num);
		bag[game.i].mutexes = m;
		bag[game.i].game = game;
		pthread_create(&threads[game.the_turn[game.i] - 1], NULL, helloWorld, \
		 (void *)&bag[game.i]);
		usleep(1);
	}
	pthread_create(&threads[game.num], NULL, philosoph_podoh, (void *)bag);
	pthread_create(&threads[game.num + 1], NULL, ph_round, (void *) bag);
	make_join_and_free(threads, &game, bag, m);
	return (0);
}
