/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 19:29:51 by mphobos           #+#    #+#             */
/*   Updated: 2019/10/17 18:35:28 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int         check_flag(char *flag)
{
    int     i;

    i = 0;
    if (flag[i] != '-')
        return (0);
    i++;
    while (flag[i] == 'l' || flag[i] == 'R' || flag[i] == 'a' ||
        flag[i] == 'r' || flag[i] == 't' || flag[i] == 'g')
        i++;
    if (i == 1 || flag[i] != '\0')
        return (0);
    return (1);
}

char        *get_flags(char *flags, char *new_flag)
{
    char        *tmp;

    if (flags == NULL)
        flags = ft_strnew(1);
    if (check_flag(new_flag) != 0)
    {
        tmp = ft_strjoin(flags, new_flag + 1);
        free(flags);
        flags = tmp;
    }
    else
    {
        ft_putstr("usage: ./ft_ls \
[-lRartg] [file ...]\n");
        free(flags);
        exit(0);
    }
    return (flags);
}

char        *split_file(char *filedir, char *new_filedir)
{
    char    *tmp;
    char    *tmpa;

    if (filedir == NULL)
        filedir = ft_strnew(1);
    tmpa = ft_strjoin(filedir, " ");
    tmp = ft_strjoin(tmpa, new_filedir);
    free(tmpa);
    free(filedir);
    filedir = tmp;
    return(filedir);
}

void        get_flagfile(int ac, char **av, char **flags, char ***files)
{
    int     i;
    char    *file;
    
    file = NULL;
    i = 1;
    while (i < ac)
    {
        if (av[i][0] != '-')
            break ;
        *flags = get_flags(*flags, av[i]);
        i++;
    }
    while (i < ac)
    {
        file = split_file(file, av[i]);
        i++;
    }
    *files = ft_strsplit(file, ' ');
    if (*flags == NULL)
        *flags = ft_strnew(1);
    free(file);
}
