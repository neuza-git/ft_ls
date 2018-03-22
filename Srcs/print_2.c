/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 13:59:52 by tgascoin          #+#    #+#             */
/*   Updated: 2017/02/09 16:27:53 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void		printerror(char *name, int *ern, int s, int mode)
{
	int		i;

	if (*ern == 0 || *ern == 25)
		return ;
	i = 0;
	if (mode == 1 && name[ft_strlen(name) - 1] != '/')
	{
		i = ft_strlen(name);
		while (name[i] != '/' && i > 0)
			i--;
		if (name[i] == '/')
			i++;
	}
	if (s == 1)
	{
		write(1, "\n", 1);
		write(1, name, ft_strlen(name));
		write(1, ":\n", 2);
	}
	write(2, "ft_ls: ", 7);
	write(2, name + i, ft_strlen(name + i));
	write(2, ": ", 2);
	write(2, strerror(*ern), ft_strlen(strerror(*ern)));
	*ern = 0;
	write(2, "\n", 1);
}

void		printlinked(t_file *file, t_args args)
{
	char	*res;

	res = NULL;
	if (args.l)
		write(1, " ", 1);
	write(1, file->name, ft_strlen(file->name));
	if ((file->type == 'x' || file->type == 'l') && args.l)
	{
		res = ft_strnew(file->size);
		readlink(file->npath, res, file->size);
		write(1, " -> ", 4);
		write(1, res, ft_strlen(res));
		free(res);
	}
}

void		printdetail(t_file *file, t_args args)
{
	struct passwd	*u;
	struct group	*g;

	if (args.l)
	{
		u = NULL;
		g = NULL;
		u = getpwuid(file->uid);
		g = getgrgid(file->gid);
		write(1, (file->type == 'x') ? "l" : &(file->type), 1);
		printperm(file->mode, file->npath);
		ft_putnbr(file->nlink);
		write(1, " ", 1);
		(u != NULL) ? write(1, u->pw_name, ft_strlen(u->pw_name)) \
			: write(1, "?", 1);
		write(1, "\t", 1);
		(g != NULL) ? write(1, g->gr_name, ft_strlen(g->gr_name)) \
			: write(1, "?", 1);
		write(1, "\t", 1);
		printsizecol(file);
		write(1, "\t", 1);
		printdate(file->lm);
	}
	printlinked(file, args);
}

int			printlist(t_file *b, int s, t_args args, int total)
{
	if (s == 1)
		write(1, ":\n", 2);
	if (b != NULL && args.l && s != 2)
	{
		write(1, "total ", 6);
		ft_putnbr(total);
		write(1, "\n", 1);
	}
	total = 0;
	while (b != NULL)
	{
		if ((s == 2 && b->type == 'd') || (args.l == 0 && b->type == 'x'))
			b = b->next;
		else
		{
			total++;
			printdetail(b, args);
			write(1, "\n", 1);
			b = b->next;
		}
	}
	return (total);
}
