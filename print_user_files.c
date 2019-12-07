#include "ft_ls.h"

char        *get_path(char *file)
{
    char    *path;
    int     i;

    i = ft_strlen(file) - 1;
    while (file[i] != '/')
        i--;
    path = ft_strsub(file, 0, i);
    return (path);
}

t_file      *search_file(DIR *dir, t_file *file, char *filepath, char *flags)
{
    char            *file_name;
    struct dirent   *dirent;
    struct stat     statbuf;
    int             i;

    i = ft_strlen(filepath) - 1;
    while (filepath[i] != '/')
        i--;
    file_name = ft_strdup(filepath + i + 1);
    dirent = readdir(dir);
    while (dirent != NULL)
    {
        if (ft_strcmp(file_name, dirent->d_name) == 0)
        {
            lstat(filepath, &statbuf);
            if (ft_strchr(flags, 't') == NULL)
                file = add_file(file, dirent, statbuf);
            else
                file = add_file_t(file, dirent, statbuf);
            break ;
         }
         dirent = readdir(dir);
    }
    free(file_name);
    free(file->name);
    file->name = ft_strdup(filepath);
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
        if (dir == NULL && ft_strchr(files[i], '/') != NULL &&
            files[i][ft_strlen(files[i]) - 1] != '/')
        {
            path = get_path(files[i]);
            dir = opendir(path);
            file = search_file(dir, file, files[i], flags);
            free(path);
        }
        i++;
    }
    print_all_files(file, flags);
}
