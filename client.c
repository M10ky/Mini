/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:29:33 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/08 13:46:20 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t ack = 0; // Variable globale de synchronisation

void ack_handler(int sig)
{
	(void)sig;
	ack = 1; // Le serveur a confirmé réception du bit
}

void send_char(pid_t pid, char c)
{
    int i = 0;
    while (i < 8)
    {
        ack = 0; // Réinitialiser l’ACK avant chaque bit

        if ((c >> i) & 1)
            kill(pid, SIGUSR2); // bit = 1
        else
            kill(pid, SIGUSR1); // bit = 0

        int attempts = 0;
        while (!ack)
        {
            // Vérifier si le serveur est toujours vivant
            if (kill(pid, 0) == -1)
            {
                write(2, "\nError: Server is not responding\n", 33);
                exit(1);
            }

            // Attente courte avant de réessayer
            usleep(5000); // 5 ms

            // Timeout après ~1 seconde
            if (++attempts > 200)
            {
                write(2, "\nError: No ACK from server\n", 28);
                exit(1);
            }
        }
        i++;
    }
}


int is_numeric(const char *str)
{
    while (*str)
    {
        if (*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        write(2, "Usage: ./client <PID> <MESSAGE>\n", 33);
        return 1;
    }

    if (!is_numeric(argv[1]))
    {
        write(2, "Error: PID must be numeric\n", 28);
        return 1;
    }

    pid_t pid = atoi(argv[1]);
    if (pid <= 1 || kill(pid, 0) == -1)
    {
        write(2, "Error: Invalid PID\n", 20);
        return 1;
    }

    // Associer SIGUSR1 au handler ACK
    struct sigaction sa;
    sa.sa_handler = ack_handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        perror("sigaction");
        return 1;
    }

    const char *msg = argv[2];
    while (*msg)
    {
        send_char(pid, *msg);
        msg++;
    }
    send_char(pid, '\0');

    return 0;
}
