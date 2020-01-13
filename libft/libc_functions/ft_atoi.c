/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabduras <rabduras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:04:17 by rabduras          #+#    #+#             */
/*   Updated: 2019/11/28 15:51:54 by rabduras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	long	res;
	long	prev;
	int		sign;

	res = 0;
	while (ft_isspace(*str))
		str++;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		prev = res;
		res = 10 * res + (*str++ - '0');
		if (prev > res)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
	}
	return (int)(sign * res);
}
