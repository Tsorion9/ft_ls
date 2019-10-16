/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:37:00 by mphobos           #+#    #+#             */
/*   Updated: 2019/10/15 18:54:17 by mphobos          ###   ########.fr       */
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
#include <time.h>

typedef struct      s_file
{
    char            *mode;
    int             nlink;
    int             nlinkdig;
    char            *uid;
    char            *gid;
    off_t           size;
    int             sizedig;
    struct timespec date_mod;
    char            *name;
    struct s_file   *next;
}                   t_file;

/*          main.c                  */
t_file              *get_t_file(DIR *dir, char *flags, char *path);

/*          flags_file.c            */
char                *get_flags(char *flags, char *new_flag);
int                 check_flag(char *flag);
char                *split_file(char *filedir, char *new_filedir);
void                get_flagfile(int ac, char **av, char **flags, char ***files);

/*          create_new_t_file.c     */
t_file              *create_new_t_file(struct dirent *dirent, struct stat statbuf);
char                *get_mode(struct stat statbuf);
void                get_mode_sup(char *mode);

/*          add_file.c              */
t_file              *add_file(t_file *file, struct dirent *dirent, struct stat statbuf);
t_file              *add_file_sup(t_file *file, struct dirent *dirent, struct stat statbuf);
t_file              *add_file_t(t_file *file, struct dirent *dirent, struct stat statbuf);
t_file              *add_file_sup_t(t_file *file, struct dirent *dirent, struct stat statbuf);

/*          print_files.c           */
void                print_all_files(t_file *file, char *flags);
void                print_all_files_l(t_file *file, char *flags);
void                print_file_l(t_file file, int nlinkdig, int sizedig);
t_file              *reverse_list(t_file *file);

/*          trash.c                 */
char                *ft_strdup_s_e(char *s, int start, int end);
int                 count_of_digits(int a);
void                fill_nlinkd_sized(t_file *file, int *nlinkdig, int *sizedig);

/*          recursion_ls.c          */
void                recursion_ls(char *flags, char *path);
