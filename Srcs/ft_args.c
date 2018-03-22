/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_global.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 12:52:07 by tgascoin          #+#    #+#             */
/*   Updated: 2017/02/08 14:51:30 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void		assign_args(t_args *args, char c, char *pn)
{
	args->l = (c == 'l') ? 1 : args->l;
	args->ru = (c == 'R') ? 1 : args->ru;
	args->a = (c == 'a') ? 1 : args->a;
	args->r = (c == 'r') ? 1 : args->r;
	args->t = (c == 't') ? 1 : args->t;
	if (c != 'l' && c != 'R' && c != 'a' && c != 'r' && c != 't')
	{
		write(2, pn, ft_strlen(pn));
		write(2, ": illegal option -- ", 20);
		write(2, &c, 1);
		write(2, "\n", 1);
		write(2, "usage: ls [-Ralrt] [file ...]\n", 30);
		exit(1);
	}
}

char		ft_gt1(mode_t m)
{
	if ((m & S_IFMT) == S_IFDIR)
		return ('d');
	else if ((m & S_IFMT) == S_IFLNK)
		return ('l');
	else if ((m & S_IFMT) == S_IFCHR)
		return ('c');
	else if ((m & S_IFMT) == S_IFBLK)
		return ('b');
	else if ((m & S_IFMT) == S_IFIFO)
		return ('p');
	else if ((m & S_IFMT) == S_IFREG)
		return ('-');
	else if ((m & S_IFMT) == S_IFSOCK)
		return ('s');
	return ('-');
}

char		ft_gt2(char *npath)
{
	struct stat lfile;

	stat(npath, &lfile);
	return (((S_IFMT & lfile.st_mode) == S_IFDIR) ? 'x' : 'l');
}

t_file		*ft_lcr(char *name, char *path, t_file *prev, int mode)
{
	t_lcr	s;

	s.file = NULL;
	s.tmp = ft_strapp(path, name);
	lstat(s.tmp, &s.dfile);
	s.file = malloc(sizeof(t_file));
	s.file->next = NULL;
	s.file->name = ft_strdup(name);
	s.file->size = s.dfile.st_size;
	s.file->lm = s.dfile.st_mtime;
	s.file->mode = s.dfile.st_mode;
	s.file->nlink = s.dfile.st_nlink;
	s.file->rdev = s.dfile.st_rdev;
	s.file->blks = (ft_strcmp(name, ".") &&\
	ft_strcmp(name, "..")) ? s.dfile.st_blocks : 0;
	s.file->uid = s.dfile.st_uid;
	s.file->gid = s.dfile.st_gid;
	s.file->prev = prev;
	s.file->npath = ft_strapp(path, name);
	s.file->type = (mode == 0 || (s.dfile.st_mode & S_IFMT) != S_IFLNK) ? \
				ft_gt1(s.dfile.st_mode) : ft_gt2(s.file->npath);
	free(path);
	free(s.tmp);
	return (s.file);
}

t_args		get_args(int ac, char **av, int *i)
{
	int		ic;
	int		iv;
	t_args	args;

	ft_init_args(&args, &ic);
	while (ic < ac)
	{
		iv = 0;
		if (av[ic][iv] == '-' && av[ic][iv + 1] == '-'\
				&& av[ic][iv + 2] == '\0')
		{
			ic++;
			break ;
		}
		if (av[ic][iv] == '-' && av[ic][iv + 1] != '\0')
		{
			while (av[ic][++iv] != '\0')
				assign_args(&args, av[ic][iv], av[0]);
			ic++;
		}
		else
			break ;
	}
	*i = ic;
	return (args);
}
