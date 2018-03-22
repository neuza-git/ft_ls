/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extras2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 14:31:11 by tgascoin          #+#    #+#             */
/*   Updated: 2017/02/09 15:25:40 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void		ft_resl(t_file **file, int *ern, int *dv, int *nbd)
{
	if (*ern != 0 && *ern != 25)
	{
		if (*dv > 1)
		{
			printerror((*file)->next->name, &errno, 0, 1);
			free((*file)->next);
			(*file)->next = NULL;
		}
		else
		{
			printerror((*file)->name, &errno, 0, 1);
			free(*file);
			*file = NULL;
			*dv -= 1;
		}
		*ern = 0;
	}
	else
	{
		if (*dv > 1)
			*file = (*file)->next;
		if ((*file)->type == 'd' || (*file)->type == 'x')
			*nbd += 1;
	}
}

void		ft_init_cr(int *blksum, int *nope, t_file **file, t_file **begin)
{
	*blksum = 0;
	*nope = 0;
	*file = NULL;
	*begin = NULL;
}

t_file		*ft_cr(DIR *adir, t_args args, char *name, int *total)
{
	t_ft_cr s;

	ft_init_cr(&s.blksum, &s.nope, &s.f, &s.begin);
	while ((s.sdir = readdir(adir)) != NULL)
	{
		if (s.sdir->d_name[0] != '.' || args.a == 1)
		{
			if (s.nope++ == 0)
			{
				s.f = ft_lcr(s.sdir->d_name, ft_strapp(name, "/"), NULL, 0);
				s.blksum += s.f->blks;
				s.begin = s.f;
			}
			else
			{
				s.f->next = ft_lcr(s.sdir->d_name,\
						ft_strapp(name, "/"), s.f, 0);
				s.f = s.f->next;
				s.blksum += s.f->blks;
			}
		}
	}
	*total = s.blksum;
	closedir(adir);
	return (s.begin);
}

void		ft_init_args(t_args *args, int *ic)
{
	args->l = 0;
	args->ru = 0;
	args->a = 0;
	args->r = 0;
	args->t = 0;
	*ic = 1;
}
