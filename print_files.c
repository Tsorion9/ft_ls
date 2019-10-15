/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:46:12 by mphobos           #+#    #+#             */
/*   Updated: 2019/10/15 19:24:43 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file          *reverse_list(t_file *file)
{
    t_file      *head_file;
    t_file      *next_file;
    t_file      *head_r_file;
    t_file      *r_file;

    head_file = file;
    while (file->next != NULL)
        file = file->next;
    r_file = file;
    head_r_file = r_file;
    while (head_file->next != NULL)
    {
        file = head_file;
        next_file = file->next;
        while (next_file->next != NULL)
        {
            file = file->next;
            next_file = next_file->next;
        }
        file->next = NULL;
        r_file = head_r_file;
        while (r_file->next != NULL)
            r_file = r_file->next;
        r_file->next = file;
    }
    return (head_r_file);
}

void            print_all_files(t_file *file, char *flags)
{
    if (ft_strchr(flags, 'r') != NULL)
        file = reverse_list(file);
    if (ft_strchr(flags, 'l') != NULL)
    {
        fill_nlinkd_sized(file, &(file->nlinkdig), &(file->sizedig));
        print_all_files_l(file, flags);
        return ;
    }
    while (file != NULL)
    {
        if (ft_strchr(flags, 'a') == NULL && file->name[0] != '.')
        {
            ft_putstr(file->name);
            if (file->next != NULL)
                ft_putchar('\t');
            else
                ft_putchar('\n');
        }
        else if (ft_strchr(flags, 'a') != NULL)
        {
            ft_putstr(file->name);
            if (file->next != NULL)
                ft_putchar('\t');
            else
                ft_putchar('\n');
        }
        file = file->next;
    }
}

void            print_file_l(t_file file, int nlinkdig, int sizedig)
{
    char        *date_mod;
    int         space;

    date_mod = ft_strdup_s_e(ctime(&(file.date_mod.tv_sec)), 4, 16);
    ft_putstr(file.mode);
    space = 0;
    while (space < nlinkdig - count_of_digits(file.nlink))
    {
        write(1, " ", 1);
        space++;
    }
    ft_putnbr(file.nlink);
    ft_putstr(" ");
    ft_putstr(file.uid);
    ft_putstr("  ");
    ft_putstr(file.gid);
    space = 0;
    while (space < sizedig - count_of_digits(file.size))
    {
        write(1, " ", 1);
        space++;
    }
    ft_putnbr(file.size);
    ft_putstr(" ");
    ft_putstr(date_mod);
    ft_putstr(" ");
    ft_putstr(file.name);
    ft_putchar('\n');
    free(date_mod);
}

void            print_all_files_l(t_file *file, char *flags)
{
    int     nlinkdig;
    int     sizedig;

    nlinkdig = file->nlinkdig + 2;
    sizedig = file->sizedig + 2;
    while (file != NULL)
    {
        if (ft_strchr(flags, 'a') == NULL && file->name[0] != '.')
            print_file_l(*file, nlinkdig, sizedig);
        else if (ft_strchr(flags, 'a') != NULL)
            print_file_l(*file, nlinkdig, sizedig);
        file = file->next;
    }
}
