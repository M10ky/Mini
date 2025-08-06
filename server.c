/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokyrakotoarivelo@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:29:50 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/06 22:45:33 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_receive g_data = {NULL, 0, 0, 0};

void append_char(char c)
{
    size_t old_len = 0;
    char *new_msg;

    if (g_data.message)
        old_len = strlen(g_data.message);

    new_msg = malloc(sizeof(char) * (old_len + 2)); // +1 pour c, +1 pour \0
    if (!new_msg)
        exit(EXIT_FAILURE);

    if (g_data.message)
    {
        strcpy(new_msg, g_data.message);
        free(g_data.message);
    }
    else
        new_msg[0] = '\0';

    new_msg[old_len] = c;
    new_msg[old_len + 1] = '\0';
    g_data.message = new_msg;
}

void handler(int sig, siginfo_t *info, void *context)
{
    (void)context;
    g_data.client_pid = info->si_pid;
    if (sig == SIGUSR2)
        g_data.current_char |= (1 << g_data.bit_count);
    g_data.bit_count++;
    if (g_data.bit_count == 8)
    {
        append_char(g_data.current_char);
        if (g_data.current_char == '\0')
        {
            printf("Message reçu : %s\n", g_data.message);
            free(g_data.message);
            g_data.message = NULL;
        }
        g_data.bit_count = 0;
        g_data.current_char = 0;
    }
    kill(g_data.client_pid, SIGUSR1);
}

int main(void)
{
    struct sigaction sa;

    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO | SA_RESTART;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    printf("PID du serveur : %d\n", getpid());

    while (1)
        pause();
}
