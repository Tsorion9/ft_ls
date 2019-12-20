/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:41:31 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/20 14:10:41 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file		*add_file_sup(t_file *file, struct dirent *dirent, \
	struct stat statbuf, char *d_name)
{
	t_file	*head;
	t_file	*prev_file;

	head = file;
	prev_file = file;
	while (ft_strcmp(file->name, d_name) < 0 && file->next != NULL)
		file = file->next;
	if (file->next == NULL && ft_strcmp(file->name, d_name) < 0)
	{
		file->next = create_new_t_file(dirent, statbuf);
		return (head);
	}
	else if (ft_strcmp(file->name, d_name) >= 0 && file == head)
	{
		prev_file = create_new_t_file(dirent, statbuf);
		prev_file->next = head;
		return (prev_file);
	}
	while (prev_file->next != file && prev_file->next != NULL)
		prev_file = prev_file->next;
	prev_file->next = create_new_t_file(dirent, statbuf);
	prev_file->next->next = file;
	return (head);
}

t_file		*add_file(t_file *file, struct dirent *dirent, \
	struct stat statbuf, char *d_name)
{
	t_file	*prev_file;

	if (file == NULL)
		file = create_new_t_file(dirent, statbuf);
	else if (file->next == NULL && ft_strcmp(file->name, d_name) < 0)
		file->next = create_new_t_file(dirent, statbuf);
	else if (file->next == NULL && ft_strcmp(file->name, d_name) >= 0)
	{
		prev_file = create_new_t_file(dirent, statbuf);
		prev_file->next = file;
		return (prev_file);
	}
	else if (file->next != NULL)
		return (add_file_sup(file, dirent, statbuf, d_name));
	return (file);
}

t_file		*add_file_sup_t1(t_file *prev_file, t_file *file)
{
	while (prev_file->next != file && prev_file->next != NULL)
		prev_file = prev_file->next;
	return (prev_file);
}

t_file		*add_file_sup_t(t_file *file, struct dirent *dirent, \
	struct stat statbuf)
{
	t_file	*head;
	t_file	*prev_file;

	head = file;
	prev_file = file;
	while ((file->date_mod.tv_sec - statbuf.st_mtimespec.tv_sec) >= 0 \
		&& file->next != NULL)
		file = file->next;
	if (file->next == NULL && (file->date_mod.tv_sec - \
		statbuf.st_mtimespec.tv_sec) >= 0)
	{
		file->next = create_new_t_file(dirent, statbuf);
		return (head);
	}
	else if ((file->date_mod.tv_sec - statbuf.st_mtimespec.tv_sec) < 0 \
		&& file == head)
	{
		prev_file = create_new_t_file(dirent, statbuf);
		prev_file->next = head;
		return (prev_file);
	}
	prev_file = add_file_sup_t1(prev_file, file);
	prev_file->next = create_new_t_file(dirent, statbuf);
	prev_file->next->next = file;
	return (head);
}

t_file		*add_file_t(t_file *file, struct dirent *dirent, \
	struct stat statbuf)
{
	t_file	*prev_file;

	if (file == NULL)
		file = create_new_t_file(dirent, statbuf);
	else if (file->next == NULL && (file->date_mod.tv_sec - \
		statbuf.st_mtimespec.tv_sec) >= 0)
		file->next = create_new_t_file(dirent, statbuf);
	else if (file->next == NULL && (file->date_mod.tv_sec - \
		statbuf.st_mtimespec.tv_sec) < 0)
	{
		prev_file = create_new_t_file(dirent, statbuf);
		prev_file->next = file;
		return (prev_file);
	}
	else if (file->next != NULL)
		return (add_file_sup_t(file, dirent, statbuf));
	return (file);
}
