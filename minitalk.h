/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:30:07 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/13 00:04:20 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include "ft_printf/ft_printf.h"

typedef struct s_msg
{
	char	*str;
	int		bit_count;
	char	c;
	__pid_t	client_pid;
}	t_msg;

size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_atoi(char const *str);
int		is_numeric(const char *str);

#endif
