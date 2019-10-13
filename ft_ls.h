/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:37:00 by mphobos           #+#    #+#             */
/*   Updated: 2019/10/13 19:30:22 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h> //delete
#include <stdlib.h>
#include <sys/stat.h>
#include "libft/includes/libft.h"
#include <pwd.h>
#include <sys/types.h>
#include <grp.h>

typedef struct      s_file
{
    char            *mode;
    int             nlink;
    char            uid;
    char            gid;
    int             size;
    char            date;
    char            file_name;
    struct s_file   *next;
}                   t_file;

/*          flags_file.c         */
char                *get_flags(char *flags, char *new_flag);
int                 check_flag(char *flag);
char                *split_file(char *filedir, char *new_filedir);
void                get_flagfile(int ac, char **av, char **flags, char ***files);