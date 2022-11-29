# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 11:31:44 by jleroux           #+#    #+#              #
#    Updated: 2022/11/29 12:28:13 by jleroux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	cub3dD

LIBS        :=	m ft mlx
LIBS_TARGET :=	lib/libft/libft.a \
				lib/minilibx_opengl_20191021/libmlx.a \

INCS        :=	include \
				lib/libft/include \
				lib/minilibx_opengl_20191021/ \

SRC_DIR		:=	src
SRCS		:=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/rgb.c \

CC          :=	gcc
CFLAGS      :=	-Wall -Wextra -Werror
CPPFLAGS    :=	$(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS     :=	$(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS      :=	$(addprefix -l,$(LIBS)) -framework OpenGL -framework Appkit

RM			:= rm -rf
MAKEFLAGS   += --no-print-directory #--silent

all: $(NAME)

debug: all

ifeq ($(MAKECMDGOALS), debug)
    CFLAGS = -g3 -DDEBUG
	BUILD = debug
else
    CFLAGS = -O3 -DNDEBUG
	BUILD = release
endif

BUILD_DIR   :=	.build/$(BUILD)
OBJS		:=	$(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        :=	$(OBJS:.o=.d)

$(NAME): $(OBJS) $(LIBS_TARGET)
	@$(CC) -o $(NAME) $(CPPFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS)

$(LIBS_TARGET):
	@$(MAKE) -C $(@D)

$(BUILD_DIR):
	@mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEPS)

clean:
	@$(MAKE) -C lib/libft clean
	@$(RM) $(BUILD_DIR)

fclean: clean
	@$(MAKE) -C lib/libft fclean
	@$(MAKE) -C lib/minilibx_opengl_20191021 clean
	@$(RM) $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

run: all
	@-./$(NAME) test

.PHONY: all clean fclean re debug release
