/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   multthread.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/03/09 17:58:08 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2020/03/09 19:37:16 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"



/*void thread_start(t_input	*data)
{
	int i;
    t_poly *poly;
    int dx;
    int dy;
   // long o1;
	//long o2;
	//struct timeval time;
	//gettimeofday(&time, NULL);
	//o1 = time.tv_usec;
    poly = data->map;
    
    while (poly)
    {
        if(poly->isvisible)
        {
           //printf("Box \nmin = %d  %d\nmax = %d %d\n", poly->box.amin.x,  poly->box.amin.y,  poly->box.amax.x,  poly->box.amax.y);
	       rb(data, poly, poly->box);

		
           // gettimeofday(&time, NULL);
	       // o2 = time.tv_usec;
	       // printf("ray box %ld   %ld		%ld\n", o1 , o2, o2 - o1);
            //    printf("tread22222 = %d\n", i);
        }
        poly = poly->next;
    }
   // gettimeofday(&time, NULL);
	//o2 = time.tv_usec;
	//printf("END THREAD %ld   %ld		%ld\n", o1 , o2, o2 - o1);
    //printf("end of thread\n");
	i = -1;
	/*while (++i < data->screensize)
	{
		if (!checkzero(data->rays[i].dp1, 0.001) && !checkzero(data->rays[i].dp2, 0.001))
			if (data->rays[i].dp1 < data->rays[i].dp2)
			{
				printf("dp1: %f		dp2: %f		i = %d\n", data->rays[i].dp1, data->rays[i].dp2, i);
				printf("p1: %f	%f  %f	p2: %f	%f  %f\n", data->rays[i].colli1.x, data->rays[i].colli1.y, data->rays[i].colli1.z, data->rays[i].colli2.x, data->rays[i].colli2.y, data->rays[i].colli2.z);
			}
		//if (i > 400000 && i < 1000000)
		//printf("poly b x %f y %f z %f\n\n", poly->dot[1].x, poly->dot[1].y, poly->dot[1].z);
	}*
}*/

void thread_start(t_input	*data, t_poly *poly)
{
	int i;
	int j;
	j = 0;
   // t_poly *poly;
    int dx;
    int dy;
   // long o1;
	//long o2;
	//struct timeval time;
	//gettimeofday(&time, NULL);
	//o1 = time.tv_usec;
   // poly = data->map;
    
    while (poly)
    {
        if(poly->isvisible)
        {
           //printf("Box \nmin = %d  %d\nmax = %d %d\n", poly->box.amin.x,  poly->box.amin.y,  poly->box.amax.x,  poly->box.amax.y);
	        i = 0;
            dx = poly->box.amax.x - poly->box.amin.x;
            dy = poly->box.amax.y - poly->box.amin.y;
            while(i < NB_THREAD)
            {
                data->thread_tab[i].poly = poly;
		        data->thread_tab[i].box.amin.x = poly->box.amin.x;
		        data->thread_tab[i].box.amax.x = poly->box.amax.x;
		        data->thread_tab[i].box.amin.y = (float)(i / (float)NB_THREAD) * dy + poly->box.amin.y;
		        data->thread_tab[i].box.amax.y = (float)((i + 1) / (float)NB_THREAD) * dy + poly->box.amin.y;
		        data->thread_tab[i].inputs = data;

	           // gettimeofday(&time, NULL);
	           // o1 = time.tv_usec;
               /// printf("poly = %d tread = %d\nBox \nmin = %d  %d\nmax = %d %d\n\n", j, i, data->thread_tab[i].box.amin.x , data->thread_tab[i].box.amin.y, data->thread_tab[i].box.amax.x, data->thread_tab[i].box.amax.y);
		        pthread_create(&data->thread_tab[i].thread, NULL,
		        &ray_boxes, &data->thread_tab[i]);
		        i++;
            }
           // printf("go le join\n");
	        i = 0;
	        while (i < NB_THREAD)
            {
            //    printf("jtread = %d\n", i);
		        pthread_join(data->thread_tab[i].thread, NULL);
           // gettimeofday(&time, NULL);
	       // o2 = time.tv_usec;
	       // printf("ray box %ld   %ld		%ld\n", o1 , o2, o2 - o1);
            //    printf("tread22222 = %d\n", i);
				i++;
            }
        }
        poly = poly->next;
		j++;
    }
   // gettimeofday(&time, NULL);
	//o2 = time.tv_usec;
	//printf("END THREAD %ld   %ld		%ld\n", o1 , o2, o2 - o1);
    //printf("end of thread\n");
	i = -1;
	/*while (++i < data->screensize)
	{
		if (!checkzero(data->rays[i].dp1, 0.001) && !checkzero(data->rays[i].dp2, 0.001))
			if (data->rays[i].dp1 < data->rays[i].dp2)
			{
				printf("dp1: %f		dp2: %f		i = %d\n", data->rays[i].dp1, data->rays[i].dp2, i);
				printf("p1: %f	%f  %f	p2: %f	%f  %f\n", data->rays[i].colli1.x, data->rays[i].colli1.y, data->rays[i].colli1.z, data->rays[i].colli2.x, data->rays[i].colli2.y, data->rays[i].colli2.z);
			}
		//if (i > 400000 && i < 1000000)
		//printf("poly b x %f y %f z %f\n\n", poly->dot[1].x, poly->dot[1].y, poly->dot[1].z);
	}*/
}

    /*
	while(i < NB_THREAD)
	{
		data->thread_tab[i].i_start = i * (data->win_h * data->win_w / NB_THREAD);
		data->thread_tab[i].i_end = (i + 1) * (data->win_h * data->win_w / NB_THREAD);
		data->thread_tab[i].inputs = data;
        data->thread_tab[i].index = i;
		pthread_create(&data->thread_tab[i].thread, NULL,
		&processbox, &data->thread_tab[i]);
		i++;
	}
    printf("end\n");
	i = 0;
	while (i <= NB_THREAD)
		pthread_join(data->thread_tab[i++].thread, NULL);*/