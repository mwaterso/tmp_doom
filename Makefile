
FLAGS =  -framework OpenGL -framework AppKit -framework OpenAL


SRC_PATH = srcs/


SRC_NAME =  srcs/main.c

SRC_NAME += srcs/Event/hooks.c

SRC_NAME += srcs/Engine/math.c\
            srcs/Engine/Projection.c\
            srcs/Engine/trace.c\
            srcs/Engine/map.c\
            srcs/Engine/matrix.c\
			srcs/Engine/multthread.c\
			srcs/Engine/objects.c\


SRC_NAME += srcs/Parsing/parsing_poly.c srcs/Parsing/parsing_error.c \
            srcs/Parsing/parsing_list.c srcs/Parsing/parsing_error2.c \
            srcs/Parsing/parsing_other.c srcs/Parsing/parsing_tex.c
    
SRC_NAME += srcs/Parsing_obj/parse_obj.c     \
            srcs/Parsing_obj/object_list.c   \
            srcs/Parsing_obj/obj_error.c     \
            srcs/Parsing_obj/parsing_obj.c   \
            srcs/Parsing_obj/sort_dot.c      \
            srcs/Parsing_obj/sort_poly.c     \
            srcs/Parsing_obj/parsing_mtl.c   \
            srcs/Parsing_obj/obj_mlt.c\
			srcs/Parsing_obj/parsing_norm.c\

SRC_NAME += srcs/hud/check_event.c       \
            srcs/hud/display_hud.c       \
            srcs/hud/display_weapon.c    \
            srcs/hud/event.c             \
            srcs/hud/health_bar.c        \
            srcs/hud/hud.c               \
            srcs/hud/init_function.c     \
            srcs/hud/timer.c             \

SRC_NAME +=	libft/src/ft_atoi.c			libft/src/ft_strcmp.c			libft/src/ft_strcpy.c 		\
			libft/src/ft_strlen.c			libft/src/ft_strncmp.c		libft/src/ft_strncpy.c 		\
			libft/src/ft_memcpy.c			libft/src/ft_memset.c			libft/src/ft_bzero.c			\
 	  		libft/src/ft_memccpy.c		libft/src/ft_memmove.c		libft/src/ft_memchr.c			\
 	  		libft/src/ft_memcmp.c			libft/src/ft_strdup.c			libft/src/ft_strcat.c			\
 	 		libft/src/ft_strncat.c 		libft/src/ft_strlcat.c		libft/src/ft_strchr.c			\
 	  		libft/src/ft_isalpha.c		libft/src/ft_isdigit.c		libft/src/ft_isalnum.c		\
 	  		libft/src/ft_strrchr.c		libft/src/ft_strstr.c			libft/src/ft_isascii.c 		\
 	  		libft/src/ft_isprint.c		libft/src/ft_toupper.c	libft/src/ft_tolower.c		\
 	  		libft/src/ft_putchar.c		libft/src/ft_putstr.c 		libft/src/ft_strnstr.c		\
 	  		libft/src/ft_strclr.c			libft/src/ft_putnbr.c			libft/src/ft_putendl.c		\
 	  		libft/src/ft_striter.c		libft/src/ft_striteri.c		libft/src/ft_memdel.c			\
 	  		libft/src/ft_strnew.c 		libft/src/ft_memalloc.c		libft/src/ft_putchar_fd.c		\
 	  		libft/src/ft_putendl_fd.c		libft/src/ft_putnbr_fd.c 		libft/src/ft_putstr_fd.c		\
 	  		libft/src/ft_strdel.c			libft/src/ft_strmap.c			libft/src/ft_strmapi.c 		\
 	 	 	libft/src/ft_strequ.c			libft/src/ft_strnequ.c		libft/src/ft_strsub.c			\
 	 	 	libft/src/ft_strjoin.c		libft/src/ft_strtrim.c		libft/src/ft_strsplit.c		\
 	 	 	libft/src/ft_itoa.c			libft/src/ft_lstnew.c			libft/src/ft_intsize.c		\
 	  		libft/src/ft_lstdelone.c		libft/src/ft_lstdel.c			libft/src/ft_lstadd.c 		\
 	 	 	libft/src/ft_lstiter.c		libft/src/ft_lstmap.c			libft/src/ft_strrev.c			\
 	  		libft/src/ft_foreach.c		libft/src/ft_factorial.c		libft/src/ft_power.c			\
 	  		libft/src/ft_is_prime.c		libft/src/ft_swap.c			libft/src/ft_range.c 			\
 		  	libft/src/get_next_line.c		libft/src/ft_sqrt.c			\
			libft/src/ft_strcchr.c		libft/src/ft_putspace.c		libft/src/ft_avlen.c			\
			libft/src/ft_color_txt.c		libft/src/ft_putendl_color.c	libft/src/rspace.c 			\
			libft/src/ft_putstr_color.c 	libft/src/ft_avswap.c 		libft/src/ft_up_rounded.c		\
			libft/src/ft_2dstrdel.c		libft/src/ft_tablen.c			libft/src/first_word.c		\
			libft/src/ft_ispace.c			libft/src/ft_strnchr.c		libft/src/ft_putstr_hexa.c	\
			libft/src/ft_putendl_hexa.c	libft/src/ft_putnbr_hexa.c	libft/src/ft_atof.c			\
			libft/src/ft_strjoin2.c

LIBFT = libft/libft.a

LIBMLX = minilibx_macos/libmlx.a

LIBMLX2= minilibx_macos/libmlx_Linux.a


INC = include/doom.h

NAME = Doom-nukem

FLAGS_MATH = -O3 -flto -march=native -ffast-math

FLAGS = -Llibft -Llibmlx -lX11 -lbsd -lm -lpthread -lXext $(FLAGS_MATH)



OBJ = $(SRC_NAME:%.c=%.o)

all : $(NAME)

$(NAME): $(LIBMLX) $(OBJ)
	clang $(OBJ) -o $(NAME)  $(LIBMLX) $(LIBMLX2) $(FLAGS) 

%.o: %.c $(INC)
	clang -c -I include/ $< -o $@ $(FLAGS_MATH)


$(LIBMLX):
	make -C minilibx_macos/ 

clean: 
	make clean -C libft/
	make clean -C minilibx_macos/
	rm -rf $(OBJ)

fclean: clean
	make fclean -C libft/
	rm -rf $(NAME)