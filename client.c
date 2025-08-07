/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:29:33 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/07 08:44:18 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile	sig_atomic_t ack = 0;
void	ack_handler(int sig)
{
	(void)sig;
	ack = 1;
}

void	wait_ack()
{
	while (!ack)
		pause();
	ack = 0;
}

void	send_character(__pid_t pid, char c)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		wait_ack();
		usleep(50);
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Usage: %s <PID> <message>\n", argv[0]);
		return 1;
    }
	__pid_t pid = ft_atoi(argv[1]);
	const char *msg = argv[2];
	struct sigaction sa;
	sa.sa_handler = ack_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	while (*msg)
	{
		send_character(pid, *msg);
		msg++;
	}
	send_character(pid, '\0');
	return 0;
}
