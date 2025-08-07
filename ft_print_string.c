/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:01:45 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/07 08:12:51 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_string(char *str)
{
	if (str == NULL)
	{
		ft_putstr("(null)");
		return (6);
	}
	else
		ft_putstr(str);
	return (ft_stlen(str));
}
