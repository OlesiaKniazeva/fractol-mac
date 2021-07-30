INC=/usr/include


INCLIB=/user/lib

CC=gcc

CFLAGS= -I$(INC) -O3 -Iminilbx -g

NAME= fractol
HEADER = fractol.h
SRC = main.c
OBJ = $(SRC:%.c=%.o)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -O3 -c $< -o $@

LFLAGS = -Lminilibx -lmlx -L$(INCLIB) -Iminilbx -lXext -lX11 -lm

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	# mac
else
	#Linux and others...
	LFLAGS += -lbsd
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

show:
	@printf "UNAME		: $(UNAME)\n"
	@printf "NAME  		: $(NAME)\n"
	@printf "CC		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "LFLAGS		: $(LFLAGS)\n"
	@printf "SRC		:\n	$(SRC)\n"
	@printf "OBJ		:\n	$(OBJ)\n"

clean:
	rm -f $(NAME) $(OBJ)

re: clean all
