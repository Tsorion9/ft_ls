/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:37:34 by mphobos           #+#    #+#             */
/*   Updated: 2019/10/15 18:06:06 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
    if (ft_strchr(flags, 't') == NULL)
        while (dirent != NULL)
        {
            filepath = ft_strjoin(tmp, dirent->d_name);
            lstat(filepath, &statbuf);
            file = add_file(file, dirent, statbuf);
            dirent = readdir(dir);
            free(filepath);
        }
    else
    {
        while (dirent != NULL)
        {
            filepath = ft_strjoin(tmp, dirent->d_name);
            lstat(filepath, &statbuf);
            file = add_file_t(file, dirent, statbuf);
            dirent = readdir(dir);
            free(filepath);
        }
    }
    free(tmp);
    return (file);
}

int         main(int ac, char **av)
{
    DIR     *dir = opendir(".");
    char    *flags;
    char    **files;

    get_flagfile(ac, av, &flags, &files);
    if (ft_strchr(flags, 'R') == NULL)
    {
        t_file *filelst = get_t_file(dir, flags, ".");
        print_all_files(filelst, flags);
    }
    else
        recursion_ls(flags, ".");
    closedir(dir);
    return (0);
}
