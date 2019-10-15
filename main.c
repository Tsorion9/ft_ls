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

t_file      *get_t_file(DIR *dir, char *flags)
{
    t_file          *file;
    struct dirent   *dirent;
    struct stat     statbuf;

    file = NULL;
    dirent = readdir(dir);
    if (ft_strchr(flags, 't') == NULL)
        while (dirent != NULL)
        {
            lstat(dirent->d_name, &statbuf);
            file = add_file(file, dirent, statbuf);
            dirent = readdir(dir);
        }
    else
    {
        while (dirent != NULL)
        {
            lstat(dirent->d_name, &statbuf);
            file = add_file_t(file, dirent, statbuf);
            dirent = readdir(dir);
        }
    }
    return (file);
}

int         main(int ac, char **av)
{
    DIR     *dir = opendir(".");
    char    *flags;
    char    **files;

    get_flagfile(ac, av, &flags, &files);
    t_file *filelst = get_t_file(dir, flags);
    closedir(dir);
    print_all_files(filelst, flags);
    return (0);
}
