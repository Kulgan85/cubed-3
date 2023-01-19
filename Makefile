# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbertozz <tbertozz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 14:18:22 by jwilliam          #+#    #+#              #
#    Updated: 2023/01/19 09:57:20 by tbertozz         ###   ########.fr        #
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
		error.c \
		init_mlx.c \
		key_input.c \
		map_check.c \
		map_check_utils.c \
		map_file_check.c \
		mlx_hooks.c \
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
		@echo "\033[32m█████\033[39mminishell  created\033[32m█████"
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
		@echo "\033[33m█████\033[39mcleaned  minishell\033[33m█████"
		@echo "\033[33m█████   \033[39mobject files   \033[33m█████"		
		@echo "\033[33m████████████████████████████\033[39m"

fclean:	clean
		@$(MAKE) fclean -C ./3dcube/$(LIB)
		@$(MAKE) clean -C ./3dcube/$(MLX)		
		@$(RM) $(NAME)
		@$(RM) $(NAME).a
		@echo "\033[33m████████████████████████████"
		@echo "\033[33m█████      \033[39mcleaned     \033[33m█████"
		@echo "\033[33m█████  \033[39mminishell file  \033[33m█████"		
		@echo "\033[33m████████████████████████████\033[39m"

re: fclean all

.PHONY: clean fclean all re
