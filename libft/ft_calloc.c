/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpichon <gpichon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:07:33 by gpichon           #+#    #+#             */
/*   Updated: 2024/11/18 18:39:53 by gpichon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmeb, size_t n)
{
	char	*tab;
	size_t	i;

	i = 0;
	if ((nmeb * n) > (size_t) - 1)
		return (NULL);
	tab = (char *)malloc(n * nmeb);
	if (!tab)
		return (NULL);
	while (i < nmeb * n)
		tab[i++] = '\0';
	return (tab);
}
