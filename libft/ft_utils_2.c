/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totake <totake@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:31:37 by totake            #+#    #+#             */
/*   Updated: 2025/07/17 17:38:16 by totake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printhex(unsigned int n, char *base)
{
	char	buf[20];
	int		i;
	int		count;

	if (n == 0)
		return (write(1, "0", 1));
	i = 0;
	count = 0;
	while (n)
	{
		buf[i++] = base[n % 16];
		n /= 16;
	}
	while (--i >= 0)
		count += write(1, &buf[i], 1);
	return (count);
}

int	ft_printptr(uintptr_t n, char *base, int with_prefix)
{
	char	buf[20];
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (n == 0)
	{
		if (with_prefix)
			return (write(1, "(nil)", 5));
		else
			return (write(1, "0", 1));
	}
	while (n)
	{
		buf[i++] = base[n % 16];
		n /= 16;
	}
	if (with_prefix)
		count += write(1, "0x", 2);
	while (--i >= 0)
		count += write(1, &buf[i], 1);
	return (count);
}
