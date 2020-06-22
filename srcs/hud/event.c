/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:26:48 by calin             #+#    #+#             */
/*   Updated: 2020/06/21 12:36:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		mouse_release(int button, int x, int y, void *param)
{
	t_data *data;

	data = (t_data *)param;
	(void)x;
	(void)y;
	//printf("mouse release\n");
	if (y > 0)
	{
		if (button == 1)
			data->keycode.l_click = 0;
	}
	return (0);
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	//printf("Mouse pressn x %d y %d\n", x, y);
	if (x > 625 && x < 915 && y > 425 && y < 525)
	{
		data->menu_state = 0;
		mlx_mouse_hide(data->mlx_addrs, data->win_addrs);
	}
	if (data->menu_state == 1 && (x > 625 && x < 915 && y > 576 && y < 671))
		printf("Exec editor\n");
	if ((data->menu_state == 1 || data->dead_state == 1) && (x > 625 && x < 915 && y > 727 && y < 822))
		close_game(data);
	if (y > 0)
	{
		if (button == 1)
			data->keycode.l_click = 1;
	}
	return (0);
}

int		key_release(int keycode, void *param)
{
	t_input *data;

	data = (t_input *)param;
	//printf("keyrelease   %d\n", keycode);
	data->data_hud->keys[keycode] = 0;
	//printf("keyrelease2222   %d\n", keycode);
	return (0);
}

int		key_press(int keycode, void *param)
{
	t_input *data;
	data = (t_input *)param;
	printf("keypress %d\n", keycode);

	data->data_hud->keys[keycode] = 1;
	if (keycode == KEY_ESCAPE)
		close_game(data->data_hud);
	if (keycode == KEY_P)
		data->data_hud->menu_state = 1;
	if (keycode == KEY_T)
		dead_anim(data->data_hud);
	if (keycode == KEY_R)
		data->data_hud->keys[keycode] = 1;
	//printf("keypress\n");
	return (0);
}
void check_hooks3(t_input *inputs, int key)
{
	//printf("check hooks 3 %d\n", key);
	if (key == KEY_UP || key == KEY_DOWN || key == KEY_RIGHT || key == KEY_LEFT)
		moove(inputs, key);
	else if (key == KEY_J)
		inputs->debug = (inputs->debug ? 0 : 1);
	else if (key == KEY_W)
		inputs->angley += ROTY;
	else if (key == KEY_S)
		inputs->angley -= ROTY;
	else if (key == KEY_A)
		maprotateallp(inputs->map, (t_fdot){.x = 0, .y = 0, .z = -1}, inputs);
	else if (key == KEY_D)
		maprotateallp(inputs->map, (t_fdot){.x = 0, .y = 0, .z = 1}, inputs);
}

void	check_mouse(t_input *input)
{
	if ( input->data_hud->menu_state == 0 && input->data_hud->keycode.l_click == 1 && cooldown(input->data_hud, 150000)
	&& input->data_hud->first_frame == 1 && input->data_hud->current_ammo >= 0)
		check_fire(input->data_hud, input);
}

void check_hooks2(t_input *input, int key)
{	
	if (key == KEY_1 && (input->data_hud->inventory.slot_one > 0 &&
	input->data_hud->health_bar.shield < 100) && cooldown(input->data_hud, 300000))
	{
		if (input->data_hud->shieldanim.index_shield_anim == -1)
			input->data_hud->shieldanim.index_shield_anim = 0;
		input->data_hud->inventory.slot_one--;
		input->data_hud->health_bar.shield += 10;
	}
	else if (key == KEY_2 && (input->data_hud->inventory.slot_two > 0 &&
	input->data_hud->health_bar.health < 100) && cooldown(input->data_hud, 300000))
	{
		if (input->data_hud->healanim.index_heal_anim == -1)
			input->data_hud->healanim.index_heal_anim = 0;
		input->data_hud->inventory.slot_two--;
		input->data_hud->health_bar.health += 10;
	}
	else
		check_hooks3(input, key);
	
}

int 	mouse_moove(int x, int y, void *param)
{
	t_input *data;
	int dx;
	int dy;

	data = (t_input *)param;
	if (data->data_hud->menu_state != 1)
	{
	//printf("XXXXXX %d YYYYYY %d\n", x, y );

		/*if (y < WIN_SIZE_H / 2)
			data->angley += ROTY;
		else if (y > WIN_SIZE_H / 2)
			data->angley -= ROTY;
		if (x < WIN_SIZE_W / 2)
			maprotateallp(data->map, (t_fdot){.x = 0, .y = 0, .z = 1}, data);
		else if (x > WIN_SIZE_W / 2)
			maprotateallp(data->map, (t_fdot){.x = 0, .y = 0, .z = -1}, data);
*/

		dx = WIN_SIZE_W / 2 - x;
		dy = WIN_SIZE_H / 2 - y;

		if (pow(dx, 2) >= pow(dy, 2))
		{
			if (dx > 0)
				maprotateallp(data->map, (t_fdot){.x = 0, .y = 0, .z = 1}, data);
			else if (dx < 0)
				maprotateallp(data->map, (t_fdot){.x = 0, .y = 0, .z = -1}, data);
		}
		else
		{
			if (dy > 0)
				data->angley += ROTY;
			else if (dy < 0)
				data->angley -= ROTY;
		}
			
		mlx_mouse_move(data->mlx_ad, data->win_ad, WIN_SIZE_W / 2, WIN_SIZE_H / 2);
	}
	//printf("XXXXXX %d YYYYYY %d\n", x, y );
}

void check_hooks(t_input *input)
{
	int i;

	i = -1;
	while(++i < 80000)
	{
		if (input->data_hud->keys[i] == 1)
		{
			if (i == KEY_R && (input->data_hud->current_ammo != 30 ||
			input->data_hud->current_ammo == 0))
			{
				if (input->data_hud->weaponanim.index_rld_anim == -1)
				input->data_hud->weaponanim.index_rld_anim = 0;
					ammo(input->data_hud);
			}
			else
				check_hooks2(input, i);
		}
	}
	input->data_hud->first_frame = 1;
}


int		redraw(void *param)
{
	t_input *input;
	input = (t_input *)param;
	//mlx_clear_window(input->data_hud->mlx_addrs, input->data_hud->win_addrs);
	if (input->data_hud->menu_state != 1 && input->data_hud->dead_state != 1)
	{
		//mlx_mouse_hide(input->mlx_ad, input->win_ad);
		check_hooks(input);
		check_mouse(input);

		maprotateallp(input->map, (t_fdot){.x = 0, .y = 1, .z = 0}, input);

		getobjplans(input);
		get_plans(input->map);

		clear_im(input);
		proj_2d(input->map, input);
		//clear_im(input);
		//check_list_mob(input);
		redefineobj(input);
		redefinevector(input->map);
		if (input->data_hud->current_ammo == 0)
			print_reload(input->data_hud);

		//printf("%f\n", input->angley);
	}
	if (input->angley > M_PI_2)
		input->angley = M_PI_2;
	if (input->angley < -M_PI_2)
		input->angley = -M_PI_2;
	clear_im(input);
	if (input->data_hud->dead_state != 1)
	{
		check_anim(input->data_hud);
		print_hud(input->data_hud);
	}
	return (0);
}
