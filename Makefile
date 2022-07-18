#	VARIABLES
NAME		= cub3D
NAME_BONUS	= cub3D_bonus
OBJDIR		= obj/
OBJDIR_BONUS= obj_bonus/
INCDIR		= mandatory/inc/
INCDIR_BONUS= bonus/inc/
VPATH		= mandatory/src/$(addprefix :mandatory/src/, ui textures multi enemies parsing mouse_key_hooks render utils init  )
VPATH		+= bonus/src/$(addprefix :bonus/src/, ui textures multi enemies parsing mouse_key_hooks render utils init  )
INC			= $(addprefix ${INCDIR}, cub3D.h)
INC_BONUS	= $(addprefix ${INCDIR_BONUS}, cub3D.h)

SRC			= utils.c \
			main.c \
			parse.c \
			parse_utils.c \
			init_player.c \
			glb_init.c \
			l_pts.c \
			key_actions.c \
			key_hooks.c \
			texture_manage_get.c \
			texture_manage_load.c \
			texture_manage_free.c \
			mouse_hooks.c \
			plot.c \
			line_texture.c \
			render.c \
			color_utils.c \
			project_rays.c \
			draw_utils.c \
			calc_rays.c
SRC_BONUS = $(subst .c,_bonus.c,${SRC} minimap.c)

OBJ			= $(addprefix ${OBJDIR}, $(SRC:.c=.o))
OBJ_BONUS	= $(addprefix ${OBJDIR_BONUS}, $(SRC_BONUS:.c=.o))
LIBRARY		= -L libft -lft -L mlx_opengl -lmlx -lm
LIB_FILE	= libft/libft.a mlx_opengl/libmlx.a
CC			= gcc
FLAGS		= -Wall -Wextra -Werror
# FLAGS		=  -DDEBUG_PROFILE -finstrument-functions -I./inc/
FLAGS		+= -O2
#  FLAGS		+= -fsanitize=address -g
# FLAGS		+= -Ofast

#	RULES
all: ${OBJDIR} ${NAME}

${OBJDIR}:
	@mkdir -p ${OBJDIR}

${NAME}: ${OBJ} ${LIB_FILE}
	${CC} ${FLAGS} ${LIBRARY} $^ -framework OpenGL -framework AppKit -o ${NAME}

${OBJDIR}%.o: %.c ${INC} Makefile
	${CC} ${FLAGS} -I./${INCDIR} -c $< -o $@

libft/libft.a:
	make -C libft

bonus: ${OBJDIR_BONUS} ${NAME_BONUS}

${OBJDIR_BONUS}:
	@mkdir -p ${OBJDIR_BONUS}

${NAME_BONUS}: ${OBJ_BONUS} ${LIB_FILE}
	${CC} ${FLAGS} ${LIBRARY} $^ -framework OpenGL -framework AppKit -o ${NAME_BONUS}

${OBJDIR_BONUS}%.o: %.c ${INC_BONUS} Makefile
	${CC} ${FLAGS} -I./${INCDIR_BONUS} -c $< -o $@

clean:
	make clean -C libft
	rm -rf ${OBJDIR}
	rm -rf ${OBJDIR_BONUS}

fclean:
	make fclean -C libft
	rm -rf maps.txt
	rm -rf textures.txt
	rm -rf ${OBJDIR}
	rm -rf ${OBJDIR_BONUS}
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
