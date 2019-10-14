/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:37:34 by mphobos           #+#    #+#             */
/*   Updated: 2019/10/14 18:48:15 by mphobos          ###   ########.fr       */
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

/*int         main(void)
{
    DIR *dir = opendir(".");
    struct dirent *dirent = readdir(dir);
    struct stat statbuf;
    struct group *gid;
    while (dirent != NULL)
    {
        if (ft_strcmp(dirent->d_name, ".") != 0 &&
            ft_strcmp(dirent->d_name, "..") != 0)
        {
            stat(dirent->d_name, &statbuf);
            gid = getgrgid(statbuf.st_gid);
            printf("%s\n", dirent->d_name);
            if ((S_IFREG & statbuf.st_mode) == S_IFREG)
                printf("is file\n");
            else
                printf("is not file\n");
            printf("%lld\n", statbuf.st_size);
        }
        dirent = readdir(dir);
        printf("\n");
    }
    closedir(dir);
    return (0);
}*/

int         main(int ac, char **av)
{
    DIR     *dir = opendir(".");
    char    *flags;
    char    **files;

    get_flagfile(ac, av, &flags, &files);
    t_file *filelst = get_t_file(dir, flags);
    filelst = NULL;
    return (0);
}
