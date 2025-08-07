/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:01:36 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/07 08:12:48 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchr(char c)
{
	return (write(1, &c, 1));
}

static int	ft_puthex(unsigned int n, const char format)
{
	int		len;
	char	*hex;

	len = 0;
	if (format == 'x')
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	if (n >= 16)
		len += ft_puthex(n / 16, format);
	len += ft_putchr(hex[n % 16]);
	return (len);
}

int	ft_print_hex(unsigned int n, const char format)
{
	return (ft_puthex(n, format));
}
