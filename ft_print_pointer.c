/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:01:42 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/07 08:12:50 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchr(char c)
{
	return (write(1, &c, 1));
}

static int	ft_print_hexa(unsigned long x)
{
	char	*hex;
	int		len;

	hex = "0123456789abcdef";
	len = 0;
	if (x >= 16)
		len = len + ft_print_hexa(x / 16);
	len = len + ft_putchr(hex[x % 16]);
	return (len);
}

int	ft_print_pointer(unsigned long ptr)
{
	int	len;

	len = 0;
	if (ptr == 0)
		len = len + write(1, "(nil)", 5);
	else
	{
		len = len + write(1, "0x", 2);
		len = len + ft_print_hexa(ptr);
	}
	return (len);
}
