NAME = fractol

CC = gcc

INC=/usr/include

INCLIB=/usr/lib

LFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

CFLAGS= -I$(INC) -O3 -Imlx -g

HEADER = fractol.h

SRCS = main2.c prog_utils.c

RM = rm -f

OBJS = $(SRCS:%.c=%.o)

%.o: %.c $(HEADER)
	$(CC) -Wall -Wextra -Werror -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(MLBX)
	$(CC) -o $(NAME) $(OBJS) $(LFLAGS)

$(MLBX):
	@make -C mlx

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			clean all

.PHONY:		all clean fclean re