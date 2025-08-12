/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 00:03:09 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/13 00:09:59 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_ack = 0;

static void	ack_handler(int sig)
{
	if (sig == SIGUSR1)
		g_ack = 1;
	else if (sig == SIGUSR2)
	{
		ft_printf("\n[OK] Message reçu avec succès par le serveur\n");
		exit(0);
	}
}

static void	send_char(__pid_t pid, char c)
{
	int	i;
	int	attempts;

	i = 0;
	while (i < 8)
	{
		g_ack = 0;
		if ((c >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		attempts = 0;
		while (!g_ack)
		{
			if (kill(pid, 0) == -1)
				exit(write(2, "Error: Server down\n", 19));
			usleep(5000);
			if (++attempts > 200)
			{
				write(2, "Error: No ACK\n", 14);
				exit(1);
			}
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	__pid_t				pid;
	char				*msg;

	if (argc != 3 || !is_numeric(argv[1]))
		return (write(2, "Usage: ./client <PID> <MESSAGE>\n", 33), 1);
	pid = ft_atoi(argv[1]);
	if (pid <= 1 || kill(pid, 0) == -1)
		return (write(2, "Error: Invalid PID\n", 19), 1);
	sa.sa_handler = ack_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (write(2, "Sigaction failed\n", 17), 1);
	msg = argv[2];
	while (*msg)
		send_char(pid, *msg++);
	send_char(pid, '\0');
	usleep(1000000);
	ft_printf("\n[FAIL] Message non confirmé par le serveur\n");
	return (1);
}
