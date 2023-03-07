/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukanie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:38:08 by tlukanie          #+#    #+#             */
/*   Updated: 2023/03/07 13:06:41 by tlukanie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

static void	confirmation_msg(int sig)
{
	if (sig == SIGUSR1)
		signal(SIGUSR1, confirmation_msg);
	else if (sig == SIGUSR2)
	{
		ft_printf("Message recieved!\n");
		exit(0);
	}
}

void	send_signal(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (1 << bit)))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(500);
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	pid = ft_atoi(argv[1]);
	i = 0;
	if (argc != 3 || (ft_atoi(argv[1]) < 1) || (ft_strlen(argv[2]) < 1))
		ft_printf("Error (client)!\n");
	else
	{
		while (argv[2][i])
		{
			send_signal(pid, argv[2][i]);
			i++;
		}
		signal(SIGUSR2, confirmation_msg);
		signal(SIGUSR1, confirmation_msg);
		send_signal(pid, '\0');
	}
	return (0);
}
