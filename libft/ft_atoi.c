/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 16:43:07 by gchopin           #+#    #+#             */
/*   Updated: 2021/05/30 10:52:40 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_tab(char c)
{
	if (c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}

static int	is_jump(char c)
{
	if (c == '\n' || c == '\r')
		return (1);
	else
		return (0);
}

static int	is_other(char c)
{
	if (c == '\f' || c == ' ')
		return (1);
	else
		return (0);
}

ssize_t	ft_atoi(const char *str)
{
	int		i;
	ssize_t	result;
	ssize_t	symbol;

	i = 0;
	result = 0;
	symbol = 1;
	while (is_tab(str[i]) || is_jump(str[i]) || is_other(str[i]))
		i++;
	if (str[i] == '-')
	{
		symbol = -symbol;
	}
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (symbol * result);
}
