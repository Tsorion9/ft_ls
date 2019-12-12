/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:38:56 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/12 15:20:13 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ft_strdup_s_e(char *s, int start, int end)
{
	char	*ret;
	int		i;

	ret = (char*)malloc(sizeof(char) * (end - start + 1));
	i = 0;
	while (start < end)
	{
		ret[i] = s[start];
		i++;
		start++;
	}
	ret[i] = '\0';
	return (ret);
}

int			count_of_digits(int a)
{
	int		count;

	count = 0;
	if (a == 0)
		return (1);
	while (a != 0)
	{
		a /= 10;
		count++;
	}
	return (count);
}

void		fill_nlinkd_sized(t_file *file, int *nlinkdig, int *sizedig)
{
	*nlinkdig = 0;
	*sizedig = 0;
	while (file != NULL)
	{
		if (count_of_digits(file->nlink) > *nlinkdig)
			*nlinkdig = count_of_digits(file->nlink);
		if (count_of_digits(file->size) > *sizedig)
			*sizedig = count_of_digits(file->size);
		file = file->next;
	}
}

char		*get_path(char *file)
{
	char	*path;
	int		i;

	i = ft_strlen(file) - 1;
	if (ft_strchr(file, '/') != NULL)
	{
		while (file[i] != '/')
			i--;
		path = ft_strsub(file, 0, i + 1);
	}
	else
	{
		path = (char*)malloc(sizeof(char) * 3);
		path[0] = '.';
		path[1] = '/';
		path[2] = '\0';
	}
	return (path);
}

void		new_filename(t_file *file, char *filepath)
{
	char	*path;
	char	*temp;

	path = get_path(filepath);
	while (file != NULL)
	{
		temp = ft_strjoin(path, file->name);
		if (ft_strcmp(filepath, temp) == 0)
		{
			free(file->name);
			free(temp);
			free(path);
			file->name = ft_strdup(filepath);
			return ;
		}
		free(temp);
		file = file->next;
	}
	free(path);
}
