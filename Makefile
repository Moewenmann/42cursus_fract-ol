# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julian <julian@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 17:43:53 by jmuhlber          #+#    #+#              #
#    Updated: 2024/03/30 17:23:50 by julian           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CFLAGS = -Wall -Wextra -Werror

LIBS = $(MLXDIR)/build/libmlx42.a -ldl -lglfw -pthread -lm ./lib/libft/libft.a

MLXDIR = ./lib/mlx

LIBFTDIR = ./lib/libft

HEADER = -I ./src -I $(MLXDIR)/include -I $(LIBFTDIR)

SRCDIR = ./src/

SOURCE = $(SRCDIR)fractol.c\
			$(SRCDIR)hooks.c\
			$(SRCDIR)utils.c\
			$(SRCDIR)mandelbrot.c\
			$(SRCDIR)julia.c\
			$(SRCDIR)burningship.c\

OBJ = $(SOURCE:.c=.o)

COMPILER = cc


all: libmlx libft $(NAME)

libft:
	@if [ ! -d $(LIBFTDIR) ]; then \
		echo "LIBFTDIR not found! - Cloning libf from github."; \
		git clone git@github.com:Moewenmann/42cursus_Libft.git $(LIBFTDIR); \
	fi
	@make -C $(LIBFTDIR)

libmlx:
	@if [ ! -d $(MLXDIR) ]; then \
		echo "MLXDIR not found! - Cloning mlx from github."; \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLXDIR); \
	fi
	@cmake $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4

%.o: %.c
	@$(COMPILER) $(CFLAGS) $(HEADER) -c $< -o $@

$(NAME): $(OBJ)
	$(COMPILER) $(OBJ) $(LIBS) -o $(NAME)

clean:
	@if [ -d "$(LIBFTDIR)" ]; then \
		rm -f $(OBJ); \
		make -C $(LIBFTDIR) clean; \
	else \
		echo "LIBFTDIR not found!"; \
	fi
	@if [ -d "$(MLXDIR)" ]; then \
		rm -rf $(MLXDIR)/build; \
	else \
		echo "MLXDIR not found!"; \
	fi

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		rm -f $(NAME); \
	fi
	@if [ -d "$(LIBFTDIR)" ]; then \
		make -C $(LIBFTDIR) fclean; \
	fi

re: fclean all

install:
	@brew install glfw
	@if [ ! -d $(MLXDIR) ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLXDIR); \
	else \
		echo "MLX is already installed. Run make rmlib to remove libs."; \
	fi
	@if [ ! -d $(LIBFTDIR) ]; then \
		git clone git@github.com:Moewenmann/42cursus_Libft.git $(LIBFTDIR); \
	else \
		echo "libft is already installed. Run make rmlib to remove libs."; \
	fi

relib:
	@rm -rf $(MLXDIR)
	@rm -rf $(LIBFTDIR)
	@make install

rmlib:
	@rm -rf $(MLXDIR)
	@rm -rf $(LIBFTDIR)

.PHONY: all clean fclean re libmlx libft install
