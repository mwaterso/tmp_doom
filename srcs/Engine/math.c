/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   math.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/21 14:43:50 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2020/03/06 17:31:47 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

void redefineobj(t_input *data)
{
    t_object *obj;

    obj = data->obj;
    while(obj)
    {
        redefinevector(obj->poly);
        obj = obj->next;
    }
}

void redefinevector(t_poly *poly)
{
    while (poly)
    {
        poly->vAB = getvect(poly->dot[0], poly->dot[1]);
		poly->vBC = getvect(poly->dot[1], poly->dot[2]);
        poly->vAC = getvect(poly->dot[0], poly->dot[2]);
        poly->scaleAB = scale(poly->vAB, poly->vAB);
        poly->scaleAC = scale(poly->vAC, poly->vAC);
        poly->scaleABAC = scale(poly->vAB, poly->vAC);
       // printf("ab   %f %f %f \n ac %f %f %f \n", poly->vAB.x,  poly->vAB.y,  poly->vAB.z, poly->vAC.x, poly->vAC.y, poly->vAC.z);
       // printf("a   %f %f %f b %f %f %f \n", poly->dot[0].x,  poly->dot[0].y,  poly->dot[0].z, poly->dot[1].x, poly->dot[1].y, poly->dot[1].z);
       // printf("a   %f %f %f c %f %f %f \n", poly->dot[0].x,  poly->dot[0].y,  poly->dot[0].z, poly->dot[2].x, poly->dot[2].y, poly->dot[2].z);
        poly->vBA = getvect(poly->dot[1], poly->dot[0]);
		poly->vCB = getvect(poly->dot[2], poly->dot[1]);
        poly->vCA = getvect(poly->dot[2], poly->dot[0]);
        poly->den1 = (-poly->vAB.y * poly->vBC.z + poly->vBC.y * poly->vAB.z);
        poly->den2 = (-poly->vAB.x * poly->vBC.y + poly->vBC.x * poly->vAB.y);
        poly->den3 = (-poly->vAB.z * poly->vBC.x + poly->vBC.z * poly->vAB.x);
        poly = poly->next;
    }
}

t_fdot getvect(t_fdot a, t_fdot b)
{
    return((t_fdot){.x = b.x - a.x, .y = b.y - a.y, .z = b.z - a.z});
}

float magnitude(t_fdot a)
{
    return(sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_2d get2dvect(t_2d a, t_2d b)
{
    return((t_2d){.x = b.x - a.x, .y = b.y - a.y});
}

float get3ddist(t_fdot a, t_fdot b)
{
	float dx;
	float dy;
	float dz;

	dx = b.x - a.x;
	dy = b.y - a.y;
	dz = b.z - a.z;
    return(sqrtf(dx * dx + dy * dy + dz * dz));
}


float getpow3ddist(t_fdot a)
{
	return(a.x * a.x + a.y * a.y + a.z * a.z);
}

t_fdot vectorial_product(t_fdot a, t_fdot b)
{
    //printf("vectorial product\n");
    t_fdot u;

    u.x = a.y * b.z - a.z * b.y;
    u.y = a.z * b.x - a.x * b.z;
    u.z = a.x * b.y - a.y * b.x;
    return (u);
}

void getobjplans(t_input *data)
{
    t_object *obj;

    obj = data->obj;
    while(obj)
    {
        get_plans(obj->poly);
        obj = obj->next;
    }

}
void get_plans(t_poly *poly)
{
    t_fdot vectu;
    //printf("poly = %p\nnbr points = %d\n point1 x = %f y = %f z = %f", poly, poly->nbrpoly, poly->finaldot3d[0].x, poly->finaldot3d[0].y, poly->finaldot3d[0].z);
    while (poly)
    {
        vectu = vectorial_product(getvect(poly->dot[0], poly->dot[1]), getvect(poly->dot[0], poly->dot[2]));

        poly->a = vectu.x;
        poly->b = vectu.y;
        poly->c = vectu.z;

        poly->d = -(poly->a * poly->dot[0].x + poly->b * poly->dot[0].y + poly->c * poly->dot[0].z);

	    // printf("PLAN ||| %lf	%lf	%lf	%lf\n", poly->a, poly->b, poly->c, poly->d);
	    // printf("PLAN ||| %lf	%lf	%lf\n", poly->finaldot3d[0].x, poly->finaldot3d[0].y, poly->finaldot3d[0].z);
	    // printf("PLAN ||| %lf	%lf	%lf\n", poly->finaldot3d[1].x, poly->finaldot3d[1].y, poly->finaldot3d[1].z);
	    // printf("PLAN ||| %lf	%lf	%lf\n", poly->finaldot3d[2].x, poly->finaldot3d[2].y, poly->finaldot3d[2].z);
        //poly->areaabc = get3ddist(poly->finaldot3d[0], poly->finaldot3d[1]) * get3ddist(poly->finaldot3d[0], poly->finaldot3d[2]) ;// / 2;
		poly = poly->next;
    }
}

int solv_equ(t_fdot e1, t_fdot e2, t_fdot *sol)
{
    float tmp;
    //printf("solve equ   %f %f %f \n %f %f %f\n", e1.x, e1.y, e1.z, e2.x, e2.y, e2.z);

    if (!(tmp = e2.x * e1.y - e1.x * e2.y))
    {
    //    printf("solve equ error\n");
        return(0);
    }
   // printf("tmp + %f\n", tmp);
    tmp = 1. / tmp;
    sol->x = (e2.y * e1.z - e1.y * e2.z) * tmp;
    sol->y = (e1.x * e2.z - e2.x * e1.z) * tmp;
   // printf("%f  %f !!!! %f  %f\n", sol->x, sol->y, (e2.y * e1.z - e1.y * e2.z) * tmp, (e1.x * e2.z - e2.x * e1.z) * tmp);
    return(1);
}

float scale(t_fdot a, t_fdot b)
{
    return(a.x * b.x + a.y * b.y + a.z * b.z);
    return(fmaf(a.x, b.x, fmaf(a.y, b.y, fmaf(a.z, b.z, 0))));
}

t_fdot  fix_vec(t_fdot vec)
{
    t_fdot des;
    des.x = vec.x;
    des.y = vec.y;
    des.z = vec.z;
    if(des.x <= 0.005)
        des.x = 0.f;
    if(des.y <= 0.005)
        des.y = 0.f;
    if(des.z <= 0.005)
        des.z = 0.f;
    return(des);
}

t_fdot	vectoriel_product(t_fdot v1, t_fdot v2)
{
	return ((t_fdot){v1.y * v2.z - v1.z * v2.y,\
						v1.z * v2.x - v1.x * v2.z,\
						v1.x * v2.y - v1.y * v2.x});
}