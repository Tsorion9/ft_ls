/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_user_files_sup.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:15:45 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/12 15:07:23 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			count_file(t_file *file)
{
	int	i;

	i = 0;
	if (file != NULL)
		while (file != NULL)
		{
			file = file->next;
			i++;
		}
	return (i);
}

void		print_such_file(char *file_name)
{
	write(1, "ft_ls: ", 7);
	ft_putstr(file_name);
	write(1, ": No such file or directory\n", 28);
}

char		*seach_file_sup(char *filepath)
{
	int		i;
	char	*file_name;

	i = ft_strlen(filepath) - 1;
	if (ft_strchr(filepath, '/') != NULL)
	{
		while (filepath[i] != '/')
			i--;
		file_name = ft_strdup(filepath + i + 1);
	}
	else
		file_name = ft_strdup(filepath);
	return (file_name);
}

t_file		*seach_file_sup1(t_file *file, char *filepath, \
	char *flags, DIR *dir)
{
	struct stat		statbuf;
	struct dirent	*dirent;
	char			*file_name;

	file_name = seach_file_sup(filepath);
	dirent = readdir(dir);
	while (dirent != NULL)
	{
		if (ft_strcmp(file_name, dirent->d_name) == 0)
		{
			lstat(filepath, &statbuf);
			if (ft_strchr(flags, 't') == NULL)
				file = add_file(file, dirent, statbuf, filepath);
			else
				file = add_file_t(file, dirent, statbuf);
			break ;
		}
		dirent = readdir(dir);
	}
	if (dirent != NULL)
		new_filename(file, filepath);
	free(file_name);
	return (file);
}

t_file		*search_file(DIR *dir, t_file *file, char *filepath, char *flags)
{
	int	count;

	if (dir == NULL)
	{
		print_such_file(filepath);
		return (file);
	}
	count = count_file(file);
	file = seach_file_sup1(file, filepath, flags, dir);
	if (count == count_file(file))
		print_such_file(filepath);
	return (file);
}
