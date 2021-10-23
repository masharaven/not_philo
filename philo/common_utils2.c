/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbackyet <vbackyet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:34:16 by vbackyet          #+#    #+#             */
/*   Updated: 2021/10/22 19:50:16 by vbackyet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_str_isdigit(char *c)
{
	int	i;

	i = 0;
	while (*c)
	{
		if (*c < '0' || *c > '9')
			return (0);
		c++;
	}
	return (1);
}

void	check_args(int argc, char **argv)
{
	int			i;

	i = 1;
	if (argc < 5 || argc > 6 )
	{
		write(1, "Wrong number of arguments\n", 26);
		exit(1);
	}
	while (i < argc)
	{
		if (!(ft_str_isdigit(argv[i])))
		{
			write(1, "Arguments are invalid\n", 23);
			exit(1);
		}
		i++;
	}
}

void	init_the_game(int argc, char **argv, t_game *game, int flag)
{
	sem_t		*sem;

	check_args(argc, argv);
	if (flag)
	{
		sem_unlink("mysemaphore8");
		sem = sem_open("mysemaphore8", O_CREAT, 0644, 1);
		game->mut_for_bonus = sem;
	}	
	game->num = f_a(argv[1]);
	game->time_to_die = f_a(argv[2]);
	game->time_to_eat = f_a(argv[3]);
	game->time_to_sleep = f_a(argv[4]);
	game->philo = -1;
	game->i = -1;
	if (flag)
		game->the_turn = create_turn_for_bonus(game->num);
	else
		game->the_turn = create_turn(game->num);
	game->time_strt = get_time_ms();
	if (argc == 6)
		game->number_of_each_philosopher_must_eat = f_a(argv[5]);
	else
		game->number_of_each_philosopher_must_eat = -1;
}

int	check(int argc, t_ph_and_mut	*bag, int *pid_array)
{
	if (argc < 5 || argc > 6 )
	{
		write(1, "Wrong number of arguments\n", 30);
		exit(1);
	}
	if (!(bag || pid_array))
	{
		write(1, "Malloc error! \n", 30);
		exit(1);
	}
	return (0);
}

void	join_nad_free(t_game *game, t_ph_and_mut *bag, \
int *pid_array, sem_t *semaphore)
{
	int	status;
	int	sum;

	sum = game->num;
	if (game->number_of_each_philosopher_must_eat == -1)
		sum = 42;
	game->i = -1;
	while (sum > 0)
	{
		waitpid(P_ALL, &status, 0);
		if (status != 0)
			sum--;
		else
			sum = 0;
	}
	sem_close(semaphore);
	free(bag);
	free(pid_array);
	game->i = -1;
	while (++game->i < game->num)
		kill(pid_array[game->i], SIGKILL);
}
