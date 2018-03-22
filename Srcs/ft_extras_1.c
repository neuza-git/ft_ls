/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extras.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 13:11:10 by tgascoin          #+#    #+#             */
/*   Updated: 2017/02/09 16:26:23 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_file		*crparam(int ac, int ic, char **av, int *nbd)
{
	t_file	*file;
	t_file	*begin;
	int		dejavu;

	*nbd = 0;
	file = NULL;
	dejavu = 0;
	while (ic < ac)
	{
		if (dejavu++ == 0)
		{
			file = ft_lcr(av[ic++], NULL, NULL, 1);
			begin = file;
		}
		else
			file->next = ft_lcr(av[ic++], NULL, file, 1);
		ft_resl(((dejavu > 1) ? &file : &begin), &errno, &dejavu, nbd);
	}
	return (begin);
}

t_file		*ft_dsort(t_file *begin)
{
	t_sort	s;

	s.r = 0;
	s.file = begin;
	while (s.file->next != NULL)
	{
		if (ft_strcmp(s.file->name, s.file->next->name) > 0)
		{
			s.curr = *s.file;
			s.new = s.file->next;
			s.next = *s.new;
			*s.new = s.curr;
			s.new->next = s.next.next;
			s.new->prev = s.next.prev;
			*s.file = s.next;
			s.file->next = s.curr.next;
			s.file->prev = s.curr.prev;
			s.r = 1;
		}
		s.file = s.file->next;
	}
	return ((s.r == 1) ? ft_dsort(begin) : begin);
}

t_file		*ft_tsort(t_file *begin)
{
	t_sort	s;

	s.r = 0;
	s.file = begin;
	while (s.file->next != NULL)
	{
		if (s.file->lm < s.file->next->lm || (s.file->lm == \
		s.file->next->lm && ft_strcmp(s.file->name, s.file->next->name) > 0))
		{
			s.curr = *s.file;
			s.new = s.file->next;
			s.next = *s.new;
			*s.new = s.curr;
			s.new->next = s.next.next;
			s.new->prev = s.next.prev;
			*s.file = s.next;
			s.file->next = s.curr.next;
			s.file->prev = s.curr.prev;
			s.r = 1;
		}
		s.file = s.file->next;
	}
	return ((s.r == 1) ? ft_tsort(begin) : begin);
}

t_file		*ft_revl(t_file *file)
{
	t_file	*begin;
	t_file	*new;

	if (file->next == NULL)
		return (file);
	new = NULL;
	while (file->next != NULL)
		file = file->next;
	new = file;
	begin = new;
	new->next = file->prev;
	new = new->next;
	while (file->prev != NULL)
	{
		new->next = file->prev;
		new = new->next;
		file = file->prev;
	}
	new->next = file;
	new = new->next;
	new->next = NULL;
	return (begin);
}

void		gothrdirs(t_file *begin, t_args args, int nbd, int nbf)
{
	int dv;

	dv = 0;
	while (begin != NULL)
	{
		if (begin->type == 'd' || (begin->type == 'x' && args.l == 0))
		{
			if (nbd > 1 && nbf == 0 && dv == 0)
			{
				write(1, begin->name, ft_strlen(begin->name));
				write(1, ":\n", 2);
				ft_open(begin->name, 0, args);
			}
			else if (nbd <= 1 && nbf < 1)
				ft_open(begin->name, 0, args);
			else
				ft_open(begin->name, 1, args);
		}
		dv++;
		begin = begin->next;
	}
}
