#	VARIABLES
NAME		= cub3D
OBJDIR		= obj/
INCDIR		= inc/
VPATH		= src/
INC			= $(addprefix ${INCDIR}, cub3D.h)
SRC			= main.c utils.c parse.c l_pts.c
OBJ			= $(addprefix ${OBJDIR}, $(SRC:.c=.o))
LIBRARY		= -L libft -lft -L mlx2020 -lmlx
LIB_FILE	= libft/libft.a libmlx.dylib
CC			= gcc
FLAGS		= -Wall -Wextra -Werror
#FLAGS		+= -O2
FLAGS		+= -fsanitize=address -g
#FLAGS		+= -Ofast

#	RULES
all: ${OBJDIR} ${NAME}

${OBJDIR}:
	@mkdir -p ${OBJDIR}

${NAME}: ${OBJ} ${LIB_FILE}
	${CC} ${FLAGS} ${LIBRARY} $^ -framework OpenGL -framework AppKit -o ${NAME}

${OBJDIR}%.o: %.c ${INC} Makefile
	${CC} ${FLAGS} -c $< -o $@

libft/libft.a:
	make -C libft

clean:
	rm -rf ${OBJDIR}

fclean:	clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re 
