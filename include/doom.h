/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:38:23 by mwaterso          #+#    #+#             */
/*   Updated: 2020/06/21 12:35:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef DOOM_H
# define DOOM_H

# include "../libft/include/libft.h"
# include "../minilibx_macos/mlx.h"
# include "../minilibx_macos/mlx_int.h"
# include <stdio.h>
# include <math.h>
# include "keyboard.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>
# define NB_THREAD		8
# define NB_TEXTURE		4
# define NB_HUD_TEX 15
# define NB_ANIM_TEX 4
# define WIN_SIZE_W 1600
# define WIN_SIZE_H 900
# define HITBOXRAY		2
# define X_VIEW			1.57079632679
# define Z_VIEW			1.57079632679
//# define X_VIEW			3.1415926535
//# define Z_VIEW			3.1415926535
# define m_3PI_2		4.71238898038
# define m_PI3			1.0471975512
# define ROTX			0.007
# define ROTZ			0.007
# define ROTY			0.007
# define NBR_PPOLY		4
# define NBR_PIX		1000000
# define GROUNDCOLOR	0x000000
# define R_SKYBOX		100
# define MOB_MOVE_SPEED	2


enum {NUM, TEX, CORD, BRACKET, O_BRACKET, TEX_E, TEX_X, BLOCK, D_OBJ};
enum {ENEMI, POTION, ARMOR, MUN, SCEN, CHEST, KEY};


typedef struct		s_2d
{
   float			x;
   float			y;
}					t_2d;


typedef struct		s_index
{
	int				i;
	int				j;
	int           	k;
}					t_index;

typedef struct		s_fdot
{
	float			x;
	float			y;
	float			z;
}					t_fdot;

typedef struct		s_ray
{
	float				x;
	float				y;
	float				z;
	float				bx;
	float				by;
	float				bz;
	float				distcolli;
	float dp1;
	float dp2;
	t_fdot colli1;
	t_fdot colli2;
}					t_ray;

typedef struct		s_dot
{
	int				x;
	int				y;
	int				z;
}					t_dot;


typedef struct		s_line
{
   char				*line;
   int				n_line;
   struct s_line	*next;
}					t_line;

typedef struct		s_3x3matrix
{
	float a1;
	float a2;
	float a3;

	float b1;
	float b2;
	float b3;

	float c1;
	float c2;
	float c3;
}					t_3x3matrix;

typedef struct		s_fov
{
	float				rotx;
	float				roty;
	struct s_fov 		*next;
}					t_fov;

typedef struct	s_2dbox
{
	t_dot amin;
	t_dot amax;
}				t_2dbox;

typedef struct		s_image
{
	void			*ad; 				//img
	int				*tab;				//addr
	int				bits_per_pixel;		//bpp
	int				size_line;   		//s_l
	int				endian;
}					t_image;

typedef struct		s_thread
{
	pthread_t		thread;
	t_2dbox			box;
	int				i_start;
	int				i_end;
	int				index;
	struct s_poly	*poly;
	t_fov			*fov;
	struct s_input	*inputs;
}					t_thread;

typedef struct		s_tex
{
	void			*tab;
	unsigned int	*img;
	int				width;
	int				height;
	int				bpp;
	int				s_l;
	int				endian;
}					t_tex;

typedef struct	s_proray
{
	int x;
	int y;
	int frst;
}				t_proray;


typedef struct		s_color
{
	u_int8_t			r;
	u_int8_t			g;
	u_int8_t			b;
}					t_color;

typedef	struct		s_mtl
{
	t_tex			tex;
	t_color			ka;
	t_color			kd;
}					t_mtl;

typedef	struct		s_lst_mtl
{
	char				*name;
	t_mtl				mtl;
	struct s_lst_mtl	*next;
}					t_lst_mtl;

typedef struct s_poly
{
	t_2dbox			box;
  	t_fdot			dot[NBR_PPOLY];
	t_fdot			dot_vn[NBR_PPOLY];
	t_fdot			rotx[NBR_PPOLY];
	t_fdot			projx[NBR_PPOLY];
   	t_2d			cord[NBR_PPOLY];
	t_fdot			normale;
	int isvisible;
	float			a;
	float			b;
	float			c;
	float			d;
	t_fdot 			vAB;
	t_fdot 			vBC;
	t_fdot			vAC;
	t_fdot 			vBA;
	t_fdot 			vCB;
	t_fdot			vCA;
	float 			scaleAB;
	float			scaleAC;
	float			scaleABAC;
	float			den1;
	float			den2;
	float			den3;
	t_2d			ab;
	t_2d			ac;
	t_2d			a2d;
	float			areaabc;
	int				nbr_p;
	int				nbr_pprojx;
	int 			debug;
	char*			tex;
	t_tex			tex_tab;
	t_mtl			mtl;
	t_image			texture;
	struct s_poly 	*next;

}					t_poly;

typedef struct			s_sphere
{
	float		r;
	float		rp2;
	t_tex		tex;
	t_fdot		veci;  
	t_fdot		vecj;
	t_fdot 		i;
	t_fdot		j;
	t_fdot 		pos;

}						t_sphere;

typedef struct			s_object
{
	t_fdot				pos;
	t_fdot				posrx;
	t_fdot				rot;
	t_poly				*poly;
	char				*file;
	char				*l_file;
	int					exist;
	int					hp;
	u_int8_t			type;
	struct s_object		*next;
}						t_object;

/**********************               HUD               *********************/

typedef	struct		s_life
{
	int				x_min;
	int				x_max;
	int				y_min;
	int				y_max;
	int				health;
	int				shield;
}					t_life;

typedef	struct		s_texture
{
	t_image			img;
	t_dot			pos_text;
	char			*name_text;
	int				height;
	int				width;
}					t_texture;

typedef struct		s_timer
{
	struct timeval	save_time;
	time_t			time;
	long			microsec;
}					t_timer;

typedef	struct		s_inventory
{
	int				slot_one;
	int				slot_two;
	int				slot_three;
	int				slot_four;
}					t_inventory;

typedef struct		s_keycode
{
	int				r;
	int				t;
	int				one;
	int				two;
	int				escape;
	int				l_click;
}					t_keycode;

typedef struct		s_animation
{
	t_texture		anim_texture[NB_ANIM_TEX];
	char			*tab_texture[NB_ANIM_TEX];
	int				index_heal_anim;
	int				index_shield_anim;
	int				index_wpn_anim;
	int				index_rld_anim;
}					t_animation;

typedef struct		s_data
{
	t_keycode		keycode;
	t_inventory		inventory;
	t_animation		healanim;
	t_animation		shieldanim;
	t_animation		weaponanim;
	t_texture		tab_tex[NB_HUD_TEX];
	t_texture		menu_texture[4];
	t_timer			timer;
	t_life			health_bar;
	t_dot			pos_texture[NB_HUD_TEX];
	char			*name_texture[NB_HUD_TEX];
	void			*mlx_addrs;
	void			*win_addrs;
	int				keys[80000];
	int				total_ammo;
	int				current_ammo;
	int				dead_state;
	int				menu_state;
	int				first_frame;
	int				diff;
}					t_data;

/**********************               HUD               *********************/

typedef struct		s_input
{   
	void			*mlx_ad;
	void			*win_ad;
	t_image			im;
	struct timeval timer2;
	t_thread		thread_tab[NB_THREAD];
	t_sphere		sky;
    int				win_h;
    int				win_w;
	float			alpha_x;   /* angle entre vue joueur et vect x sur plan xy (PROJECTION 2D)*/
	float			alpha_z;   /* angle entre vue joueur et vect z */
	float			angley;
	int				nbrpoly;
	int 			debug;
	int				nbrtour;
	t_poly			*map;
	t_object		*obj;
	t_fdot			dir;
	t_fov			*fov;
	t_ray			*rays;
	t_fdot			tmp_pos;
	t_3x3matrix		rotz;
	t_3x3matrix		roty;
	t_3x3matrix		minrotz;
	t_3x3matrix 	minroty;
	t_data			*data_hud;
	int				fps;
	int screensize;
	float cons1;
	float cons2;

}					t_input;

typedef struct 		s_lstex
{
	t_tex			tex;
	char			*name;
	struct s_lstex	*next;
}					t_lstex;

typedef struct		s_file_obj
{
	t_fdot			pos;
	t_lst_mtl		*lst;
	t_fdot      	*v;
    t_2d        	*vt;
    t_fdot      	*vn;
	t_index			size;
	t_index			index;
}					t_file_obj;



/*typedef struct		s_octree
{
	struct s_octree (*childs)[8];
	int color;
	float size;
	t_fdot end_corner;		/Coordonnees du sommet +z +x +y/
	t_fdot start_corner;	/Coordonnees du sommet -z -x -y/
}					t_octree;*/
void damage_mob(t_object *obj);
int 	mouse_moove(int x, int y, void *param);
void	dead_anim(t_data *data);
t_fdot normalise_vec(t_fdot a);
void getobjplans(t_input *data);
void redefineobj(t_input *data);
void separate_points(t_poly *map);
void mapmoveallp(t_input  *data, t_fdot way);
int 	Projxy(t_poly *map, t_input *data);
void get_objpo(t_object *objects, t_input *data);
int  process_ray(t_proray ray, t_input *data, t_poly *poly);
float getpow3ddist(t_fdot a);
int alkashisolver(t_poly *poly, t_fdot col);
t_fdot	vectoriel_product(t_fdot v1, t_fdot v2);
float scale(t_fdot a, t_fdot b);
t_fdot  fix_vec(t_fdot vec);
int		in_poly(t_poly *poly, t_fdot col);
void thread_start(t_input	*data, t_poly* poly);
int 				solv_equ(t_fdot e1, t_fdot e2, t_fdot *sol);
int checkzero(float a, float inter);
void 			rea_ray(t_input *data);
int 			check_colli(t_poly *poly);
void moove(t_input *data, int way);
t_3x3matrix 	define_yRotMat(float a);
t_3x3matrix 	define_zRotMat();
t_3x3matrix 	define_minyRotMat();
t_3x3matrix 	define_minzRotMat();
float 			get3ddist(t_fdot a, t_fdot b);
int getcolli(t_input *data, t_poly *poly, t_fdot *colli, int r);
void			get_plans(t_poly *poly);
void			*ray_boxes(void *para);
void 			mapmovep(t_poly *poly, t_fdot incr);
void 			maprotateallp(t_poly *poly, t_fdot rot, t_input *data);
int				poly_toboxes (t_input *data, t_poly *poly);
int				proj_2d(t_poly *map, t_input *data);
float 			magnitude(t_fdot a);
int				keyboard_move(int key, t_input *inputs);
t_fdot			ApplyMatPoint(t_3x3matrix matrix, t_fdot point);
t_fdot 			getvect(t_fdot a, t_fdot b);
t_2d 			get2dvect(t_2d a, t_2d b);
void redefinevector(t_poly *poly);


int				push_back(t_poly *new, t_poly **poly);
int				creat_elem_l(char *line, int n_line, t_line **list);
int		   		sort_dot(char *line, t_poly *new, t_index *index);
int				parse_loop(t_poly **poly, t_line *list, t_input *data, int fd);
int				parse_file(t_line *list, t_poly **poly, t_input *data);
int				load_tex(t_poly **poly, t_input *data);
t_poly			*parsing_poly(char *file, t_input *data);
char			*sort_file(char *line);
void		   	error_file(int fd, char *av);
void		  	poly_error(t_line *list, int error, int i, int *err);
void			print_s(int i);
void    		get_device(char **device);
void 			print_parse(t_poly *poly);
int				check_error(t_line *list);
void		   	free_poly(t_poly **poly);
void		   	free_line(t_line **line);
t_line			*read_obj(t_line *list, t_object **obj, t_input *data);
void			push_front_obj(t_object *new, t_object **obj);
void             reverse(t_object **obj);
void             poly_rev(t_poly **poly) ;
void 			obj_error(t_line *list, int *error);
t_poly			*ft_pares_obj(char *file, t_input *data);
int      		sort_tfdot(char *line, t_fdot *dot);
int      		sort_t2d(char *line, t_2d *dot);
int         	sort_poly(char *line, t_poly **poly, t_file_obj file, char *mtl);
void			free_tab(char ***tab);
void			clear_im(t_input *data);
/*------------------------------*/
void 			print_parse1(t_poly *poly);
/*-------------------------------*/
void			push_front_pol(t_poly *new, t_poly **poly);
void            reverse_p(t_poly **poly);
void            reverse_o(t_object **obj);
void            reverse_l(t_line **list);
int    			sort_mtl(t_input *data, char *file, t_file_obj *f);
int				creat_elem_l1(char *line, int n_line, t_line **list);
int     		sort_color(char *line, t_color *color);
char    		*sort_material(char *line);
void			push_front_mtl(t_lst_mtl *new, t_lst_mtl **mtl);
void            free_file(t_lst_mtl **lst);
int 			checkbary(t_poly *poly, t_fdot *colli);
/**********************               HUD               *********************/

void				get_texture(t_data *data);
void				string_to_print(t_data *data);
void				dead_anim(t_data *data);
void				shield_animation(t_data *data);
void				reload_animation(t_data *data);
void				heal_animation(t_data *data);
void				weapon_animation(t_data *data);
void				health(t_data *data);
void				shield(t_data *data);
void				print_reload(t_data *data);
void				fill_texture_tab(t_data *data);
void				print_ammo(t_data *data);
void				close_game(t_data *data);
void				check_inputs_bis(t_data *data);
void				check_anim(t_data *data);
void				check_fire(t_data *data, t_input *input);
int					check_inputs(t_data *data);
int					ammo(t_data *data);
int					print_hud(t_data *data);
int					load_texture_data(t_data *data);
int					key_press(int keycode, void *data);
int					key_release(int keycode, void *data);
int					mouse_press(int button, int x, int y, void *data);
int					mouse_release(int button, int x, int y, void *param);
int					redraw(void *data);
int					cooldown(t_data *data, time_t cd);
int					print_menu(t_data *data);
int					heal_texture_animation(t_data *data);
int					load_menu_texture(t_data *data);
int					shield_texture_animation(t_data *data);

/**********************               HUD               *********************/


/**********************               YOLO               *********************/
void		inter_cord(t_line *list, int *tmp, int *error, int *i);
int			loop_read(t_line *tmp, int *count, t_poly **poly, t_input *data);
t_line		*poly_read(t_line *list, t_poly **poly);
void	free_file_obj(t_file_obj file);
int	parse_fobj2(t_line *list, t_file_obj *file, t_input *d, t_poly **poly);
void	free_object(t_object **obj, t_object *new);
void	free_new_lst(t_lst_mtl *new);
void	loop_read2(t_line *list, t_object *new, t_input *data);
void		ft_sort_rot(char *line, t_object *new);
void		ft_sort_pos(char *line, t_object *new, t_input *data);
void		sort_type(char *line, t_object *new);
int		size_mtl_file(char *file);
void    parse_mtl_loop(t_line *list, t_lst_mtl *new);
/**********************               YOLO               *********************/


#endif
