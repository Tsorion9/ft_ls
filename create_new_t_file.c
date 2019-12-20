/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_t_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:37:05 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/20 14:10:41 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		get_mode_sup(char *mode)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		mode[i] = '-';
		i++;
	}
	mode[i] = '\0';
}

void		get_mode_sup1(char *mode, struct stat statbuf)
{
	if ((S_IWOTH & statbuf.st_mode) == S_IWOTH)
		mode[8] = 'w';
	if ((S_IXOTH & statbuf.st_mode) == S_IXOTH)
		mode[9] = 'x';
}

char		*get_mode(struct stat statbuf)
{
	char	*mode;

	mode = (char*)malloc(sizeof(char) * 11);
	get_mode_sup(mode);
	if ((S_IFDIR & statbuf.st_mode) == S_IFDIR)
		mode[0] = 'd';
	else if ((S_IFLNK & statbuf.st_mode) == S_IFLNK)
		mode[0] = 'l';
	if ((S_IRUSR & statbuf.st_mode) == S_IRUSR)
		mode[1] = 'r';
	if ((S_IWUSR & statbuf.st_mode) == S_IWUSR)
		mode[2] = 'w';
	if ((S_IXUSR & statbuf.st_mode) == S_IXUSR)
		mode[3] = 'x';
	if ((S_IRGRP & statbuf.st_mode) == S_IRGRP)
		mode[4] = 'r';
	if ((S_IWGRP & statbuf.st_mode) == S_IWGRP)
		mode[5] = 'w';
	if ((S_IXGRP & statbuf.st_mode) == S_IXGRP)
		mode[6] = 'x';
	if ((S_IROTH & statbuf.st_mode) == S_IROTH)
		mode[7] = 'r';
	get_mode_sup1(mode, statbuf);
	return (mode);
}

t_file		*create_new_t_file(struct dirent *dirent, struct stat statbuf)
{
	t_file			*file;
	struct passwd	*uid;
	struct group	*gid;

	file = (t_file*)malloc(sizeof(t_file));
	file->ino = dirent->d_ino;
	uid = getpwuid(statbuf.st_uid);
	gid = getgrgid(statbuf.st_gid);
	file->mode = get_mode(statbuf);
	file->nlink = statbuf.st_nlink;
	uid = getpwuid(statbuf.st_uid);
	file->uid = ft_strdup(uid->pw_name);
	gid = getgrgid(statbuf.st_gid);
	file->gid = ft_strdup(gid->gr_name);
	file->size = statbuf.st_size;
	file->date_mod = statbuf.st_mtimespec;
	if ((statbuf.st_mode & S_IFBLK) != S_IFBLK)
		file->blksize = statbuf.st_blocks;
	else
		file->blksize = 0;
	file->name = ft_strdup(dirent->d_name);
	file->lname = NULL;
	file->next = NULL;
	return (file);
}
