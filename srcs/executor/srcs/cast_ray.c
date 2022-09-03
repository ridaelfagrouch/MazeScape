/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:46:05 by sahafid           #+#    #+#             */
/*   Updated: 2022/09/03 23:42:44 by sahafid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"


unsigned int	get_texture(t_graph *lst, double j, double x)
{
	int	y;
	int	x2;
	int	color;
	
	y = j * 50;
	x2 = x * 50;
	// printf("%d  %d\n", x2, y);
	color = (int)lst->texture.img_addr[((y * lst->texture.size_line) + (x2 * lst->texture.bpp / 8))];
	return (color);
}

void    draw_rect(int x, int y, int x1, int y1, t_graph *lst, int i)
{
	int				j;
	double			posX;
	double			posY;
	double			wallstripeheight;
	unsigned int	pixel_color;	

	j = x;
	pixel_color = 0;
	posX = 0;
	posY = 0;
	wallstripeheight = y1 - y;
	if (i == 0)
	{
		posX = ((double)lst->raycast.yintercept_horiz / (double)50.0);
		// printf("%f\n", posX);
		while (y < y1)
    	{
    	    while (j < x1)
			{
				posY = ((double)(y1 - y) / (double)wallstripeheight);
				pixel_color = get_texture(lst, posY, posX);
    	        my_mlx_pixel_put(lst ,j, y, pixel_color);
				j++;
			}
			j = x;
    	    y++;
    	}
	}
	else
	{
		posX =  fmod((double)lst->raycast.xintercept_vertic / (double)50, 1.0);
		while (y < y1)
    	{
    	    while (j < x1)
			{
				posY = ((double)(y1 - y) / (double)wallstripeheight);
				pixel_color = get_texture(lst, 1, 1);
    	        my_mlx_pixel_put(lst ,j, y, pixel_color);
				j++;
			}
			j = x;
    	    y++;
    	}
	}
	
}

void	rendringwalls(t_graph *lst, int i, int j)
{
	double	distanceprojectionplane;
	double	wallstripeheight;
	double	distance;
	int		x;

	x = 0;
	if (j == 0)
		distance = distance_points(lst->plyr.x_plyr, lst->raycast.xintercept_horiz, lst->plyr.y_plyr, lst->raycast.yintercept_horiz);
	else
		distance = distance_points(lst->plyr.x_plyr, lst->raycast.xintercept_vertic, lst->plyr.y_plyr, lst->raycast.yintercept_vertic);
	distance = distance * cos(lst->raycast.ray_angle - lst->plyr.rotationangle);
	distanceprojectionplane = ((lst->map.width * lst->map.unit) / 2) / tan(lst->plyr.fov / 2);
	wallstripeheight = (lst->map.unit / distance) * distanceprojectionplane;
	x = 1;
	draw_rect((i * x),
			((lst->map.height * lst->map.unit) / 2) - (wallstripeheight / 2),
			(i * x) + x,
			wallstripeheight + ((lst->map.height * lst->map.unit) / 2) - (wallstripeheight / 2), lst, j);
	
}

void	draw_rays(t_graph *lst, int j, int i)
{
	if (j == 1)
	{
		rendringwalls(lst, i, 1);
		drawline(lst->map.minimap * lst->plyr.x_plyr,
			lst->map.minimap * lst->plyr.y_plyr,
			lst->map.minimap * lst->raycast.xintercept_vertic,
			lst->map.minimap * lst->raycast.yintercept_vertic,
			lst, lst->map.player_color);
	}
	else
	{
		rendringwalls(lst, i, 0);
		drawline(lst->map.minimap * lst->plyr.x_plyr,
			lst->map.minimap * lst->plyr.y_plyr,
			lst->map.minimap * lst->raycast.xintercept_horiz,
			lst->map.minimap * lst->raycast.yintercept_horiz,
			lst, lst->map.player_color);
	}
}

void cast_rays(t_graph *lst)
{
	double	fov;
	int		i;
	int		rays_num;
	int		j;

	lst->raycast.xintercept_horiz = 0;
	lst->raycast.yintercept_horiz = 0;
	lst->raycast.ray_angle = lst->plyr.rotationangle - lst->plyr.fov / 2;
	i = 0;
	j = 0;
	rays_num = lst->map.width * lst->map.unit;
	while (i < rays_num)
	{
		normilizeAngle(&lst->raycast.ray_angle);
		checking_where_plyr_facing(lst);
		horizantal_intersaction(lst);
		vertical_intersaction(lst);
		j = calculate_intersactions(lst);
		draw_rays(lst, j, i);
		lst->raycast.ray_angle += lst->plyr.fov / rays_num;
		i++;
	}
}