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
    if (ft_strchr(flags, 'r') != NULL)
        file = reverse_list(file);
    print_all_files(file, flags, 0);
    free_all_file(file);
}
