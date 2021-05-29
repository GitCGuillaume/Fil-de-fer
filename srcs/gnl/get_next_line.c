/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchopin <gchopin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 23:35:16 by gchopin           #+#    #+#             */
/*   Updated: 2021/05/29 18:57:58 by gchopin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

int	clear_memory(char **str, char **str_two)
{
	if (str)
	{
		free(*str);
		*str = NULL;
	}
	if (str_two)
	{
		free(*str_two);
		*str_two = NULL;
	}
	return (-1);
}

int	len_n(char *str, int *res)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i] != '\n' && str[i] != '\0')
			i++;
		if (str[i] == '\n')
		{
			if (res)
				*res = 1;
			i++;
		}
	}
	return (i);
}

int	get_last_n(char **line, char **m_ln, int *res)
{
	char	*m_tmp;

	if (!m_ln)
		return (clear_memory(0, line));
	if (!*m_ln || *m_ln[0] == '\0')
		m_tmp = ft_substr_g(*line, 0, ft_len(*line));
	else
		m_tmp = ft_substr_g(*m_ln, 0, ft_len(*m_ln));
	if (m_tmp == NULL)
		return (clear_memory(line, m_ln));
	free(*m_ln);
	*m_ln = m_tmp;
	m_tmp = ft_strdup_g(*m_ln);
	if (m_tmp == NULL)
		return (clear_memory(line, m_ln));
	free(*line);
	*line = m_tmp;
	m_tmp = ft_substr_g(*m_ln, len_n(*m_ln, res), ft_len(*m_ln));
	if (m_tmp == NULL)
		return (clear_memory(line, m_ln));
	free(*m_ln);
	*m_ln = m_tmp;
	if (*m_ln == NULL || *m_ln[0] == 0 || *res == -1 || *res == 0)
		clear_memory(m_ln, 0);
	return (*res);
}

int	read_line(int fd, char **line, char **mem_line)
{
	char	buff[BUFFER_SIZE + 1];
	char	*tmp;
	int		ret;

	free(*line);
	*line = ft_strdup_g("");
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret < 0)
			return (clear_memory(line, mem_line));
		buff[ret] = '\0';
		tmp = ft_strjoin_g(*line, buff);
		if (tmp == NULL)
			return (clear_memory(line, 0));
		free(*line);
		*line = tmp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (ret == -1)
		return (clear_memory(line, mem_line));
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	static char	*m_line;
	char		*mem_tmp;
	int			res;

	if (BUFFER_SIZE < 1 || fd < 0 || !line)
		return (-1);
	*line = NULL;
	if (m_line && m_line[0] != 0 && ft_strchr(m_line, '\n') != 0)
		return (get_last_n(line, &m_line, &res));
	res = read_line(fd, line, &m_line);
	if (res != -1)
	{
		if (m_line && m_line[0] != 0 && !ft_strchr(m_line, '\n'))
		{
			mem_tmp = ft_strjoin_g(m_line, *line);
			if (mem_tmp == NULL)
				return (clear_memory(line, &m_line));
			free(m_line);
			m_line = mem_tmp;
		}
		res = get_last_n(line, &m_line, &res);
	}
	if (*line == NULL || res == -1)
		return (clear_memory(line, &m_line));
	return (res);
}
