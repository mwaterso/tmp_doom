/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 14:48:06 by mwaterso          #+#    #+#             */
/*   Updated: 2020/06/21 00:52:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "doom.h"

int checkzero(float a, float inter)
{
	//printf("??%f		%d\n", a, (a < (0 + inter) && a > (0 - inter)) ? 1 : 0);
	return((a < (0 + inter) && a > (0 - inter)) ? 1 : 0);
}

int		tallnomin(int a, int b)
{
	int	e;
	int	r;

	e = a;
	r = b;
	if (a < 0)
		a *= -1;
	if (b < 0)
		b *= -1;
	if (a >= b)
		return (a);
	return (b);
}

void	print_line(t_input *input, t_dot a, t_dot b, int color)
{
	float	dx;
	float	dy;
	int		tall;
	int		i;

	i = 0;
	if (b.x == a.x && b.y == a.y)
		return ;
	tall = tallnomin(a.y - b.y, a.x - b.x);
	dx = (float)(a.x - b.x) / tall;
	dy = (float)(a.y - b.y) / tall;
	while (i++ < tall)
	{
		if ((i * dx + b.x) >= 0 && (i * dx + b.x) < input->win_w &&
		(i * dy + b.y) < input->win_h && (i * dy + b.y) >= 0)
			input->im.tab[((int)(i * dx + b.x) +
			(int)(i * dy + b.y) * (input->im.size_line / 4))] = color;
	}
}

int poly_toboxes (t_input *data, t_poly *poly)
{
	int i;
	i = -1;
	poly->box.amax.x = (int)poly->projx[0].x;
	poly->box.amax.y = (int)poly->projx[0].y;
	poly->box.amin.x = (int)poly->projx[0].x;
	poly->box.amin.y = (int)poly->projx[0].y;
	//printf("NBR POINTS %d			%d	%d\n%d	%d\n", poly->nbr_pprojx, poly->box.amin.x, poly->box.amin.y, poly->box.amax.x, poly->box.amax.y);
	//while(++i < poly->nbr_pprojx)
	// 	printf("%d  projection : %lf  %lf  %lf\n", i, poly->projx[i].x, poly->projx[i].y, poly->projx[i].z);
	i = -1;
	while (++i < poly->nbr_pprojx)
	{
		if (poly->projx[i].x > poly->box.amax.x)
			poly->box.amax.x = poly->projx[i].x;
		if (poly->projx[i].y > poly->box.amax.y)
			poly->box.amax.y = poly->projx[i].y;

		if (poly->projx[i].x < poly->box.amin.x)
			poly->box.amin.x = poly->projx[i].x;
		if (poly->projx[i].y < poly->box.amin.y)
			poly->box.amin.y = poly->projx[i].y;


	}
		if (data->win_w <= poly->box.amax.x)
			poly->box.amax.x = data->win_w - 1;
		if (data->win_h <= poly->box.amax.y)
			poly->box.amax.y = data->win_h - 1;
		if (data->win_w <= poly->box.amin.x)
			poly->box.amin.x = data->win_w - 1;
		if (data->win_h <= poly->box.amin.y)
			poly->box.amin.y = data->win_h - 1;
		if (0 > poly->box.amin.x)
			poly->box.amin.x = 0;
		if (0 > poly->box.amin.y)
			poly->box.amin.y = 0;
		if (0 > poly->box.amax.x)
			poly->box.amax.x = 0;
		if (0 > poly->box.amax.y)
			poly->box.amax.y = 0;
		//printf("min-%d	%d\nmax-%d	%d\n", poly->box.amin.x, poly->box.amin.y, poly->box.amax.x, poly->box.amax.y);
	//	print_line(data, poly->box.amin, poly->box.amax, 0xff0000);
	return (1);
}

int gettex(float ab, float bc, t_poly *poly)
{	
	int ret;
	int max;
	max = poly->tex_tab.width * poly->tex_tab.height - 1;
//	printf("1\n");
//	printf("2\n");
	ret = (int)(((float)(ab * poly->ab.x) + (float)(bc * poly->ac.x) + poly->a2d.x) + (int)((float)(ab * poly->ab.y) + (float)(bc * poly->ac.y) + poly->a2d.y) * (poly->tex_tab.width));
	if (ret > max)
		ret = max;
	else if (ret < 0)
	{
		//printf("ret = %d  y = %d	x = %f\n", ret, (int)((float)(ab * poly->ab.y) + (float)(bc * poly->bc.y) + poly->a2d.y), (ab * poly->ab.x) + (float)(bc * poly->bc.x) + poly->a2d.x);
		//printf("ab = %f		bc = %f		ab.x = %f ab.y = %f  bc.x = %f bc.y = %f   a.x = %f a.y = %f\n", ab, bc, poly->ab.x, poly->ab.y, poly->bc.x, poly->bc.y, poly->a2d.x, poly->a2d.y);
		ret = 0;
	}
	//printf("%d\n", poly->tex_tab.img[ret]);
	return(poly->tex_tab.img[ret]);
}


int checkbary(t_poly *poly, t_fdot *colli)
{
	float alpha; 
	float beta;
	t_fdot	AP;
	//return (0xff0000);
	//printf("chexk bary\n");
	int i = -1;
	//return(0xFF);
	/*if(poly->debug)
	{

		while(++i < 3)
		printf("%d  t checkbary( checkbary(heckbary : %lf  %lf  %lf\n", i, poly->dot[i].x, poly->dot[i].y, poly->dot[i].z);
		exit(0);
	}*/
	//if(frst)
	//{
	//	poly->vAB = getvect(poly->dot[0], poly->dot[1]);
	//	poly->vBC = getvect(poly->dot[1], poly->dot[2]);
	//}

        //poly->den1 = (-poly->vAB.y * poly->vBC.z + poly->vBC.y * poly->vAB.z);
      //  poly->den2 =data->rays[i].distcolli (-poly->vAB.x * poly->vBC.y + poly->vBC.x * poly->vAB.y);
       // poly->den3 = (-poly->vAB.z * poly->vBC.x + poly->vBC.z * poly->vAB.x);
	AP = getvect(poly->dot[0], *colli);
	//printf("colli = %lf    %lf	%lf\n", colli->x, colli->y, colli->z);
	/*if (checkzero(AB.z, 0.00001))
	{
		printf("AB = %lf    %lf	%lf\n", AB.x, AB.y, AB.z);
		printf("BC = %lf    %lf	%lf\n", BC.x, BC.y, BC.z);
	}*/
	//printf("AP = %lf    %lf	%lf\n", poly->vAP.x, poly->vAP.y, poly->vAP.z);
	//printf("%lf\n", (-AB.x * BC.y + BC.x * AB.y));

	if (!(checkzero(poly->den1, 0.0001)))
		alpha = (poly->vBC.y * AP.z - poly->vBC.z * AP.y) / poly->den1;
	else if (!(checkzero(poly->den2, 0.0001)))
		alpha = (poly->vBC.x * AP.y - poly->vBC.y * AP.x) / poly->den2;
	else if (!(checkzero(poly->den3, 0.0001)))
		alpha = (poly->vBC.z * AP.x - poly->vBC.x * AP.z) / poly->den3;



	/*if ((checkzero(poly->vAB.x, 0.0001) && checkzero(poly->vBC.x , 0.0001)) || (checkzero(poly->vAB.y, 0.0001) && checkzero(poly->vAB.x , 0.0001)))
	{
		//printf("3 = den %lf 	num %lf\n", (poly->vBC.y * AP.z - poly->vBC.z * AB.y), (-AB.y * poly->vBC.z + poly->vBC.y * AB.z));
		alpha = (poly->vBC.y * AP.z - poly->vBC.z * AP.y) / poly->den1;
	}
	else if (checkzero(poly->vAB.z, 0.0001) && checkzero(poly->vBC.z , 0.0001))
	{
	///	printf("1 = den %lf 	num %lf\n", (poly->vBC.x * AP.y - poly->vBC.y * AB.x), (-AB.x * poly->vBC.y + poly->vBC.x * AB.y));
		alpha = (poly->vBC.x * AP.y - poly->vBC.y * AP.x) / poly->den2;
	}
	else if (checkzero(poly->vAB.y, 0.0001) && checkzero(poly->vBC.y , 0.0001))
	{
	//	printf("2 = den %lf 	num %lf\n", (poly->vBC.z * AP.x - poly->vBC.x * AB.z), (-AB.z * poly->vBC.x + poly->vBC.z * AB.x));
		alpha = (poly->vBC.z * AP.x - poly->vBC.x * AP.z) / poly->den3;
	}
	else if (!checkzero(-poly->vAB.x * poly->vBC.y + poly->vBC.x * poly->vAB.y, 0.0001))
	{
		//printf("4 = den %lf 	num %lf\n", (poly->vBC.x * AP.y - poly->vBC.y * AB.x), (-AB.x * poly->vBC.y + poly->vBC.x * AB.y));
		alpha = (poly->vBC.x * AP.y - poly->vBC.y * AP.x) / poly->den2;
	}
	else
	{
	//	printf("2 = den %lf 	num %lf\n", (poly->vBC.z * AP.x - poly->vBC.x * AB.z), (-AB.z * poly->vBC.x + poly->vBC.z * AB.x));
		alpha = (poly->vBC.z * AP.x - poly->vBC.x * AP.z) / poly->den3;
	}*/
	if (!checkzero(poly->vBC.y, 0.0001))
	{
	//	printf("beta = %lf  /  %lf\n", (AB.y * alpha - AP.y), poly->vBC.y);
		beta = (poly->vAB.y * alpha - AP.y) / -poly->vBC.y;
	}
	else if (!checkzero(poly->vBC.z, 0.0001))
		beta = (poly->vAB.z * alpha - AP.z) / -poly->vBC.z;
	// else if (!checkzero(poly->vBC.x, 0.000001))
	// 	beta = (AB.z * alpha - AP.z) / -poly->vBC.x;
	else
		beta = (poly->vAB.x * alpha - AP.x) / -poly->vBC.x;
	/*
	alp
	alpha = get3ddist(colli, poly->finaldot3d[1]) * get3ddist(colli, poly->finaldot3d[2]) / poly->areaabc;
	beta = get3ddist(colli, poly->finaldot3d[0]) * get3ddist(colli, poly->finaldot3d[2]) / poly->areaabc;*/
	//printf("----------alpha beta		%f    %f	\n", alpha, beta);

	if (alpha < 0 || beta < 0 || alpha > 1 || beta > 1 || alpha < beta)
		return (-1);
	//return (gettex(beta, alpha, poly));
	/*if (alpha != alpha)
	{
		printf("AB = %lf    %lf	%lf\n", AB.x, AB.y, AB.z);
		printf("BC = %lf    %lf	%lf\n", BC.x, BC.y, BC.z);
		printf("alpha = %f\n", alpha);
	}*/
	//return (0xff0000);
	return (gettex(alpha, beta, poly));

}


int getcolli(t_input *data, t_poly *poly, t_fdot *colli, int r)
{
	float t;
	float det;
	int		ret;
	float dist;
	// long o1;
	// long o2;
	// struct timeval time;ist = %f\n", ray->distcolli);
	// gettimeofday(&time, NULL);
	// o1 = time.tv_usec;



	ret = -1;

	//printf("getcolli\n");
	//printf("%s\n", poly->tex);
	//printf("PLAN ||| %lf	%lf	%lf	%lf\n", poly->a, poly->b, poly->c, poly->d);
	if (!(det = (poly->a * data->rays[r].x + poly->b * data->rays[r].y + poly->c * data->rays[r].z)))
		return(-1);
	//	printf("det = %lf\n", det);
	t = - poly->d / det;
	colli->x = t * data->rays[r].x;
	colli->y = t * data->rays[r].y;
	colli->z = t * data->rays[r].z;

	// gettimeofday(&time, NULL);
	// o2 = time.tv_usec;
	//printf("calc colli\n");
	//if (poly->debug == 2)
//	{
//		printf("==================%lf	%lf	%lf	 %f====================\n", ray.x, ray.y, ray.z, poly->d);
//		printf("==================%lf	%lf	%lf====================\n", colli->x, colli->y, colli->z);
//	}
	//printf("getcolli\n");
	if (data->rays[r].distcolli == -1)
	{
		//printf("ray -1\n");
		if ((ret = checkbary(poly, colli)) != -1)
			data->rays[r].distcolli = getpow3ddist(*colli);
	}
	else if ((dist = getpow3ddist(*colli)) < data->rays[r].distcolli)
	{
		//printf("else\n");
		//printf("Colli x %f y %f z %f\ndistcolli: %f		dsit: %f\n", colli->x, colli->y, colli->z, data->rays[r].distcolli, dist );
		//printf("poly b x %f y %f z %f\n\n", poly->dot[1].x, poly->dot[1].y, poly->dot[1].z);
		if ((ret = checkbary(poly, colli)) != -1)
			data->rays[r].distcolli = dist;
	}
	else if ((data->rays[r].distcolli != -1) && (dist = getpow3ddist(*colli)) >= data->rays[r].distcolli)
	{
		//printf("Colli x %f y %f z %f\ndistcolli: %f		dsit: %f\n", colli->x, colli->y, colli->z, data->rays[r].distcolli, dist );
		//printf("poly b x %f y %f z %f\n\n", poly->dot[1].x, poly->dot[1].y, poly->dot[1].z);
	}
	//printf("Dist = %f\n", data->rays[r].distcolli);
	// gettimeofday(&time, NULL);
	// o1 = time.tv_usec;process_ra

	
	

	// gettimeofday(&time, NULL);ist = %f\n", ray->distcolli);
	// o2 = time.tv_usec;
	// printf("checkbary %ld   %ld		%ld\n", o1 , o2, o2 - o1);
/*
	if (ret == 1)
	{
		if ((ret = checkbary(poly, colli)) == -1)
			ret = -1;
		elseay *ray,
			ray->distcolli = dist;
	}
	else if (ret == 2)
	{
		if ((ret = checkbary(poly, colli)) == -1)
		{
			ray->distcolli = -1;
			ret = -1;
		}
		else
			ray->distcolli = get3ddist((t_fdot){.x = 0, .y = 0, .z = 0}, *colli);
	}
	*/
	//printf("ret = %d\n", ret);
	return (ret);
}

int  process_ray(t_proray ray, t_input *data, t_poly *poly)
{
	t_fdot	colli;
	// int ret;
	// long o1;
	// long o2;
	// struct timeval time;
	// gettimeofday(&time, NULL);distcolli = -1;
	// o1 = time.tv_usec;
	// //printf("process_ray\n");
	
	// ret = getcolli(&(data->rays[ray.y * data->win_w + ray.x]), poly, &colli, 0);

    // gettimeofday(&time, NULL);
	// o2 = time.tv_usec;
	// printf("~~~~~~process ray %ld   %ld		%ld\n", o1 , o2, o2 - o1);
	// return (ret);
	/*if (ray.y * data->win_w + ray.x == 500)
			poly->debug = 2;
	else
			poly->debug = 0;
	/*if (getcolli(data->rays[y * data->win_w + x], poly, &colli, &texcol))
	{
		return(1);
	}*/

	//printf("procerrrrrrerrrrrrrrrrrrrrrrrrn													%d\n", ray.frst);
	return(getcolli(data, poly, &colli, ray.y * data->win_w + ray.x));

}

void *ray_boxes(void *para)
{
	t_dot p;
	int ret;
	t_thread *thread;
	thread = (t_thread *)para;

	//struct timeval time;
	//long o1;
	//long o2;

	//poly->box.amin = (t_dot){.x = 0, .y = 0};
	//poly->box.amax = (t_dot){.x = data->win_w - 1, .y = data->win_h - 1};

	p = thread->box.amin;
//	printf("rayboxes %d %d   %d %d\n", p.x, p.y, thread->box.amax.x, thread->box.amax.y);
	//print_line(thread->inputs, thread->poly->box.amin, (t_dot){.x = thread->poly->box.amax.x, .y = thread->poly->box.amin.y}, 0xFF0000);
	//print_line(thread->inputs, thread->poly->box.amin, (t_dot){.x = thread->poly->box.amin.x, .y = thread->poly->box.amax.y}, 0xFF0000);
	//print_line(thread->inputs, thread->poly->box.amax, (t_dot){.x = thread->poly->box.amax.x, .y = thread->poly->box.amin.y}, 0xFF0000);
	//print_line(thread->inputs, thread->poly->box.amax, (t_dot){.x = thread->poly->box.amin.x, .y = thread->poly->box.amax.y}, 0xFF0000);
	///print_line(thread->inputs, thread->poly->box.amax, thread->poly->box.amin, 0xFF0000);
	//print_line(thread->inputs, (t_dot){.x = thread->poly->box.amax.x, .y = thread->poly->box.amin.y}, (t_dot){.x = thread->poly->box.amin.x, .y = thread->poly->box.amax.y}, 0xFF0000);

	//printf("rayboxes\n");
	if (!(thread->box.amin.x == thread->box.amax.x || thread->box.amin.y == thread->box.amax.y))
	{

	//gettimeofday(&time, NULL);
	//o1 = time.tv_usec;
		while(p.y <= thread->box.amax.y)
		{
			//printf();
			/*if (thread->inputs->debug)
			{
				printf("ray boxes : %d %d\n", p.x, p.y);
				printf("min-%d	%d\nmax-%d	%d\n", poly->box.amin.x, poly->box.amin.y, poly->box.amax.x, poly->box.amax.y);
			}*/
			/*if(p.x == thread->box.amin.x && p.y == thread->box.amin.y)
				ret = process_ray((t_proray){.x = p.x, .y = p.y, 0}, thread->inputs, thread->poly);
			else*/
			//printf("process ray\n");
			ret = process_ray((t_proray){.x = p.x, .y = p.y, 0}, thread->inputs, thread->poly);
			//printf("color = %d\n", ret);
			if (ret != -1)
			{
			//	printf("drawing\n");
				thread->inputs->im.tab[p.x + p.y * thread->inputs->win_w] = ret; 
			}
			p.x++;
			if (p.x == thread->box.amax.x)
			{
				p.y++;
				p.x = thread->box.amin.x;
			}
		}
	//gettimeofday(&time, NULL);
	//o2 = time.tv_usec;
	//printf("-------process all rays %ld   %ld		%ld\n", o1 , o2, o2 - o1);
	}
	return(NULL);	
}
