/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 00:03:41 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/13 08:31:06 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	reset_message(char **str, int *bit_count, char *c)
{
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
	*bit_count = 0;
	*c = 0;
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

static void	process_byte(char **str, char *c, int *bit_count, __pid_t pid)
{
	if (*c == '\0')
	{
		kill(pid, SIGUSR2); // Confirmation finale
		if (*str != NULL && **str != '\0')
		{
			ft_printf("%s", *str);
			usleep(5000); // Laisser le temps au client de finir l'envoi
		}
		reset_message(str, bit_count, c);
	}
	else
		append_char(str, *c);
	*c = 0;
	*bit_count = 0;
}


static void	ft_handler(int sig, siginfo_t *info, void *context)
{
	static char		*str;
	static int		bit_count;
	static char		c;
	static __pid_t	client_pid;

	(void)context;
	if (client_pid != info->si_pid)
	{
		client_pid = info->si_pid;
		reset_message(&str, &bit_count, &c);
	}
	if (sig == SIGUSR2)
		c |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
		process_byte(&str, &c, &bit_count, info->si_pid);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID : %d\n", getpid());
	sa.sa_sigaction = ft_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(2, "Sigaction Failed\n", 17);
		return (1);
	}
	while (1)
		pause();
}
