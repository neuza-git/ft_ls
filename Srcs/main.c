/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 10:22:34 by tgascoin          #+#    #+#             */
/*   Updated: 2017/02/09 16:34:00 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void		ft_l(char *name, t_file *file, t_args args)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = NULL;
	tmp2 = NULL;
	tmp1 = ft_strapp(name, "/");
	name = (name[0] == '/' && name[1] == '\0') ? name : tmp1;
	while (file != NULL)
	{
		if (file->type == 'd' && args.ru && ft_strcmp(file->name, ".") \
				&& ft_strcmp(file->name, ".."))
		{
			tmp2 = ft_strapp(name, file->name);
			ft_open(tmp2, 1, args);
			ft_strdel(&tmp2);
		}
		file = file->next;
	}
	ft_strdel(&tmp1);
}

void		ft_read(DIR *adir, t_args args, char *name, int s)
{
	int		total;
	t_file	*file;
	t_file	*tmp;

	file = NULL;
	total = 0;
	file = ft_cr(adir, args, name, &total);
	if (file != NULL)
		file = (args.t == 1) ? ft_tsort(file) : ft_dsort(file);
	if (args.r == 1 && file != NULL)
		file = ft_revl(file);
	if (s == 1)
		write(1, "\n", 1);
	if (s == 1)
		write(1, name, ft_strlen(name));
	printlist(file, s, args, total);
	ft_l(name, file, args);
	while ((tmp = file) != NULL)
	{
		file = file->next;
		free(tmp->name);
		free(tmp->npath);
		free(tmp);
	}
}

void		ft_open(char *name, int s, t_args args)
{
	DIR		*adir;

	adir = NULL;
	adir = opendir(name);
	if (adir == NULL)
	{
		printerror(name, &errno, s, 1);
		return ;
	}
	ft_read(adir, args, name, s);
}

int			main(int ac, char **av)
{
	int		ic;
	int		nbd;
	t_args	args;
	t_file	*file;

	args = get_args(ac, av, &ic);
	if (ac == ic)
	{
		ft_open(".", 0, args);
		exit(0);
	}
	file = crparam(ac, ic, av, &nbd);
	if (file != NULL)
		file = (args.t == 1) ? ft_tsort(file) : ft_dsort(file);
	if (args.r == 1 && file != NULL)
		file = ft_revl(file);
	gothrdirs(file, args, nbd, printlist(file, 2, args, 0));
	return (0);
}
