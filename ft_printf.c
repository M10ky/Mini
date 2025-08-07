/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:01:51 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/07 08:12:54 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	va_list(args);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += ft_check(format[i + 1], args);
			i = i + 1;
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
