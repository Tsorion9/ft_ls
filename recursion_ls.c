/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion_ls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:07:21 by mphobos           #+#    #+#             */
/*   Updated: 2019/10/18 13:42:49 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void            recursion_ls_first(char *flags, char *path)
{
    DIR         *dir;
    t_file      *file;
    char        *filepath;
    char        *tmp;
    t_file      *head;

    dir = opendir(path);
    file = get_t_file(dir, flags, path);
    print_all_files(file, flags);
    tmp = ft_strjoin(path, "/");
    head = file;
    while (file != NULL)
    {
        if (file->mode[0] == 'd' && ft_strcmp(file->name, ".") != 0 &&
            ft_strcmp(file->name, "..") != 0)
        {
            filepath = ft_strjoin(tmp, file->name);
            if (file->name[0] != '.' && ft_strchr(flags, 'a') == NULL)
                recursion_ls(flags, filepath);
            else if (ft_strchr(flags, 'a') != NULL)
                recursion_ls(flags, filepath);
            free(filepath);
        }
        file = file->next;
    }
    free(tmp);
    free_all_file(head);
    closedir(dir);
}

void            recursion_ls(char *flags, char *path)
{
    DIR         *dir;
    t_file      *file;
    char        *filepath;
    char        *tmp;
    t_file      *head;

    dir = opendir(path);
    file = get_t_file(dir, flags, path);
    write(1, "\n", 1);
    ft_putstr(path);
    write(1, ":\n", 2);
    print_all_files(file, flags);
    tmp = ft_strjoin(path, "/");
    head = file;
    while (file != NULL)
    {
        if (file->mode[0] == 'd' && ft_strcmp(file->name, ".") != 0 &&
            ft_strcmp(file->name, "..") != 0)
        {
            filepath = ft_strjoin(tmp, file->name);
            if (file->name[0] != '.' && ft_strchr(flags, 'a') == NULL)
                recursion_ls(flags, filepath);
            else if (ft_strchr(flags, 'a') != NULL)
                recursion_ls(flags, filepath);
            free(filepath);
        }
        file = file->next;
    }
    free(tmp);
    free_all_file(head);
    closedir(dir);
}
