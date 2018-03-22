/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <tgascoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 13:57:35 by tgascoin          #+#    #+#             */
/*   Updated: 2017/02/10 11:54:22 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void		printexacl(char *npath)
{
	acl_t	acl;
	ssize_t	rxattr;

	acl = NULL;
	acl = acl_get_file(npath, ACL_TYPE_EXTENDED);
	rxattr = listxattr(npath, NULL, 0, XATTR_NOFOLLOW);
	if (rxattr > 0)
		write(1, "@", 1);
	else if (acl != NULL && rxattr <= 0)
		write(1, "+", 1);
	else
		write(1, " ", 1);
}

void		printperm(mode_t m, char *npath)
{
	write(1, (m & S_IRUSR) ? "r" : "-", 1);
	write(1, (m & S_IWUSR) ? "w" : "-", 1);
	write(1, (m & S_IXUSR) ? "x" : "-", 1);
	write(1, (m & S_IRGRP) ? "r" : "-", 1);
	write(1, (m & S_IWGRP) ? "w" : "-", 1);
	write(1, (m & S_IXGRP) ? "x" : "-", 1);
	write(1, (m & S_IROTH) ? "r" : "-", 1);
	write(1, (m & S_IWOTH) ? "w" : "-", 1);
	if ((m & S_ISVTX) && (m & S_IXOTH))
		write(1, "t", 1);
	else if (!(m & S_ISVTX) && (m & S_IXOTH))
		write(1, "x", 1);
	else
		write(1, "-", 1);
	printexacl(npath);
	write(1, " ", 1);
}

void		printdate(time_t t)
{
	char	date[13];
	time_t	now;
	int		i;
	int		otsm;

	now = time(NULL);
	otsm = ((int)now - 15780000 >= (int)t) ? 11 : 12;
	i = -1;
	while (++i < otsm)
	{
		date[i] = (ctime(&t) + 4)[i];
		if (otsm == 11 && i == 6)
			break ;
	}
	if (otsm == 11)
	{
		i++;
		otsm = 0;
		date[i++] = ' ';
		while (otsm < 4)
			date[i++] = (ctime(&t) + 20)[otsm++];
	}
	date[i] = '\0';
	write(1, date, ft_strlen(date));
}

void		printsizecol(t_file *file)
{
	struct stat	dfile;

	write(1, " ", 1);
	if (file->type == 'd' || file->type == '-' \
			|| file->type == 'l' || file->type == 'p' || file->type == 'x')
		ft_putnbr(file->size);
	else
	{
		lstat(file->npath, &dfile);
		ft_putnbr(major(file->rdev));
		write(1, ",\t", 2);
		ft_putnbr(minor(file->rdev));
	}
}
