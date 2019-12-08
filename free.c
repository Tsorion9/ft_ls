/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 13:13:19 by mphobos           #+#    #+#             */
/*   Updated: 2019/10/18 13:31:25 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void            free_one_file(t_file *file)
{
    free(file->mode);
    free(file->uid);
    free(file->gid);
    free(file->name);
    free(file);
}

void            free_all_file(t_file *file)
{
    t_file      *head;

    head = file;
    if (file->next == NULL)
    {
        free_one_file(file);
        return ;
    }
    while (file->next->next != NULL)
    {
        while (file->next->next != NULL)
            file = file->next;
        free_one_file(file->next);
        file->next = NULL;
        file = head;
    }
    free_one_file(file->next);
    file->next = NULL;
    free_one_file(file);
}

void            free_strsplit(char **str)
{
    int     i;

    i = 0;
    if (str != NULL)
    {
        while (str[i] != NULL)
        {
            free(str[i]);
            i++;
        }
        free(str);
    }
}
