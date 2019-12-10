/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:37:34 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/10 15:08:45 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file          *reverse_list(t_file *file)
{
    t_file      *head_file;
    t_file      *next_file;
    t_file      *head_r_file;
    t_file      *r_file;

    head_file = file;
    while (file->next != NULL)
        file = file->next;
    r_file = file;
    head_r_file = r_file;
    while (head_file->next != NULL)
    {
        file = head_file;
        next_file = file->next;
        while (next_file->next != NULL)
        {
            file = file->next;
            next_file = next_file->next;
        }
        file->next = NULL;
        r_file = head_r_file;
        while (r_file->next != NULL)
            r_file = r_file->next;
        r_file->next = file;
    }
    return (head_r_file);
}

t_file      *get_t_file(DIR *dir, char *flags, char *path)
{
    t_file          *file;
    struct dirent   *dirent;
    struct stat     statbuf;
    char            *filepath;
    char            *tmp;

    tmp = ft_strjoin(path, "/");
    file = NULL;
    dirent = readdir(dir);
    while (dirent != NULL)
    {
        filepath = ft_strjoin(tmp, dirent->d_name);
        lstat(filepath, &statbuf);
        if (ft_strchr(flags, 't') == NULL)
            file = add_file(file, dirent, statbuf, dirent->d_name);
        else
            file = add_file_t(file, dirent, statbuf);
        dirent = readdir(dir);
        free(filepath);
    }
    free(tmp);
    if (ft_strchr(flags, 'r') != NULL)
        return (reverse_list(file));
    return (file);
}

int         get_total(t_file *file, char *flags)
{
    blkcnt_t     size;

    size = 0;
    while (file != NULL)
    {
        if (ft_strchr(flags, 'a') != NULL || 
            (ft_strchr(flags, 'a') == NULL && file->name[0] != '.'))
            size += file->blksize;
        file = file->next;
    }
    return (size);
}

int         main(int ac, char **av)
{
	DIR     *dir = opendir(".");
   	char    *flags;
	char    **files;
	t_file 	*filelst;

	flags = NULL; //delete
	files = NULL; //delete
	get_flagfile(ac, av, &flags, &files);
	filelst = get_t_file(dir, flags, ".");
    if (files == NULL)
    {
        if (ft_strchr(flags, 'R') == NULL)
            print_all_files(filelst, flags, 1);
        else
            recursion_ls_first(flags, ".");
        free_all_file(filelst);
        closedir(dir);
    }
    else
        print_user_files(flags, files);
    free(flags);
    free_strsplit(files);
    return (0);
}
