/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:46:12 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/14 17:18:31 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_all_files_sup(t_file *file, char *flags)
{
	if (ft_strchr(flags, 'i') != NULL)
	{
		ft_putnbr(file->ino);
		write(1, " ", 1);
	}
	ft_putstr(file->name);
	if (file->next != NULL)
		write(1, "    ", 4);
}

void		print_all_files(t_file *file, char *flags, int a)
{
	if (ft_strchr(flags, 'l') != NULL || ft_strchr(flags, 'g') != NULL)
	{
		fill_nlinkd_sized(file, &(file->nlinkdig), &(file->sizedig));
		print_all_files_l(file, flags, a);
		return ;
	}
	while (file != NULL)
	{
		if (ft_strchr(flags, 'a') == NULL && file->name[0] != '.')
			print_all_files_sup(file, flags);
		else if (ft_strchr(flags, 'a') != NULL)
			print_all_files_sup(file, flags);
		if (file->next == NULL)
			ft_putchar('\n');
		file = file->next;
	}
}

void		print_file_l_sup(t_file file, int nlinkdig, \
	int sizedig, char *flags)
{
	int	space;

	space = 0;
	while (space < nlinkdig - count_of_digits(file.nlink))
	{
		write(1, " ", 1);
		space++;
	}
	ft_putnbr(file.nlink);
	write(1, " ", 1);
	if (ft_strchr(flags, 'g') == NULL)
	{
		ft_putstr(file.uid);
		ft_putstr("  ");
	}
	ft_putstr(file.gid);
	space = 0;
	while (space < sizedig - count_of_digits(file.size))
	{
		write(1, " ", 1);
		space++;
	}
}

void		print_file_l(t_file file, int nlinkdig, int sizedig, char *flags)
{
	char	*date_mod;

	date_mod = ft_strdup_s_e(ctime(&(file.date_mod.tv_sec)), 4, 16);
	if (ft_strchr(flags, 'i') != NULL)
	{
		write(1, "        ", 6 - count_of_digits(file.ino));
		ft_putnbr(file.ino);
		write(1, " ", 1);
	}
	ft_putstr(file.mode);
	print_file_l_sup(file, nlinkdig, sizedig, flags);
	ft_putnbr(file.size);
	ft_putstr(" ");
	ft_putstr(date_mod);
	ft_putstr(" ");
	ft_putstr(file.name);
	if (file.mode[0] == 'l')
	{
		write(1, " -> ", 4);
		ft_putstr(file.lname);
	}
	ft_putchar('\n');
	free(date_mod);
}

void		print_all_files_l(t_file *file, char *flags, int a)
{
	int		nlinkdig;
	int		sizedig;
	int		total;
	t_file	*head;

	nlinkdig = file->nlinkdig + 2;
	sizedig = file->sizedig + 2;
	total = get_total(file, flags);
	head = file;
	if ((total != 0 || ft_strchr(flags, 'a') != NULL) && a == 1)
	{
		write(1, "total ", 6);
		ft_putnbr(total);
		write(1, "\n", 1);
	}
	while (file != NULL)
	{
		if (ft_strchr(flags, 'a') == NULL && file->name[0] != '.')
			print_file_l(*file, nlinkdig, sizedig, flags);
		else if (ft_strchr(flags, 'a') != NULL)
			print_file_l(*file, nlinkdig, sizedig, flags);
		file = file->next;
	}
}
