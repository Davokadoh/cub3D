# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 11:31:44 by jleroux           #+#    #+#              #
#    Updated: 2022/12/21 13:25:38 by jleroux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	cub3D

LIBS        :=	m ft mlx
LIBS_TARGET :=	lib/libft/libft.a \
				lib/minilibx_opengl_20191021/libmlx.a \

INCS        :=	include \
				lib/libft/include \
				lib/minilibx_opengl_20191021/ \

SRC_DIR		:=	src
SRCS		:=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/parsing.c \
				$(SRC_DIR)/textures.c \
				$(SRC_DIR)/paths.c \
				$(SRC_DIR)/map.c \
				$(SRC_DIR)/map_check.c \
				$(SRC_DIR)/camera.c \
				$(SRC_DIR)/minimap.c \
				$(SRC_DIR)/move.c \
				$(SRC_DIR)/turn.c \
				$(SRC_DIR)/render.c \
				$(SRC_DIR)/draw3d.c \
				$(SRC_DIR)/anim.c \
				$(SRC_DIR)/raycasting1.c \
				$(SRC_DIR)/raycasting2.c \
				$(SRC_DIR)/hooks.c \
				$(SRC_DIR)/vector2d.c \
				$(SRC_DIR)/line.c \
				$(SRC_DIR)/rgb.c \
				$(SRC_DIR)/gnl.c \
				$(SRC_DIR)/error.c \

CC          :=	gcc
CFLAGS      :=	-Wall -Wextra -Werror
CPPFLAGS    :=	$(addprefix -I,$(INCS)) -MMD -MP -O2 #-fsanitize=address -g
LDFLAGS     :=	$(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS      :=	$(addprefix -l,$(LIBS)) -framework OpenGL -framework Appkit

RM			:= rm -rf
MAKEFLAGS   += --no-print-directory #--silent

all: $(NAME)

debug: run

ifeq ($(MAKECMDGOALS), debug)
    CFLAGS += -g3 -DDEBUG
	BUILD = debug
else
    CFLAGS += -O3 -DNDEBUG
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
	@-./$(NAME) maps/test.cub

noel: all
	@-./$(NAME) maps/noel.cub

.PHONY: all clean fclean re debug release
