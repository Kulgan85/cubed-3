# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 14:18:22 by jwilliam          #+#    #+#              #
#    Updated: 2023/02/06 15:54:44 by tbertozz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = gcc -g

INCL = includes

LIB = Libft
GNL = gnl

MLX = minilibx
#MLX = minilibx-linux

FLAGS = -Wall -Werror -Wextra

MLX_FL = -framework OpenGL -framework Appkit
#MLX_FL = -L/usr/lib -lXext -lX11 -lm -lz

RM = rm -rf

FILES = main.c \
		close_game.c \
		draw_beegee.c \
		error.c \
		imageload.c \
		init_img.c \
		init_mlx.c \
		init_player.c \
		key_input.c \
		loops.c \
		map_check.c \
		map_check_utils.c \
		map_check_utils2.c \
		map_file_check.c \
		map_file_check_utils.c \
		mlx_hooks.c \
		movement.c \
		raycasting.c \
		tilemap_generator.c \

OBJS_NAME = $(FILES:.c=.o)

OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
SRCS = $(addprefix $(SRC_DIR), $(FILES))
SRC_DIR = ./3dcube/srcs/
OBJS_DIR = ./3dcube/objs/

all: $(NAME)

$(NAME): $(OBJS)
		@$(MAKE) -C ./3dcube/$(LIB)
		@$(MAKE) -C ./3dcube/$(MLX)
		@$(CC) $(FLAGS) $(OBJS) -L$(LIB) ./3dcube/$(LIB)/libft.a  -L$(MLX) ./3dcube/$(MLX)/libmlx.a -o $@ $(MLX_FL)
		@echo "\033[32m████████████████████████████"
		@echo "\033[32m█████\033[39mcub3D      created\033[32m█████"
		@echo "\033[32m████████████████████████████\033[39m"

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
		@mkdir -p $(OBJS_DIR)
		@$(CC) $(FLAGS) $(GNL_FILES) -o $@ -c $< -I ./3dcube/$(INCL) -I ./3dcube/$(GNL) -I ./3dcube/$(LIB)/$(INCL) -I ./3dcube/$(MLX) 

clean:
		@$(MAKE) clean -C ./3dcube/$(LIB)
		@$(MAKE) clean -C ./3dcube/$(MLX)
		@$(RM) $(OBJS)
		@$(RM) $(OBJS_DIR)
		@echo "\033[33m████████████████████████████"
		@echo "\033[33m█████\033[39mcleaned      cub3D\033[33m█████"
		@echo "\033[33m█████   \033[39mobject files   \033[33m█████"		
		@echo "\033[33m████████████████████████████\033[39m"

fclean:	clean
		@$(MAKE) fclean -C ./3dcube/$(LIB)
		@$(MAKE) clean -C ./3dcube/$(MLX)		
		@$(RM) $(NAME)
		@$(RM) $(NAME).a
		@echo "\033[33m████████████████████████████"
		@echo "\033[33m█████      \033[39mcleaned     \033[33m█████"
		@echo "\033[33m█████  \033[39mcub3D     file  \033[33m█████"		
		@echo "\033[33m████████████████████████████\033[39m"

re: fclean all

.PHONY: clean fclean all re
