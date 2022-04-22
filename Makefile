#	VARIABLES
NAME		= cub3D
OBJDIR		= obj/
INCDIR		= inc/
VPATH		= src/
INC			= $(addprefix ${INCDIR}, fdf.h)
SRC			= main.c utils.c color_utils.c project.c key_hooks.c mouse_hooks.c parse.c plot.c l_pts.c
OBJ			= $(addprefix ${OBJDIR}, $(SRC:.c=.o))
LIBRARY		= -L libft -lft -L mlx2020 -lmlx
HEADERS		= fdf.h libft/libft.h mlx2020/mlx.h
CC			= gcc
LIB_FILE	= libft/libft.a libmlx.dylib
FLAGS		= -Wall -Wextra -Werror
#FLAGS		+= -fsanitize=address -g
#FLAGS		+= -Ofast

#	RULES
all: ${OBJDIR} ${NAME} libs 

${OBJDIR}:
	@mkdir -p ${OBJDIR}

${NAME}: ${OBJ} ${LIB_FILE}
	${CC} ${FLAGS} ${LIBRARY} $^ -framework OpenGL -framework AppKit -o ${NAME}

${OBJDIR}%.o: %.c ${INC} Makefile
	${CC} ${FLAGS} -Imlx2020 -c $< -o $@

libmlx.dylib:
	@make -C mlx2020
	@mv mlx2020/libmlx.dylib ./

libs:
	make -C libft

clean:
	make clean -C libft
	rm -rf ${OBJDIR}

fclean:
	rm -rf ${OBJDIR}
	make fclean -C libft
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re lib
