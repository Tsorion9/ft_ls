/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_user_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:57:38 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/12 14:24:59 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir		*create_dir(char *dir_name, t_file *file, struct stat statbuf)
{
	t_dir	*dir;

	dir = (t_dir*)malloc(sizeof(t_dir));
	if (dir != NULL)
	{
		dir->name = ft_strdup(dir_name);
		dir->file = file;
		dir->date_mode = statbuf.st_mtimespec;
		dir->next = NULL;
	}
	return (dir);
}

void		print_user_dir(char *flags, char **files, t_file *file)
{
	DIR			*dir;
	t_dir		*user_dir;
	struct stat	statbuf;
	int			i;

	i = 0;
	user_dir = NULL;
	while (files[i] != NULL)
	{
		dir = opendir(files[i]);
		if (dir != NULL)
		{
			lstat(files[i], &statbuf);
			if (ft_strchr(flags, 't') == NULL)
				user_dir = add_dir(user_dir, files[i], \
				get_t_file(dir, flags, files[i]), statbuf);
			else
				user_dir = add_dir_t(user_dir, files[i], \
				get_t_file(dir, flags, files[i]), statbuf);
			closedir(dir);
		}
		i++;
	}
	user_dir = print_user_dir_sup2(flags, user_dir, file);
	free_all_dir(user_dir);
}

void		print_user_files_sup(char *flags, char **files, t_file *file)
{
	if (file != NULL)
	{
		if (ft_strchr(flags, 'r') != NULL)
			print_all_files(reverse_list(file), flags, 0);
		else
			print_all_files(file, flags, 0);
	}
	print_user_dir(flags, files, file);
	free_all_file(file);
}

void		print_user_files(char *flags, char **files)
{
	DIR		*dir;
	t_file	*file;
	char	*path;
	int		i;

	file = NULL;
	i = 0;
	while (files[i] != NULL)
	{
		dir = opendir(files[i]);
		if (dir == NULL && files[i][ft_strlen(files[i]) - 1] != '/')
		{
			path = get_path(files[i]);
			dir = opendir(path);
			file = search_file(dir, file, files[i], flags);
			free(path);
		}
		if (dir != NULL)
			closedir(dir);
		i++;
	}
	print_user_files_sup(flags, files, file);
}
