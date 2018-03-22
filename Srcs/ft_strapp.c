/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strapp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgascoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 15:53:26 by tgascoin          #+#    #+#             */
/*   Updated: 2017/02/09 15:37:40 by tgascoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

char	*ft_strapp(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		fi;

	str = NULL;
	if (s2 == NULL)
		return (ft_strdup(s1));
	if (s1 == NULL)
		return (ft_strdup(s2));
	str = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	fi = 0;
	while (s1[fi] != '\0')
		str[i++] = s1[fi++];
	fi = 0;
	while (s2[fi] != '\0')
		str[i++] = s2[fi++];
	str[i] = '\0';
	return (str);
}
