/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_user_dir_sup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:13:15 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/12 15:02:53 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_user_dir_sup(t_dir *user_dir, char *flags, t_file *file)
{
	if (file != NULL && user_dir != NULL)
		write(1, "\n", 1);
	if (user_dir != NULL)
	{
		if (user_dir->next == NULL && file == NULL)
		{
			if (ft_strchr(flags, 'R') == NULL)
				print_all_files(user_dir->file, flags, 1);
			else
				recursion_ls_first(flags, user_dir->name);
			if (user_dir->next != NULL)
				write(1, "\n", 1);
		}
		else
			print_user_dir_sup1(user_dir, flags);
	}
}

void		print_user_dir_sup1(t_dir *user_dir, char *flags)
{
	while (user_dir != NULL)
	{
		ft_putstr(user_dir->name);
		write(1, ":\n", 2);
		if (ft_strchr(flags, 'R') == NULL)
			print_all_files(user_dir->file, flags, 1);
		else
			recursion_ls_first(flags, user_dir->name);
		if (user_dir->next != NULL)
			write(1, "\n", 1);
		user_dir = user_dir->next;
	}
}

t_dir		*print_user_dir_sup2(char *flags, t_dir *user_dir, t_file *file)
{
	if (ft_strchr(flags, 'r') != NULL && user_dir != NULL)
		user_dir = reverse_dir(user_dir);
	print_user_dir_sup(user_dir, flags, file);
	return (user_dir);
}

t_dir		*reverse_dir_sup(t_dir *user_dir)
{
	while (user_dir->next != NULL)
		user_dir = user_dir->next;
	return (user_dir);
}

t_dir		*reverse_dir(t_dir *user_dir)
{
	t_dir	*head_dir;
	t_dir	*next_dir;
	t_dir	*head_r_dir;
	t_dir	*r_dir;

	head_dir = user_dir;
	user_dir = reverse_dir_sup(user_dir);
	r_dir = user_dir;
	head_r_dir = r_dir;
	while (head_dir->next != NULL)
	{
		user_dir = head_dir;
		next_dir = user_dir->next;
		while (next_dir->next != NULL)
		{
			user_dir = user_dir->next;
			next_dir = next_dir->next;
		}
		user_dir->next = NULL;
		r_dir = head_r_dir;
		while (r_dir->next != NULL)
			r_dir = r_dir->next;
		r_dir->next = user_dir;
	}
	return (head_r_dir);
}
