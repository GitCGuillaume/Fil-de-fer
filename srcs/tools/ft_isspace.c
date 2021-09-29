/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 01:57:59 by gchopin           #+#    #+#             */
/*   Updated: 2021/06/16 01:58:17 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_tab(char c)
{
	if (c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}

int	is_jump(char c)
{
	if (c == '\n' || c == '\r')
		return (1);
	else
		return (0);
}

int	is_other(char c)
{
	if (c == '\f' || c == ' ')
		return (1);
	else
		return (0);
}
