/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:29:33 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/12 23:15:11 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_ack = 0;

static void	ack_handler(int sig)
{
	(void)sig;
	g_ack = 1;
}

static void	send_char(__pid_t pid, char c)
{
	int	i;
	int	attempts;

	attempts = 0;
	i = 0;
	while (i < 8)
	{
		g_ack = 0;
		if ((c >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		while (!g_ack)
		{
			if (kill(pid, 0) == -1 || attempts > 200)
			{
				write(2, "\nError: Server is not responding\n", 33);
				exit(1);
			}
			else
				usleep(5000);
			attempts++;
		}
		i++;
	}
}

static int	setup_sigaction(void)
{
	struct sigaction	sa;

	sa.sa_handler = ack_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		write(2, "Sigaction Failed\n", 17);
		return (1);
	}
	return (0);
}

static int	validate_args(int argc, char **argv, __pid_t *pid, const char **msg)
{
	if (argc != 3)
	{
		write(2, "Usage: ./client <PID(Numeric)> <MESSAGE>\n", 41);
		return (1);
	}
	if (!is_numeric(argv[1]))
	{
		write(2, "Error: PID must be numeric\n", 27);
		return (1);
	}
	*pid = ft_atoi(argv[1]);
	if (*pid <= 1 || kill(*pid, 0) == -1)
	{
		write(2, "Error: Invalid PID\n", 19);
		return (1);
	}
	*msg = argv[2];
	return (0);
}

int	main(int argc, char **argv)
{
	__pid_t		pid;
	const char	*msg;

	if (validate_args(argc, argv, &pid, &msg) != 0)
		return (1);
	if (setup_sigaction() != 0)
		return (1);
	while (*msg)
	{
		send_char(pid, *msg);
		msg++;
	}
	send_char(pid, '\0');
	return (0);
}
