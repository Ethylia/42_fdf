SRC_FILES = fdf.c \
            camera.c \
            file.c \
            framebuffer.c \
            input.c \
            map.c \
			util.c \
            math/geometric.c \
        	math/mat4.c \
            math/math.c \
            math/transform.c \
			math/vec4.c

SRC_DIR = src

OBJ_DIR=obj
OBJ:=$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))

NAME=fdf

all: mlx $(NAME)

CC=gcc
CFLAGS=-Wall -Wpedantic -Werror -Isrc -Imlx/include -Ofast -mfpmath=sse -msse3 -ffast-math
LDFLAGS=-Lmlx/build -Ofast -mfpmath=sse -msse3 -ffast-math
LDLIBS=-lmlx42 -lglfw

ifeq ($(shell uname),Darwin)
# Mac OS
CFLAGS+=-DMACOS
LDFLAGS+=-L${HOME}/.brew/lib
LDLIBS+=-framework OpenGL -framework AppKit -framework IOKit
else
# Linux
CFLAGS+=-DLINUX
LDLIBS+=-lGL
endif

debug: CFLAGS=-Wall -Wpedantic -Werror -Isrc -Imlx/include -g -DDEBUG
debug: LDFLAGS+=-g
debug: all

mlx/build/libmlx42.a:
	cmake -S mlx -B mlx/build
	$(MAKE) -C mlx/build -j4

mlx: mlx/build/libmlx42.a

clean:
	@-find $(OBJ_DIR) -type f -name '*.o' -delete
	@-find $(OBJ_DIR) -type f -name '*.d' -delete

fclean: clean
	@-rm -f $(NAME)
	@-rm -fr $(OBJ_DIR)

re: fclean all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $< -MMD

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $(NAME)

.PHONY: clean fclean re all mlx

-include $(OBJ:.o=.d)
