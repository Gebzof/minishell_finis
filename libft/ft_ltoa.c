/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpichon <gpichon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:03:12 by mprokosc          #+#    #+#             */
/*   Updated: 2025/03/26 15:27:28 by gpichon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	len(long n)
{
	long			l;
	unsigned long	nb;

	l = 1;
	if (n < 0)
		nb = (unsigned long)(-n);
	else
		nb = (unsigned long)n;
	while (nb >= 10)
	{
		l++;
		nb /= 10;
	}
	return (l + (n < 0));
}

char	*ft_ltoa(long n)
{
	char			*str;
	unsigned long	nb;
	long			lentab;

	lentab = len(n);
	str = (char *)calloc(lentab + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		nb = (unsigned long)(-n);
	}
	else
		nb = (unsigned long)n;
	while (lentab-- > (n < 0))
	{
		str[lentab] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}
