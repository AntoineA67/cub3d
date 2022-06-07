#	VARIABLES
NAME		= cub3D
OBJDIR		= obj/
INCDIR		= inc/
VPATH		= src/$(addprefix :src/, ui textures multi enemies parsing mouse_key_hooks render utils init)
INC			= $(addprefix ${INCDIR}, cub3D.h)
SRC			= main.c utils.c parse.c enemies.c init_player.c button.c slider.c ui.c l_pts.c key_hooks.c texture_manage.c mouse_hooks.c plot.c render.c color_utils.c client.c minimap.c font.c rays.c profiling.c
SERVER		= server
OBJ			= $(addprefix ${OBJDIR}, $(SRC:.c=.o))
LIBRARY		= -L libft -lft -L mlx_opengl -lmlx -lm
LIB_FILE	= libft/libft.a mlx_opengl/libmlx.a
CC			= gcc
FLAGS		= -Wall -Wextra -Werror -I./inc/
# FLAGS		+=  -DDEBUG_PROFILE -finstrument-functions
# FLAGS		+= -O3
# FLAGS		+= -fsanitize=address -g
# FLAGS		+= -Ofast

#	RULES
all: ${OBJDIR} ${NAME}
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
	rm -rf ${OBJDIR}
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
