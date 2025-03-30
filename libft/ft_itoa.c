/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpichon <gpichon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:10:09 by gpichon           #+#    #+#             */
/*   Updated: 2024/11/16 21:01:40 by gpichon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(int n)
{
	int				l;
	unsigned int	nb;

	l = 0;
	if (n <= 0)
	{
		nb = -n;
		l++;
	}
	else
		nb = n;
	while (nb > 0)
	{
		l++;
		nb = nb / 10;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	nb;
	int				lentab;
	int				i;

	lentab = len(n);
	str = ft_calloc(lentab + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		str[0] = '-';
		nb = -n;
		i = 1;
	}
	else
		nb = n;
	while (i < lentab)
	{
		lentab--;
		str[lentab] = (nb % 10 + '0');
		nb /= 10;
	}
	return (str);
}
