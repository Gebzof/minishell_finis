/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpichon <gpichon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:07:17 by gpichon           #+#    #+#             */
/*   Updated: 2024/11/18 12:12:04 by gpichon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int n)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((char)n == s[i])
			return ((char *)s + i);
		i++;
	}
	if ((char)n == '\0')
		return ((char *)s + i);
	return (NULL);
}
