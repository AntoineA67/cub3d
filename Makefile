#	VARIABLES
NAME		= cub3D
OBJDIR		= obj/
INCDIR		= mandatory/inc/
VPATH		= mandatory/src/$(addprefix :mandatory/src/, ui textures multi enemies parsing mouse_key_hooks render utils init  )
INC			= $(addprefix ${INCDIR}, cub3D.h)

SRCM		= utils.c \
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
	
SRC			= main.c \
			utils.c \
			parse.c \
			parse_utils.c \
			enemies.c \
			init_player.c \
			glb_init.c \
			combat_init.c \
			button.c \
			slider.c \
			ui1.c \
			ui2.c \
			ui_utils.c \
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
			minimap.c \
			font.c \
			project_rays.c \
			combat.c \
			draw_utils.c \
			end_game.c \
			calc_rays.c

SERVER		= server
OBJ			= $(addprefix ${OBJDIR}, $(SRCM:.c=.o))
LIBRARY		= -L libft -lft -L mlx_opengl -lmlx -lm
LIB_FILE	= libft/libft.a mlx_opengl/libmlx.a
CC			= gcc
FLAGS		= -Wall -Wextra -Werror -I./mandatory/inc/
# FLAGS		=  -DDEBUG_PROFILE -finstrument-functions -I./inc/
FLAGS		+= -O2
#  FLAGS		+= -fsanitize=address -g
# FLAGS		+= -Ofast

#	RULES
all: ${OBJDIR} ${NAME}

bonus: ${OBJDIR} ${NAME}
	ls maps > maps.txt
	find -f textures | grep "\.xpm" > textures.txt

${OBJDIR}:
	@mkdir -p ${OBJDIR}

${NAME}: ${OBJ} ${LIB_FILE}
	${CC} ${FLAGS} ${LIBRARY} $^ -framework OpenGL -framework AppKit -o ${NAME}

${OBJDIR}%.o: %.c ${INC} Makefile
	${CC} ${FLAGS} -c $< -o $@

libft/libft.a:
	make -C libft

${SERVER}: Makefile
	${CC} ${FLAGS} src/server.c -o $@

clean:
	make clean -C libft
	rm -rf ${OBJDIR}

fclean:
	make fclean -C libft
	rm -rf maps.txt
	rm -rf textures.txt
	rm -rf ${OBJDIR}
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
