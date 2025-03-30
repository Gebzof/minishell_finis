/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpichon <gpichon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:06:26 by gpichon           #+#    #+#             */
/*   Updated: 2024/11/17 00:22:54 by gpichon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	initial_len_src;
	size_t	initial_len_dest;

	i = 0;
	initial_len_src = ft_strlen(src);
	initial_len_dest = ft_strlen(dest);
	if (size <= ft_strlen(dest) || size == 0)
		return (initial_len_src + size);
	while (src[i] && (i + initial_len_dest + 1) < size)
	{
		dest[initial_len_dest + i] = src[i];
		i++;
	}
	dest[initial_len_dest + i] = '\0';
	return (initial_len_src + initial_len_dest);
}
