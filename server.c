/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:29:50 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/08 13:36:55 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

typedef struct s_msg
{
	char	*str;
	int		bit_count;
	char	c;
	pid_t	client_pid;
}	t_msg;

t_msg g_msg = {NULL, 0, 0, 0};

void reset_message(void)
{
	free(g_msg.str);
	g_msg.str = NULL;
	g_msg.bit_count = 0;
	g_msg.c = 0;
}

void append_char(char c)
{
	size_t len = g_msg.str ? strlen(g_msg.str) : 0;
	char *new_buf = malloc(len + 2);
	if (!new_buf)
	{
		write(2, "Allocation error\n", 17);
		exit(1);
	}
	if (g_msg.str)
	{
		memcpy(new_buf, g_msg.str, len);
		free(g_msg.str);
	}
	new_buf[len] = c;
	new_buf[len + 1] = '\0';
	g_msg.str = new_buf;
}

void handler(int sig, siginfo_t *info, void *context)
{
	(void)context;

	if (g_msg.client_pid != info->si_pid)
	{
		g_msg.client_pid = info->si_pid;
		reset_message();
	}

	if (sig == SIGUSR2) // bit = 1
		g_msg.c |= (1 << g_msg.bit_count);
	g_msg.bit_count++;

	if (g_msg.bit_count == 8)
	{
		if (g_msg.c == '\0')
		{
			printf("Message reçu : %s\n", g_msg.str ? g_msg.str : "");
			fflush(stdout);
			reset_message();
		}
		else
		{
			append_char(g_msg.c);
		}
		g_msg.c = 0;
		g_msg.bit_count = 0;
	}

	kill(info->si_pid, SIGUSR1);
}

int main(void)
{
	struct sigaction sa;

	printf("Serveur PID : %d\n", getpid());

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGUSR1, &sa, NULL) == -1 ||
		sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		perror("sigaction");
		return 1;
	}

	while (1)
		pause();
}
