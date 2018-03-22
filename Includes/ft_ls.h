/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 10:25:38 by tgascoin          #+#    #+#             */
/*   Updated: 2017/02/09 16:30:57 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <errno.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <time.h>
# include <unistd.h>
# include <string.h>
# include <pwd.h>
# include <grp.h>
# include <sys/acl.h>
# include <sys/xattr.h>

typedef struct		s_args
{
	int				l;
	int				ru;
	int				a;
	int				r;
	int				t;
}					t_args;

typedef struct		s_file
{
	char			*name;
	dev_t			rdev;
	char			*npath;
	char			type;
	mode_t			mode;
	nlink_t			nlink;
	uid_t			uid;
	gid_t			gid;
	off_t			size;
	time_t			lm;
	int				blks;
	struct s_file	*next;
	struct s_file	*prev;
}					t_file;

typedef struct		s_sort
{
	char			*tmp;
	int				itmp;
	int				r;
	t_file			*file;
	t_file			*new;
	t_file			next;
	t_file			curr;
}					t_sort;

typedef struct		s_ft_cr
{
	struct dirent	*sdir;
	t_file			*f;
	t_file			*begin;
	int				nope;
	int				blksum;
}					t_ft_cr;

typedef struct		s_lcr
{
	t_file			*file;
	char			*tmp;
	struct stat		dfile;
}					t_lcr;

void				printperm(mode_t m, char *npath);
void				printlinked(t_file *file, t_args args);
void				printdate(time_t t);
void				printsizecol(t_file *file);
void				printtotal(char *name);
void				printerror(char *name, int *ern, int s, int mode);
int					printlist(t_file *begin, int s, t_args args, int total);

t_file				*ft_dsort(t_file *begin);
t_file				*ft_tsort(t_file *begin);
void				ft_init_args(t_args *args, int *ic);
void				assign_args(t_args *args, char c, char *pn);
t_file				*ft_lcr(char *name, char *path, t_file *prev, int mode);
t_file				*ft_revl(t_file *begin);
t_args				get_args(int ac, char **av, int *i);
t_file				*crparam(int ac, int ic, char **av, int *nbd);
void				gothrdirs(t_file *begin, t_args args, int nbd, int nbf);

t_file				*ft_cr(DIR *adir, t_args args, char *name, int *total);
void				ft_l(char *name, t_file *file, t_args args);
void				ft_resl(t_file **file, int *ern, int *dv, int *nbd);
char				*ft_list(DIR *adir, struct dirent *sdir, char *tname);
void				ft_open(char *name, int s, t_args args);
char				*ft_strapp(char *s1, char *s2);

int					ft_strcmp(const char *s1, const char *s2);
void				ft_putnbr(int n);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
char				*ft_strdup(const char *s1);
size_t				ft_strlen(const char *s);

#endif
