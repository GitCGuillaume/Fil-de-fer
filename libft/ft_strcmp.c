/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:12:28 by gchopin           #+#    #+#             */
/*   Updated: 2021/11/05 14:12:29 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (str1 && str2)
	{
		while ((str1[i] != '\0' || str2[i] != '\0'))
		{
			if (str1[i] - str2[i] != 0)
			{
				return (str1[i] - str2[i]);
			}
			i++;
		}
		if (str1[i] - str2[i] == 0)
			return (str1[i] - str2[i]);
	}
	return (0);
}
