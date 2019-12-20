/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 13:13:19 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/14 17:24:02 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		free_one_file(t_file *file)
{
	free(file->mode);
	free(file->uid);
	free(file->gid);
	free(file->name);
	if (file->lname != NULL)
		free(file->lname);
	free(file);
}

void		free_all_file(t_file *file)
{
	t_file	*head;

	head = file;
	if (file != NULL)
	{
		if (file->next == NULL)
		{
			free_one_file(file);
			return ;
		}
		while (file->next->next != NULL)
		{
			while (file->next->next != NULL)
				file = file->next;
			free_one_file(file->next);
			file->next = NULL;
			file = head;
		}
		free_one_file(file->next);
		file->next = NULL;
		free_one_file(file);
	}
}

void		free_strsplit(char **str)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i] != NULL)
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

void		free_one_dir(t_dir *user_dir)
{
	free(user_dir->name);
	free_all_file(user_dir->file);
	free(user_dir);
}

void		free_all_dir(t_dir *user_dir)
{
	t_dir	*head;

	head = user_dir;
	if (user_dir != NULL)
	{
		if (user_dir->next == NULL)
		{
			free_one_dir(user_dir);
			return ;
		}
		while (user_dir->next->next != NULL)
		{
			while (user_dir->next->next != NULL)
				user_dir = user_dir->next;
			free_one_dir(user_dir->next);
			user_dir->next = NULL;
			user_dir = head;
		}
		free_one_dir(user_dir->next);
		user_dir->next = NULL;
		free_one_dir(user_dir);
	}
}
