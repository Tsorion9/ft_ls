#include "ft_ls.h"

void            recursion_ls(char *flags, char *path)
{
    DIR         *dir;
    t_file      *file;
    char        *filepath;
    char        *tmp;

    dir = opendir(path);
    file = get_t_file(dir, flags, path);
    ft_putstr(path);
    ft_putchar('\n');
    print_all_files(file, flags);
    tmp = ft_strjoin(path, "/");
    while (file != NULL)
    {
        if (file->mode[0] == 'd' && ft_strcmp(file->name, ".") != 0 &&
            ft_strcmp(file->name, "..") != 0)
        {
            filepath = ft_strjoin(tmp, file->name);
            recursion_ls(flags, filepath);
            free(filepath);
        }
        file = file->next;
    }
    free(tmp);
    closedir(dir);
}
