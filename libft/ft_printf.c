/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:39:58 by totake            #+#    #+#             */
/*   Updated: 2025/07/17 17:37:37 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_handle_format(char spec, va_list *args)
{
	if (spec == 'c')
		return (ft_printchar(va_arg(*args, int)));
	else if (spec == 's')
		return (ft_printstr(va_arg(*args, char *)));
	else if (spec == 'd' || spec == 'i')
		return (ft_printnbr((long)va_arg(*args, int)));
	else if (spec == 'u')
		return (ft_printunbr(va_arg(*args, unsigned int)));
	else if (spec == 'x')
		return (ft_printhex(va_arg(*args, unsigned int), "0123456789abcdef"));
	else if (spec == 'X')
		return (ft_printhex(va_arg(*args, unsigned int), "0123456789ABCDEF"));
	else if (spec == 'p')
		return (ft_printptr((uintptr_t)va_arg(*args, void *),
				"0123456789abcdef", 1));
	else if (spec == '%')
		return (ft_printchar('%'));
	return (0);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		total;

	if (!fmt)
		return (-1);
	total = 0;
	va_start(args, fmt);
	while (*fmt)
	{
		if (*fmt == '%' && *(fmt + 1))
		{
			fmt++;
			total += ft_handle_format(*fmt, &args);
		}
		else
			total += ft_printchar(*fmt);
		fmt++;
	}
	va_end(args);
	return (total);
}
