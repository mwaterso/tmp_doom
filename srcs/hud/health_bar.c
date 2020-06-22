/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   health_bar.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/20 16:26:59 by calin        #+#   ##    ##    #+#       */
/*   Updated: 2020/03/05 18:23:46 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void	dead_anim(t_data *data)
{
	mlx_mouse_show(data->mlx_addrs, data->win_addrs);
	data->dead_state = 1;
	mlx_clear_window(data->mlx_addrs, data->win_addrs);
	data->name_texture[0] = "srcs/hud/images/dead.xpm";
	data->tab_tex[0].img.ad = mlx_xpm_file_to_image(data->mlx_addrs,
	data->name_texture[0], &data->tab_tex[0].width, &data->tab_tex[0].height);
	data->tab_tex[0].img.tab =
	(int *)mlx_get_data_addr(data->tab_tex[0].img.ad,
	&(data->tab_tex[0].img.bits_per_pixel), &(data->tab_tex[0].img.size_line),
	&(data->tab_tex[0].img.endian));
	mlx_put_image_to_window(data->mlx_addrs, data->win_addrs,
	data->tab_tex[0].img.ad, 0, 0);
	mlx_put_image_to_window(data->mlx_addrs, data->win_addrs,
	data->menu_texture[3].img.ad, data->menu_texture[3].pos_text.x,
	data->menu_texture[3].pos_text.y);
}

void	shield_animation(t_data *data)
{
	mlx_put_image_to_window(data->mlx_addrs, data->win_addrs,
	data->shieldanim.anim_texture[data->shieldanim.index_shield_anim].img.ad,
	0, 0);
	if (cooldown(data, 80000))
		data->shieldanim.index_shield_anim++;
	if (data->shieldanim.index_shield_anim == 4)
		data->shieldanim.index_shield_anim = -1;
}

void	heal_animation(t_data *data)
{
	mlx_put_image_to_window(data->mlx_addrs, data->win_addrs,
	data->healanim.anim_texture[data->healanim.index_heal_anim].img.ad,
	0, 0);
	if (cooldown(data, 80000))
		data->healanim.index_heal_anim++;
	if (data->healanim.index_heal_anim == 4)
		data->healanim.index_heal_anim = -1;
}

void	health(t_data *data)
{
	int	nb_pixel;
	int	health_percentage;
	int	i;

	data->health_bar.y_min = 806;
	data->health_bar.y_max = 831;
	nb_pixel = data->health_bar.x_max - data->health_bar.x_min;
	health_percentage = data->health_bar.x_min + nb_pixel *
	((float)data->health_bar.health / (float)100);
	while (data->health_bar.y_min < data->health_bar.y_max)
	{
		i = 1400;
		while (i < health_percentage)
		{
			mlx_pixel_put(data->mlx_addrs, data->win_addrs, i,
			data->health_bar.y_min, 0xFF0000);
			i++;
		}
		data->health_bar.y_min++;
	}
}

void	shield(t_data *data)
{
	int	nb_pixel;
	int	shield_percentage;
	int	i;

	data->health_bar.y_min = 863;
	data->health_bar.y_max = 886;
	nb_pixel = data->health_bar.x_max - data->health_bar.x_min;
	shield_percentage = data->health_bar.x_min + nb_pixel *
	((float)data->health_bar.shield / (float)100);
	while (data->health_bar.y_min < data->health_bar.y_max)
	{
		i = 1400;
		while (i < shield_percentage)
		{
			mlx_pixel_put(data->mlx_addrs, data->win_addrs, i,
			data->health_bar.y_min, 0x0000FF);
			i++;
		}
		data->health_bar.y_min++;
	}
}
