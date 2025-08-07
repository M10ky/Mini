/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:30:07 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/07 08:45:18 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct s_receive
{
	char	*message;
	size_t	bit_count;
	char	current_char;
	__pid_t	client_pid;
}t_receive;

int		ft_atoi(char const *str);
size_t	ft_strlen(const char *str);

#endif
