/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:55:19 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/07 08:12:54 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stddef.h>

int		ft_printf(const char *format, ...);
int		ft_print_char(int c);
int		ft_print_pointer(unsigned long ptr);
int		ft_print_int(int d);
int		ft_print_hex(unsigned int n, const char format);
int		ft_print_string(char *str);
int		ft_print_unsigned(unsigned int n);
int		ft_check(char c, va_list args);
int		ft_putnbr(int n);
void	ft_putchar(char c);
int		ft_putstr(char *str);
size_t	ft_stlen(const char *str);

#endif
