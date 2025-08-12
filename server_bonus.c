/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 00:03:41 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/13 00:23:23 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_msg	g_msg = {NULL, 0, 0, 0};

static void	reset_message(void)
{
	free(g_msg.str);
	g_msg.str = NULL;
	g_msg.bit_count = 0;
	g_msg.c = 0;
}

static void	append_char(char **str, char c)
{
	size_t	len;
	char	*new_buf;

	len = 0;
	if (*str)
		len = ft_strlen(*str);
	new_buf = malloc(len + 2);
	if (!new_buf)
	{
		write(2, "Allocation error\n", 17);
		exit(1);
	}
	if (*str)
	{
		ft_memcpy(new_buf, *str, len);
		free(*str);
	}
	new_buf[len] = c;
	new_buf[len + 1] = '\0';
	*str = new_buf;
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (g_msg.client_pid != info->si_pid)
	{
		g_msg.client_pid = info->si_pid;
		reset_message();
	}
	if (sig == SIGUSR2)
		g_msg.c |= (1 << g_msg.bit_count);
	g_msg.bit_count++;
	if (g_msg.bit_count == 8)
	{
		if (g_msg.c == '\0')
		{
			ft_printf("Message reçu : %s\n", g_msg.str ? g_msg.str : "");
			kill(g_msg.client_pid, SIGUSR2);
			reset_message();
		}
		else
			append_char(g_msg.c);
		g_msg.c = 0;
		g_msg.bit_count = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID : %d\n", getpid());
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	while (1)
		pause();
}
