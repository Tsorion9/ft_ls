/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_user_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:57:38 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/11 15:57:39 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char        *get_path(char *file)
{
    char    *path;
    int     i;

    i = ft_strlen(file) - 1;
    if (ft_strchr(file, '/') != NULL)
    {
        while (file[i] != '/')
            i--;
        path = ft_strsub(file, 0, i + 1);
    }
    else
    {
        path = (char*)malloc(sizeof(char) * 3);
        path[0] = '.';
        path[1] = '/';
        path[2] = '\0';
    }
    return (path);
}

void        new_filename(t_file *file, char *filepath)
{
    char    *path;
    char    *temp;

    path = get_path(filepath);
    while (file != NULL)
    {
        temp = ft_strjoin(path, file->name);
        if (ft_strcmp(filepath, temp) == 0)
        {
            free(file->name);
            free(temp);
            free(path);
            file->name = ft_strdup(filepath);
            return ;
        }
        free(temp);
        file = file->next;
    }
    free(path);
}

int         count_file(t_file *file)
{
    int     i;

    i = 0;
    if (file != NULL)
        while (file != NULL)
        {
            file = file->next;
            i++;
        }
    return (i);
}

void        print_such_file(char *file_name)
{
    write(1, "ft_ls: ", 7);
    ft_putstr(file_name);
    write(1, ": No such file or directory\n", 28);
}

t_file      *search_file(DIR *dir, t_file *file, char *filepath, char *flags)
{
    char            *file_name;
    struct dirent   *dirent;
    struct stat     statbuf;
    int             i;
    int             count;

    if (dir == NULL)
    {
        print_such_file(filepath);
        return (file);
    }
    i = ft_strlen(filepath) - 1;
    if (ft_strchr(filepath, '/') != NULL)
    {
        while (filepath[i] != '/')
            i--;
        file_name = ft_strdup(filepath + i + 1);
    }
    else
        file_name = ft_strdup(filepath);
    dirent = readdir(dir);
    count = count_file(file);
    while (dirent != NULL)
    {
        if (ft_strcmp(file_name, dirent->d_name) == 0)
        {
            lstat(filepath, &statbuf);
            if (ft_strchr(flags, 't') == NULL)
                file = add_file(file, dirent, statbuf, filepath);
            else
                file = add_file_t(file, dirent, statbuf);
            break ;
         }
         dirent = readdir(dir);
    }
    if (count == count_file(file))
        print_such_file(filepath);
    if (dirent != NULL)
        new_filename(file, filepath);
    free(file_name);
    return (file);
}

t_dir           *create_dir(char *dir_name, t_file *file, struct stat statbuf)
{
    t_dir       *dir;

    dir = (t_dir*)malloc(sizeof(t_dir));
    if (dir != NULL)
    {
        dir->name = ft_strdup(dir_name);
        dir->file = file;
        dir->date_mode = statbuf.st_mtimespec;
        dir->next = NULL;
    }
    return (dir);
}

void        print_user_dir_sup(t_dir *user_dir, char *flags, t_file *file)
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
    }
}

t_dir          *reverse_dir(t_dir *user_dir)
{
    t_dir   *head_dir;
    t_dir   *next_dir;
    t_dir   *head_r_dir;
    t_dir   *r_dir;

    head_dir = user_dir;
    while (user_dir->next != NULL)
        user_dir = user_dir->next;
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

void        print_user_dir(char *flags, char **files, t_file *file)
{
    DIR             *dir;
    t_dir           *user_dir;
    struct stat     statbuf;
    int             i;

    i = 0;
    user_dir = NULL;
    while (files[i] != NULL)
    {
        dir = opendir(files[i]);
        if (dir != NULL)
        {
            lstat(files[i], &statbuf);
            if (ft_strchr(flags, 't') == NULL)
                user_dir = add_dir(user_dir, files[i], get_t_file(dir, flags, files[i]), statbuf);
            else
                user_dir = add_dir_t(user_dir, files[i], get_t_file(dir, flags, files[i]), statbuf);
            closedir(dir);
        }
        i++;
    }
    if (ft_strchr(flags, 'r') != NULL && user_dir != NULL)
        user_dir = reverse_dir(user_dir);
    print_user_dir_sup(user_dir, flags, file);
    free_all_dir(user_dir);
}

void        print_user_files(char *flags, char **files)
{
    DIR         *dir;
    t_file      *file;
    char        *path;
    int         i;

    file = NULL;
    i = 0;
    while (files[i] != NULL)
    {
        dir = opendir(files[i]);
        if (dir == NULL && files[i][ft_strlen(files[i]) - 1] != '/')
        {
            path = get_path(files[i]);
            dir = opendir(path);
            file = search_file(dir, file, files[i], flags);
            free(path);
        }
        if (dir != NULL)
            closedir(dir);
        i++;
    }
    if (file != NULL)
    {
        if (ft_strchr(flags, 'r') != NULL)
            print_all_files(reverse_list(file), flags, 0);
        else
            print_all_files(file, flags, 0);
    }
    print_user_dir(flags, files, file);
    free_all_file(file);
}
