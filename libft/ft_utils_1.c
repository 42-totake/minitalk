/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:31:37 by totake            #+#    #+#             */
/*   Updated: 2025/07/17 17:37:55 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_printstr(const char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (*s)
		len += write(1, s++, 1);
	return (len);
}

int	ft_printnbr(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
		count += ft_printnbr(n / 10);
	count += ft_printchar('0' + (n % 10));
	return (count);
}

int	ft_printunbr(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_printunbr(n / 10);
	count += ft_printchar('0' + (n % 10));
	return (count);
}
