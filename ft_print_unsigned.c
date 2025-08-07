/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:01:48 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/07 08:12:52 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchr(char c)
{
	return (write(1, &c, 1));
}

static int	ft_putnbr_unsigned(unsigned int n)
{
	int	len;

	len = 0;
	if (n >= 10)
		len += ft_putnbr_unsigned(n / 10);
	len += ft_putchr((n % 10) + '0');
	return (len);
}

int	ft_print_unsigned(unsigned int n)
{
	return (ft_putnbr_unsigned(n));
}
