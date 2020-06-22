/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:17:42 by mwaterso          #+#    #+#             */
/*   Updated: 2020/06/21 12:39:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "doom.h"

/*void visual(int i, t_input *data, float rotx, float rotz)
{
    float a;  
    float b;
    float dist;
}*/


/*t_ray   process_ray(float  rotx, float rotz, t_fdot pos_player)
{
    return (ray);
}*/

/*t_dot define_way(t_fdot angle)
{
    t_dot way;
    if (angle.x > M_PI_2 && angle.x < m_3PI_2)
        way.x = -1;
    else
        way.x = 1;
    if (angle.y > M_PI_2 && angle.y < m_3PI_2)
        way.x = -1;
    else
        way.x = 1;
    if (angle.x > M_PI_2 && angle.x < m_3PI_2)
        way.x = -1;
    else
        way.x = 1; 
}*/


/*t_fov *creat_fov(t_input *data)
{
    int i;
    t_fov *new;
    int max;
    int max_min;
    int thread;
    max = data->win_h * data->win_w;
    max_min = max - 1;
    thread = 0;
    new = malloc(sizeof(t_fov));
    data->fov = new;
    i = -1;getcolli
    while(++i < max)
    {
        if (!(i = max_min))
            new->next = malloc(sizeof(t_fov));
        if (i = thread * (data->win_h * data->win_w / NB_THREAD))
        {
            data->thread_tab[thread].fov = new;
            thread++;
        }
        new->rotx = data->alpha_x + (X_VIEW / 2 - ((data->win_w - i % data->win_w) / data->win_w) * X_VIEW);
        new->roty = data->alpha_z + (Z_VIEW / 2 - ((data->win_h - i / data->win_h) / data->win_h) * Z_VIEW);
        new = new->next;
    }
}*/


t_ray *tab_ray(int nbrpix, t_input *data)
{
    t_ray *new;
    int i;

    i = 0;
    new = malloc(sizeof(t_ray) * nbrpix);
    while (i < data->screensize)
    {
        new[i].x = 1;
       //new[i].y = (X_VIEW / 2 - (float)(i % data->win_w / data->win_w) * X_VIEW);
        //[i].z = (Z_VIEW / 2 - ((data->win_h - (float)(i / data->win_h)) / data->win_h) * Z_VIEW);
        new[i].y = (-X_VIEW / 2 + i % data->win_w / (float)data->win_w * X_VIEW);
        new[i].z = (Z_VIEW / 2 - i / data->win_w / (float)data->win_h * Z_VIEW);
	    //printf("--%lf	%lf	%lf\n", new[i].x, new[i].y, new[i].z);
		new[i].distcolli = -1;
        new[i].dp1 = 0;
        new[i].dp2 = 0;
        i++;
    }
    return (new);
}

int cp_dots(t_poly *poly)
{
    int i;
    float xmax;
    float ymax;
    while(poly)
    {
        i = -1;

        xmax = poly->tex_tab.width - 1;
        ymax = poly->tex_tab.height - 1;

		poly->ab = get2dvect((t_2d){.x = poly->cord[0].x * xmax, .y = poly->cord[0].y * ymax}, (t_2d){.x = poly->cord[1].x * xmax, .y = poly->cord[1].y * ymax});
		poly->ac = get2dvect((t_2d){.x = poly->cord[1].x * xmax, .y = poly->cord[1].y * ymax}, (t_2d){.x = poly->cord[2].x * xmax, .y = poly->cord[2].y * ymax});
        poly->a2d.x = poly->cord[0].x * xmax;
        poly->a2d.y = poly->cord[0].y * ymax;
      //  printf("coord a %f %f b %f %f c %f %f\n", poly->cord[0].x, poly->cord[0].y, poly->cord[1].x, poly->cord[1].y, poly->cord[2].x, poly->cord[2].y);
       // printf("xm %f ym %f, adx %f ady %f\n", xmax, ymax, poly->a2d.x, poly->a2d.y);
       //f printf("Ab %f %f Ac %f %f\n", poly->ab.x, poly->ab.y, poly->ac.x, poly->ac.y);
        //sleep(15);
		// poly->vAB = fix_vec(getvect(poly->dot[0], poly->dot[1]));
		// poly->vBC = fix_vec(getvect(poly->dot[1], poly->dot[2]));
        // poly->vAC = fix_vec(getvect(poly->dot[0], poly->dot[2]));
        poly->vAB = getvect(poly->dot[0], poly->dot[1]);
		poly->vBC = getvect(poly->dot[1], poly->dot[2]);
        poly->vAC = getvect(poly->dot[0], poly->dot[2]);
        poly->vBA = getvect(poly->dot[1], poly->dot[0]);
		poly->vCB = getvect(poly->dot[2], poly->dot[1]);
        poly->vCA = getvect(poly->dot[2], poly->dot[0]);
        poly->scaleAB = scale(poly->vAB, poly->vAB);
        poly->scaleAC = scale(poly->vAC, poly->vAC);
        poly->scaleABAC = scale(poly->vAB, poly->vAC);
        while(++i < 4)
            poly->rotx[i] = poly->dot[i];
        poly = poly->next;
    }
    return(1);
}

void cp_dotsobj(t_object *obj)
{
    while (obj)
    {
        cp_dots(obj->poly);
        obj->posrx = obj->pos;
        obj->exist = 1;
        obj->hp = 100;
        get_plans(obj->poly);
        printf("AB %f %f %f\n", obj->poly->next->vAB.x, obj->poly->next->vAB.y, obj->poly->next->vAB.z);
       // printf("AC %f %f %f\n", obj->poly->vAB.x, obj->poly->vAB.y, obj->poly->vAB.z);
       //sleep(10);
    obj = obj->next;
    }

}

void init_var3 (t_input *data)
{
    printf("here\n");
    data->sky.tex.tab =  mlx_xpm_file_to_image(data->mlx_ad, "./texture/skybox.xpm", &(data->sky.tex.width), &(data->sky.tex.height));
   // printf("End     %p\n", data->sky.tex.tab);
    data->sky.tex.img = (unsigned int *)mlx_get_data_addr(data->sky.tex.tab, &(data->sky.tex.bpp), &(data->sky.tex.s_l), &(data->sky.tex.endian));
    printf("End\n");
    data->sky.r = R_SKYBOX;
    data->sky.rp2 = data->sky.r * data->sky.r;
    data->sky.veci = (t_fdot){.x = 0, .y = 0, .z = 1};
    data->sky.vecj = (t_fdot){.x = 1, .y = 0, .z = 0};
    data->sky.pos = (t_fdot){.x = 0, .y = 0, .z = 0};
    data->sky.i = (t_fdot){.x = 0, .y = 0, .z = 1};
    data->sky.j = (t_fdot){.x = 1, .y = 0, .z = 0};
    printf("End\n");
}

void        init_var2(t_data *data)
{
    int i;

    i = -1;
    while (++i < 280)
        data->keys[i] = -1;
    data->inventory = (t_inventory){.slot_one = 7, .slot_two = 8,
	.slot_three = 1, .slot_four = 0};
	data->health_bar = (t_life){.x_min = 1400, .x_max = 1556, .y_min = 813,
	.y_max = 831, .health = 20, .shield = 0};
	data->current_ammo = 30;
	data->total_ammo = 256;
	data->healanim.index_heal_anim = -1;
	data->shieldanim.index_shield_anim = -1;
	data->weaponanim.index_wpn_anim = -1;
	data->weaponanim.index_rld_anim = -1;
	data->menu_state = 1;
	data->first_frame = 0;
}

void		init_var(t_input *inputs, t_data *data)
{
	inputs->win_w = WIN_SIZE_W;
	inputs->win_h = WIN_SIZE_H;
    inputs->angley = 0;
    inputs->debug = 0;
    inputs->nbrtour = 0;

    inputs->screensize = inputs->win_h * inputs->win_w;
	//fill_texture_tab(inputs);
	inputs->rotz = define_zRotMat();
	inputs->minrotz = define_minzRotMat();
	inputs->mlx_ad = mlx_init();
	inputs->win_ad = mlx_new_window(inputs->mlx_ad, inputs->win_w,
	inputs->win_h, "Doom Nukem");
    data->mlx_addrs = inputs->mlx_ad;
    data->win_addrs = inputs->win_ad;
    printf("%p\n", data->mlx_addrs);
	inputs->im.ad = mlx_new_image(inputs->mlx_ad, inputs->win_w, inputs->win_h);
	inputs->im.tab = (int *)mlx_get_data_addr(inputs->im.ad,
	&(inputs->im.bits_per_pixel), &(inputs->im.size_line),
	&(inputs->im.endian));
    init_var3(inputs);
    init_var2(data);
}

/*int Debugfct(t_poly *poly)
{    
    t_fdot a = (t_fdot){.x = 1, .y = 2, .z = 3};
    t_fdot b = (t_fdot){.x = 1, .y = 7, .z = 2};
    t_fdot c = (t_fdot){.x = 1, .y = 8, .z = 3};
    // t_fdot a = (t_fdot){.x = 1, .y = 1, .z = 2};
    // t_fdot b = (t_fdot){.x = 1, .y = -0.5, .z = 2};
    // t_fdot c = (t_fdot){.x = 1, .y = 0, .z = -2};
    t_fdot tab[NBR_PPOLY];
    poly->next = NULL;
    printf("seg?\n");
    poly->dot[0] = a;
    poly->dot[1] = b;
    poly->dot[2] = c;
    poly->nbr_p = 3;
    return(1);
}*/

int	keyboard_test(int key, t_input *inputs)
{
    if (key == 32)
    {
        mlx_clear_window(inputs->data_hud->mlx_addrs, inputs->data_hud->win_addrs);
        mlx_put_image_to_window(inputs->data_hud->mlx_addrs, inputs->data_hud->win_addrs, inputs->map->tex_tab.tab, 0, 0);
        dprintf(1, "%s\n", inputs->map->tex);
        if (inputs->map->next)
            inputs->map = inputs->map->next;
        else
             return 0;
    }
    if (key == 98)
    {
        if (!inputs->obj->poly->mtl.tex.tab)
        {
            dprintf(1, "nop\n");
            return 0;
        }
        mlx_clear_window(inputs->data_hud->mlx_addrs, inputs->data_hud->win_addrs);
        mlx_put_image_to_window(inputs->data_hud->mlx_addrs, inputs->data_hud->win_addrs, inputs->obj->poly->tex_tab.tab, 0, 0);
        dprintf(1, "%s\n", "bla");
        if (inputs->obj->poly->next)
            inputs->obj->poly = inputs->obj->poly->next;
        else if (inputs->obj->next)
            inputs->obj = inputs->obj->next;
        else
             return 0;
    }
    return 0;
}

/*void printobj(t_input *data)
{
    t_object *obj;

    obj = data->obj;
    while(obj->poly)
    {
        obj->poly->

    }


}*/

int main(int c, char **v)
{
    t_input data;
    t_data  input;
    //t_poly  *poly;
    data.data_hud = &input;
	data.fps = 0;
	int i = -1;
    (void)c;
    //poly = (t_poly *)malloc(sizeof(t_poly));
    //data.nbrpoly = Debugfct(poly);
    init_var(&data, &input);
    if (load_texture_data(&input) == -1)
	{
		ft_putendl("Texture error");
		return (0);
	}
    gettimeofday(&input.timer.save_time, NULL);
    //printf("PARSING\n");
	if(!(data.map = parsing_poly(v[1], &data)))
		return(0);
 	//printf("PARSING END\n");
	//fprint_parse_obj(data.obj);
	//mlx_put_image_to_window(data.map->tex_tab.tab, data.win_ad, data.im.ad, 0, 0);
	//mlx_put_image_to_window(data.mlx_ad, data.win_ad, data.map->tex_tab.tab, 0, 0);
	/*-----------------------------------------*/

    /*data.map->next->texture.ad = data.map->tex_tab.tab;
    data.map->next->texture.tab = (int *)mlx_get_data_addr(data.map->texture.ad, &(data.map->texture.bits_per_pixel), &(data.map->texture.size_line), &(data.map->texture.endian));
    
    data.map->next->next->texture.ad = data.map->tex_tab.tab;
    data.map->next->next->texture.tab = (int *)mlx_get_data_addr(data.map->texture.ad, &(data.map->texture.bits_per_pixel), &(data.map->texture.size_line), &(data.map->texture.endian));*/
	/*-----------------------------------------*/
    //printf("end parsing\n");
	while(++i < 3)
		printf("%lf  %lf  %lf\n", data.map->dot[i].x, data.map->dot[i].y, data.map->dot[i].z);
   // printf("init vars\n");
    //printf("h,w    %d      %d\n", data.map->tex_tab.height, data.map->tex_tab.width);
    cp_dots(data.map);
    cp_dotsobj(data.obj);
    //printf("vect ab  x= %f      y = %f\n", data.map->ab.x, data.map->ab.y);
    //printf("vect bc  x= %f      y = %f\n", data.map->ac.x, data.map->ac.y);
    //printf("ray init\n");
    data.rays = tab_ray(data.win_h * data.win_w, &data);
    //printf("ray init end\n");
    get_plans(data.map);
   // printf("plans init end\n");
   // thread_start(&data);
    //proj_2d(data.map, &data);
    //printf("proj2d end\n");
	//input.keys[0] = 0;
	// printf("keys\n");
	//redraw(&data);
	//mlx_hook(data.win_ad, 2, 1L << 0, keyboard_test, &data);
	//mlx_mouse_move(data.mlx_ad, data.win_ad, WIN_SIZE_W / 2, WIN_SIZE_H / 2);

	//mlx_mouse_hide(data.mlx_ad, data.win_ad);

	mlx_hook(data.win_ad, 6, 1L << 6, mouse_moove, &data);
	 mlx_hook(data.win_ad, 2, 1L << 0, key_press, &data);
	 mlx_hook(data.win_ad, 3, 1L << 1, key_release, &data);
	 mlx_hook(data.win_ad, 4, 1L << 2, mouse_press, &input);
	 mlx_hook(data.win_ad, 5, 1L << 3, mouse_release, &input);
	//mlx_hook(data.win_ad, 2, 0, key_press, &data);
	//mlx_key_hook(data.win_ad, key_release, &data);
	//mlx_mouse_hook(data.win_ad, mouse_moove, &input);

	 mlx_loop_hook(data.mlx_ad, redraw, &data);
	printf("redraw\n");
	//mlx_hook(inputs.win_ad, 17, 0, &ft_close, &inputs);
	mlx_loop(data.mlx_ad);
    return(0);
}

