/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizantal_inter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:30:13 by sahafid           #+#    #+#             */
/*   Updated: 2022/09/26 16:42:37 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	horizantal_intersaction(t_graph *lst)
{
	int check;
	int	sprite;

	check = 0;
	sprite = 1;
	lst->sprite.horiz_intersaction = 0;
	lst->raycast.horiz_intersaction = 0;
	lst->raycast.yintercept_horiz = floor(lst->plyr.y_plyr / lst->map.unit) * lst->map.unit;
	if (lst->raycast.facingdown)
		lst->raycast.yintercept_horiz += lst->map.unit;
	lst->raycast.xintercept_horiz = lst->plyr.x_plyr + (lst->raycast.yintercept_horiz - lst->plyr.y_plyr) / tan(lst->raycast.ray_angle);
	lst->raycast.ystep = lst->map.unit;
	if (lst->raycast.facingup)
		lst->raycast.ystep *= -1;
	lst->raycast.xstep = lst->map.unit / tan(lst->raycast.ray_angle);
	if (lst->raycast.facingleft && lst->raycast.xstep > 0)
		lst->raycast.xstep *= -1;
	if (lst->raycast.facingright && lst->raycast.xstep < 0)
		lst->raycast.xstep *= -1;
	if (lst->raycast.facingup)
		check = 1;
	while ((lst->raycast.xintercept_horiz >= 0 && lst->raycast.xintercept_horiz <= lst->map.unit * lst->map.width) && (lst->raycast.yintercept_horiz >= 0 && lst->raycast.yintercept_horiz <= lst->map.unit * lst->map.height))
	{
		if (check_wall(lst, lst->raycast.xintercept_horiz, lst->raycast.yintercept_horiz - check))
		{
			lst->raycast.horiz_intersaction = 1;
			return ;
		}
		else if (check_sprite(lst, lst->raycast.xintercept_horiz, lst->raycast.yintercept_horiz - check) == 1 && sprite == 1)
		{
			lst->sprite.horiz_intersaction = 1;
			lst->sprite.spritefoundhorz = 1;
			sprite = 0;
			lst->sprite.xintercept_horiz = lst->raycast.xintercept_horiz;
			lst->sprite.yintercept_horiz = lst->raycast.yintercept_horiz;
			lst->raycast.xintercept_horiz += lst->raycast.xstep;
			lst->raycast.yintercept_horiz += lst->raycast.ystep;
		}
		else if (check_sprite(lst, lst->raycast.xintercept_horiz, lst->raycast.yintercept_horiz - check) == 2)
		{
			lst->door.horiz_intersaction = 1;
			lst->door.foundoor = 1;
			lst->door.xintercept_horiz = lst->raycast.xintercept_horiz;
			lst->door.yintercept_horiz = lst->raycast.yintercept_horiz;
			lst->raycast.xintercept_horiz += lst->raycast.xstep;
			lst->raycast.yintercept_horiz += lst->raycast.ystep;
		}
		else
		{
			lst->raycast.xintercept_horiz += lst->raycast.xstep;
			lst->raycast.yintercept_horiz += lst->raycast.ystep;
		}
	}
	lst->raycast.horiz_intersaction = 0;
	lst->door.horiz_intersaction = 0;
	if (sprite)
	{
		lst->sprite.horiz_intersaction = 0;
		lst->sprite.spritefoundhorz = 0;
	}
}
