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
            file->name = ft_strdup(filepath);
            return ;
        }
        free(temp);
        file = file->next;
    }
}

t_file      *search_file(DIR *dir, t_file *file, char *filepath, char *flags)
{
    char            *file_name;
    struct dirent   *dirent;
    struct stat     statbuf;
    int             i;

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

void        print_user_dir_sup(t_dir *user_dir, char *flags)
{
    if (user_dir != NULL)
    {
        if (user_dir->next == NULL)
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

void        print_user_dir(char *flags, char **files)
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
        }
        if (dir != NULL)
            closedir(dir);
        i++;
    }
    print_user_dir_sup(user_dir, flags);
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
        print_all_files(file, flags, 0);
    print_user_dir(flags, files);
    free_all_file(file);
}
