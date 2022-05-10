#	VARIABLES
NAME		= cub3D
OBJDIR		= obj/
INCDIR		= inc/
VPATH		= src/
INC			= $(addprefix ${INCDIR}, cub3D.h)
SRC			= main.c utils.c parse.c l_pts.c key_hooks.c mouse_hooks.c plot.c render.c color_utils.c client.c font.c
SERVER		= server
OBJ			= $(addprefix ${OBJDIR}, $(SRC:.c=.o))
LIBRARY		= -L libft -lft -L mlx_opengl -lmlx -lm
LIB_FILE	= libft/libft.a mlx_opengl/libmlx.a
CC			= gcc
# FLAGS		= -I/usr/include
FLAGS		= -Wall -Wextra -Werror
# FLAGS		+= -O2
# FLAGS		+= -fsanitize=address -g
FLAGS		+= -Ofast

#	RULES
all: ${OBJDIR} ${NAME}

${OBJDIR}:
	@mkdir -p ${OBJDIR}

${NAME}: ${OBJ} ${LIB_FILE}
#	${CC} ${FLAGS} ${LIBRARY} $^ -Lmlx_linux -lmlx -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o ${NAME}
	${CC} ${FLAGS} ${LIBRARY} $^ -framework OpenGL -framework AppKit -o ${NAME}

${OBJDIR}%.o: %.c ${INC} Makefile
	${CC} ${FLAGS} -I/usr/include -Imlx_linux -c $< -o $@

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
