/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:01:39 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/07 08:12:49 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchr(char c)
{
	return (write(1, &c, 1));
}

int	ft_putnbr(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		len += ft_putchr('-');
		n = -n;
	}
	if (n >= 10)
		len += ft_putnbr(n / 10);
	len += ft_putchr((n % 10) + '0');
	return (len);
}

int	ft_print_int(int d)
{
	return (ft_putnbr(d));
}
