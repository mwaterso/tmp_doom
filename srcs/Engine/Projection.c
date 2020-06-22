/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 19:34:19 by mwaterso          #+#    #+#             */
/*   Updated: 2020/06/18 17:34:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "doom.h"

t_fdot getnew_point(t_fdot frst_point, t_fdot scd_point)
{
	t_fdot a;
	//printf("						new point\n");
	//printf("1=				%lf	%lf	%lf\n", a.x, a.y, a.z);
	//a.y = frst_point.x - (scd_point.y - frst_point.y)/(scd_point.x - frst_point.x);
	a.y = (scd_point.y - frst_point.y) * ((1 - frst_point.x) / (scd_point.x - frst_point.x)) + frst_point.y;
	a.z = (scd_point.z - frst_point.z) * ((1 - frst_point.x) / (scd_point.x - frst_point.x)) + frst_point.z;
	a.x = 1;
	//printf("						new point		%lf	%lf	%lf\n", a.x, a.y, a.z);
	return (a);
}

t_fdot normalise_vec(t_fdot a)
{	
	float magn;

	magn = magnitude(a);
	return ((t_fdot){.x = a.x / magn, .y = a.y / magn, .z = a.z / magn});
}



int get_skytex(t_ray ray, t_sphere s)
{
	float t;
	t_fdot col;
	float u;
	float v;
	float tmp;

	//printf("a\n");

	// t = sqrtf(s.rp2 / (ray.y * ray.y + ray.z * ray.z + 1));
	// col.x = t - s.pos.x;
	// col.y = ray.y * t - s.pos.y;
	// col.z = ray.z * t - s.pos.z;

	//col = normalise_vec(col);
	col = normalise_vec((t_fdot){ray.x, ray.y, ray.z});
	//printf("%f	%f	%f\n", col.x, col.y, col.z);
	tmp = acos(-scale(s.i, col));
	v = tmp / 3.14;
	tmp = scale(col, s.j) / sin(tmp);
	if (tmp < -1.0f)
		tmp = -1.0f;
	tmp = ((float)acos(tmp)) / 6.28;
	u = tmp;

	u = scale(vectoriel_product(s.i, s.j), col) > 0 ? tmp : 1 - tmp;
	if (u < 0)
		u = 0;
	if (checkzero(u - 1, 0.000005))
		u = 0;
	if (checkzero(v - 1, 0.000005))
		v = 0;
		v = 1 - v;
	if(v < 0 || v > 1 | u < 0 || u > 1 || u != u || v != v || __isnanf(u) || __isnanf(v))
	{
		//printf("%f		%f		%f		%f		%f		%f\n", v, u, sin(tmp), scale(s.i, col), scale(s.i, col) / sin(tmp), acos(1));
		return(0xFF);
	}
	//printf("u = %f		v = %f\n", u, v);
	return(s.tex.img[(int)(u * s.tex.width) + (int)((int)(v * s.tex.height) * s.tex.width)]);
}

void get_sky(t_input *data)
{
	int i;

	i = -1;
	//printf("%f\n", scale(data->sky.j, data->sky.i));
	while (++i < data->screensize)
	{
		//0;
		if (data->rays[i].distcolli == -1 /*&& data->im.tab[i] != 0xFF0000*/)
		{
			//data->im.tab[i] = sphere_mapping(data->sky, (t_fdot){.x = 0, .y = 0, .z = 0}, data->rays[i]);
			data->im.tab[i] = get_skytex(data->rays[i], data->sky);
			//printf("b\n");
			//data->im.tab[i] = 0xff;
		}
	}

}

void separate_points(t_poly *map) /* 		 ===>		Ax < 0		<===      */
{
	int j;
	int k;
	int o;

	int i = -1;
	t_fdot tmp;

	//while(++i < 3)
	// 	printf("points: %lf  %lf  %lf\n", map->dot[i].x, map->dot[i].y, map->dot[i].z);
	o = 0;
	k = 0;
	j = -1;
	map->nbr_pprojx = 0;
	while (++j < 3)
	{
		 if (j == 2)
		 	k = 0;
		 else
			k = j + 1;
	 	//printf("%d				points: %lf  %lf  %lf\n", j, map->dot[j].x, map->dot[j].y, map->dot[j].z);
	 	//printf("%d				points2: %lf  %lf  %lf\n", k,  map->dot[k].x, map->dot[k].y, map->dot[k].z);
		if (map->dot[j].x > 0 && map->dot[k].x > 0)
		{
			//printf("1w r : %d x = %f y = %f z = %f\n", j, map->dot[j].x, map->dot[j].y, map->dot[j].z);
			map->projx[o++] = map->dot[j];
		//	printf("1w r : %d x = %f y = %f z = %f\n", j, map->projx[j].x, map->projx[j].y, map->projx[j].z);
		}
		else if (map->dot[j].x > 0 && map->dot[k].x <= 0)
		{
			//printf("2w r : %d x = %f y = %f z = %f\n", j, map->dot[j].x, map->dot[j].y, map->dot[j].z);
			map->projx[o++] = map->dot[j];
			tmp = getnew_point(map->dot[j], map->dot[k]);
			map->projx[o++] = tmp;
		//	printf("2w r : %d x = %f y = %f z = %f\n", j, tmp.x, tmp.y, tmp.z);
		}
		else if (map->dot[j].x <= 0 && map->dot[k].x > 0)
		{
			// printf("3w r : %d x = %f y = %f z = %f\n", j, map->dot[j].x, map->dot[j].y, map->dot[j].z);
			//map->projx[o++] = getnew_point(map->dot[j], map->dot[k]);
			tmp = getnew_point(map->dot[k], map->dot[j]);
			map->projx[o++] = tmp;
			// printf("						new point		%lf	%lf	%lf\n", map->projx[j].x, map->projx[j].y, map->projx[j].z);
			//if(k == NBR_PPOLY - 1)
			//	map->nbr_pprojx = NBR_PPOLY;
		//	printf("3w r : %d x = %f y = %f z = %f\n", j, tmp.x, tmp.y, tmp.z);
		//	printf("3w r : %d x = %f y = %f z = %f\n", j, map->projx[j].x, map->projx[j].y, map->projx[j].z);
		}
		/*else if(map->dot[j].x <= 0 && map->dot[k].x <= 0)
		{
			if(j == 0)
				o = map->nbr_pprojx - 1;
			else
				o = j - 1;
			if (map->dot[o].x > 0)
			{
				// printf("4w r : %d x = %f y = %f z = %f\n", j, map->dot[j].x, map->dot[j].y, map->dot[j].z);
				map->projx[o] = getnew_point(map->dot[j], map->dot[o]);
				// printf("4w r : %d x = %f y = %f z = %f\n", j, map->projx[j].x, map->projx[j].y, map->projx[j].z);
			}*/
	}
		//printf("-----------------   %d   ----------------\n", j);
		//printf("map->nbr_pprojx  = %d\n", map->nget_plansbr_pprojx);
	//}
	//if (map->nbr_pprojx != NBR_PPOLY)
	//	map->nbr_pprojx = map->nbr_p;
	map->nbr_pprojx = o;
	//printf("%d\n", o);
	// int i = -1;
	// while (++i < 4)
		// printf("Dot : %d x = %f y = %f z = %f\n", i, map->dot[i].x, map->dot[i].y, map->dot[i].z);
	// i = -1;
	// while (++i < 4)
		// printf("Sep points  |||   Dot : %d x = %f y = %f z = %f\n", i, map->projx[i].x, map->projx[i].y, map->projx[i].z);
} 


int 	Projxy(t_poly *map, t_input *data)
{
	float fov_x = X_VIEW;
	float fov_z = Z_VIEW;
	float tmp;

	int j = -1;
	int i = -1;
	//while(++i < map->nbr_pprojx)
//	 	printf("%d  projection : %lf  %lf  %lf\n", i, map->projx[i].x, map->projx[i].y, map->projx[i].z);
	while (++j < map->nbr_pprojx)
	{
		//printf("	%d----	PROXY		%lf	%lf	%lf\n", map->nbr_pprojx, map->projx[j].x, map->projx[j].y, map->projx[j].z);
		//printf("x = %lf / %lf - %lf * %d / %lf\n", map->projx[j].z, map->projx[j].x, fov_z / 2, (data->win_h - 1), fov_z);
		// printf("frg %d, %f, %lf\n", data->win_h, fov_z, (float)data->win_h / fov_z);
		//printf("alpha : %f\n", ((map->projx[j].z / map->projx[j].x) - fov_z / 2) * ((float)(data->win_h - 1) / fov_z));
		tmp = map->projx[j].x;
		map->projx[j].x = ((map->projx[j].y / map->projx[j].x) + fov_x / 2) * ((float)(data->win_w - 1) / fov_x);
		map->projx[j].y = (-(map->projx[j].z / tmp) + fov_z / 2) * ((float)(data->win_h - 1) / fov_z);
		//printf("point %d x = %lf y = %lf\n", j, map->projx[j].x, map->projx[j].y);
	}
	if(map->nbr_pprojx)
		return(1);
	return(0);
}

int proj_2d(t_poly *map, t_input *data)
{
	int i;
	int j;
	int ret;

	struct timeval time;
	long o1;
	long o2;
	gettimeofday(&time, NULL);
	o1 = time.tv_usec;
	
	i = -1;
    while (map)
	{
		i++;
		//while(++i < 3)
		//printf("PROJ2d i = %d\n", 
		separate_points(map);

		ret = Projxy(map, data);
		if (ret)
		{

			map->isvisible = 1;
			poly_toboxes(data, map);
			//map->box.amin = (t_dot){.x = 0, .y = 0};
			//map->box.amax = (t_dot){.x = 1899, .y = 599};
		}
		else
		{
			map->isvisible = 0;
			printf("non print : %d\n", i);
		}
		
		map = map->next;
	}

	thread_start(data, data->map);
	get_objpo(data->obj, data);
	//printf("%p		%p\n", data->im.tab, data->im.ad);
	get_sky(data);
	mlx_put_image_to_window(data->mlx_ad, data->win_ad, data->im.ad, 0, 0);
	//sleep(2);
	return(1);
}

int		in_poly(t_poly *poly, t_fdot col)
{
	t_fdot equa1;
	t_fdot equa2;
	t_fdot AP;
	t_fdot BP;
	t_fdot CP;
	t_fdot res;

	AP = getvect(poly->dot[0], col);
	BP = getvect(poly->dot[1], col);
	BP = getvect(poly->dot[2], col);
	/*equa1 = (t_fdot)
	{
		.x = poly->scaleAB,
		.y = poly->scaleABAC,
		.z = -scale(AP, poly->vAB)
	};
	//printf("Equa1\n");

	equa2 = (t_fdot)
	{
		.x = poly->dot[1].zscaleAC,
		.z = -scale(AP, poly->vAC)
	};
	//printf("Equa2\n");
	if (!solv_equ(equa1, equa2, &res))
	{
		printf("RES = %f  %f\n", res.x, res.y);
		return(0);
	}
	res.x = scale(AP, poly->vAB) / poly->scaleAB;
	res.y = scale(AP, poly->vAC) / poly->scaleAC;
	if (res.x >= 0 && res.y >= 0 && res.x + res.y < 1)
	{
		//printf("oui");	
	printf("AB AC   %f %f %f %f %f %f \n", poly->vAB.x,  poly->vAB.y,  poly->vAB.z, poly->vAC.x, poly->vAC.y, poly->vAC.z);
	printf("AP   %f %f %f \n Scale AB %f Scale AC %f Scale ABAC %f \n", AP.x,  AP.y,  AP.z, poly->scaleAB, poly->scaleAC, poly->scaleABAC);
	printf("		%f	%f\n", res.x, res.y);
		return(/*gettex(res.y, res.x, poly)); 0xFF);
	}*/
	if ((scale(vectoriel_product(poly->vAB, AP), vectoriel_product(AP, poly->vAC)) >= 0)
	 && (scale(vectoriel_product(poly->vBA, BP), vectoriel_product(BP, poly->vBC)) >= 0)
	  && (scale(vectoriel_product(poly->vCA, CP), vectoriel_product(CP, poly->vCB))) >= 0)
		return(0xFF);
	return(0);
}

int alkashisolver(t_poly *poly, t_fdot col)
{
	float sum;
	sum = 0;

	float a;
	float b;
	float c;
	float AB = get3ddist(poly->dot[0], poly->dot[1]);
	float BC = get3ddist(poly->dot[1], poly->dot[2]);
	float CA = get3ddist(poly->dot[2], poly->dot[0]);
	float	AP = get3ddist(col, poly->dot[0]);
	float	BP = get3ddist(col, poly->dot[1]);
	float	CP = get3ddist(col, poly->dot[2]);
	
	a = ((-AB * AB + BP * BP + AP * AP) / ( - 2 * BP * AP));

	//printf("0  %f\n", a);
	sum += acos(a);
	sum += acos((-BC * BC + CP * CP + BP * BP ) / (- 2 * BP * CP));
	sum += acos((-CA * CA + CP * CP + AP * AP ) / (- 2 * CP * AP));
	if (sum >= 6.27 && sum <= 6.29)
	{
		printf("1  %f\n", sum);
		return(0xFF);
	}
	return(0);
	
}