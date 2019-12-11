/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:37:00 by mphobos           #+#    #+#             */
/*   Updated: 2019/12/11 17:43:14 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "libft/includes/libft.h"
#include <pwd.h>
#include <sys/types.h>
#include <grp.h>
#include <time.h>

typedef struct      s_file
{
    ino_t           ino;
    char            *mode;
    int             nlink;
    int             nlinkdig;
    char            *uid;
    char            *gid;
    off_t           size;
    int             sizedig;
    struct timespec date_mod;
    char            *name;
    blkcnt_t        blksize;
    struct s_file   *next;
}                   t_file;

typedef struct      s_dir
{
    char            *name;
    struct s_file   *file;
    struct timespec date_mode;
    struct s_dir    *next;
}                   t_dir;

/*          main.c                  */
t_file              *get_t_file(DIR *dir, char *flags, char *path);
t_file              *reverse_list(t_file *file);
int                 get_total(t_file *file, char *flags);
t_file              *reverse_list_sup(t_file *head_file, t_file *file, t_file *next_file, t_file *r_file);

/*          flags_file.c            */
char                *get_flags(char *flags, char *new_flag);
int                 check_flag(char *flag);
char                *split_file(char *filedir, char *new_filedir);
void                get_flagfile(int ac, char **av, char **flags, char ***files);

/*          create_new_t_file.c     */
t_file              *create_new_t_file(struct dirent *dirent, struct stat statbuf);
char                *get_mode(struct stat statbuf);
void                get_mode_sup(char *mode);
void                get_mode_sup1(char *mode, struct stat statbuf);

/*          add_file.c              */
t_file              *add_file(t_file *file, struct dirent *dirent, struct stat statbuf, char *d_name);
t_file              *add_file_sup(t_file *file, struct dirent *dirent, struct stat statbuf, char *d_name);
t_file              *add_file_t(t_file *file, struct dirent *dirent, struct stat statbuf);
t_file              *add_file_sup_t(t_file *file, struct dirent *dirent, struct stat statbuf);
t_file		        *add_file_sup_t1(t_file *prev_file, t_file *file);

/*          print_files.c           */
void                print_all_files(t_file *file, char *flags, int a);
void                print_all_files_l(t_file *file, char *flags, int a);
void                print_file_l(t_file file, int nlinkdig, int sizedig, char *flags);

/*          trash.c                 */
char                *ft_strdup_s_e(char *s, int start, int end);
int                 count_of_digits(int a);
void                fill_nlinkd_sized(t_file *file, int *nlinkdig, int *sizedig);

/*          recursion_ls.c          */
void                recursion_ls(char *flags, char *path);
void                recursion_ls_first(char *flags, char *path);

/*          free.c                  */
void                free_all_file(t_file *file);
void                free_one_file(t_file *file);
void                free_strsplit(char **str);
void                free_all_dir(t_dir *user_dir);
void                free_one_dir(t_dir *user_dir);

/*          print_user_files.c      */
void                print_user_files(char *flags, char **files);
t_file              *search_file(DIR *dir, t_file *file, char *filepath, char *flags);
char                *get_path(char *file);
t_dir               *create_dir(char *dir_name, t_file *file, struct stat statbuf);

/*          add_dir                 */
t_dir               *add_dir(t_dir *user_dir, char *dir_name, t_file *file, struct stat statbuf);
t_dir               *dir_sup(t_dir *user_dir, char *dir_name, t_file *file, struct stat statbuf);
t_dir               *add_dir_t(t_dir *user_dir, char *dir_name, t_file *file, struct stat statbuf);
t_dir               *add_dir_sup_t(t_dir *user_dir, char *dir_name, t_file *file, struct stat statbuf);
t_dir		        *add_dir_sup_t1(t_dir *prev_dir, t_dir *user_dir);
