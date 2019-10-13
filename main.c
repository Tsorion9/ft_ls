/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:37:34 by mphobos           #+#    #+#             */
/*   Updated: 2019/10/13 19:35:22 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
            printf("%s\n", gid->gr_name);
        }
        dirent = readdir(dir);
        printf("\n");
    }
    closedir(dir);
    return (0);
}*/

int         main(int ac, char **av)
{
    char    *flags;
    char    **files;
    int     i = 0;

    get_flagfile(ac, av, &flags, &files);
    printf("%s\n", flags);
    if (files != NULL)
    {
        while (files[i] != NULL)
        {
            printf("%s\n", files[i]);
            i++;
        }
    }
    return (0);
}
