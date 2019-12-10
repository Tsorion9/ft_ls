#include "ft_ls.h"

t_dir      *add_dir_sup(t_dir *user_dir, char *dir_name, t_file *file, struct stat statbuf)
{
    t_dir      *head;
    t_dir      *prev_dir;

    head = user_dir;
    prev_dir = user_dir;
    while (ft_strcmp(user_dir->name, dir_name) < 0 && user_dir->next != NULL)
        user_dir = user_dir->next;
    if (user_dir->next == NULL && ft_strcmp(user_dir->name, dir_name) < 0)
    {
        user_dir->next = create_dir(dir_name, file, statbuf);
        return (head);
    }
    else if (ft_strcmp(user_dir->name, dir_name) >= 0 && user_dir == head)
    {
        prev_dir = create_dir(dir_name, file, statbuf);
        prev_dir->next = head;
        return (prev_dir);
    }
    while (prev_dir->next != user_dir && prev_dir->next != NULL)
        prev_dir = prev_dir->next;
    prev_dir->next = create_dir(dir_name, file, statbuf);
    prev_dir->next->next = user_dir;
    return (head);
}

t_dir      *add_dir(t_dir *user_dir, char *dir_name, t_file *file, struct stat statbuf)
{
    t_dir      *prev_dir;

    if (user_dir == NULL)
        user_dir = create_dir(dir_name, file, statbuf);
    else if (user_dir->next == NULL && ft_strcmp(user_dir->name, dir_name) < 0)
        user_dir->next = create_dir(dir_name, file, statbuf);
    else if (user_dir->next == NULL && ft_strcmp(user_dir->name, dir_name) >= 0)
    {
        prev_dir = create_dir(dir_name, file, statbuf);
        prev_dir->next = user_dir;
        return (prev_dir);
    }
    else if (user_dir->next != NULL)
        return (add_dir_sup(user_dir, dir_name, file, statbuf));
    return (user_dir);
}

/*t_file      *add_file_sup_t(t_file *file, struct dirent *dirent, struct stat statbuf)
{
    t_file      *head;
    t_file      *prev_file;

    head = file;
    prev_file = file;
    while ((file->date_mod.tv_sec - statbuf.st_mtimespec.tv_sec) >= 0 && file->next != NULL)
        file = file->next;
    if (file->next == NULL && (file->date_mod.tv_sec - statbuf.st_mtimespec.tv_sec) >= 0)
    {
        file->next = create_new_t_file(dirent, statbuf);
        return (head);
    }
    else if ((file->date_mod.tv_sec - statbuf.st_mtimespec.tv_sec) < 0 && file == head)
    {
        prev_file = create_new_t_file(dirent, statbuf);
        prev_file->next = head;
        return (prev_file);
    }
    while (prev_file->next != file && prev_file->next != NULL)
        prev_file = prev_file->next;
    prev_file->next = create_new_t_file(dirent, statbuf);
    prev_file->next->next = file;
    return (head);
}

t_file      *add_file_t(t_file *file, struct dirent *dirent, struct stat statbuf)
{
    t_file      *prev_file;

    if (file == NULL)
        file = create_new_t_file(dirent, statbuf);
    else if (file->next == NULL && (file->date_mod.tv_sec - statbuf.st_mtimespec.tv_sec) >= 0)
        file->next = create_new_t_file(dirent, statbuf);
    else if (file->next == NULL && (file->date_mod.tv_sec - statbuf.st_mtimespec.tv_sec) < 0)
    {
        prev_file = create_new_t_file(dirent, statbuf);
        prev_file->next = file;
        return (prev_file);
    }
    else if (file->next != NULL)
        return (add_file_sup_t(file, dirent, statbuf));
    return (file);
}*/
