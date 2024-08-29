NAME	:= cub3d
CC		:= cc
CFLAGS	:= -Wextra -Wall -Werror
LIBMLX	:= ./MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -L"/Users/$(USER)/.brew/opt/glfw/lib/"
SRCS	:= main.c get-next-line/get_next_line.c get-next-line/get_next_line_utils.c handle_map.c handle_map_utils.c \
			free_utils.c start_game.c put_images.c setup_elements.c alloc_elements.c
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -fsanitize=address -g -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) -fsanitize=address -g $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx