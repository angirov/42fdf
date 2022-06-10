NAME = fdf

SRCS_DIR = srcs/
SRCS_FILES =	main.c \
				make_data.c \
				read_map.c \
				plotting.c \
				rotation.c \
				key_hooks.c \
				exits.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJ = ${SRCS:.c=.o}

HEADERS = $(SRCS_DIR)fdf.h

# ========== libraries ==========
LIB_DIR = libs

LIBFT_DIR = $(LIB_DIR)/libft
LIBFT_A = $(LIBFT_DIR)/libft.a


LIBFT_PRINTF_DIR = $(LIB_DIR)/libft_printf
LIBFT_PRINTF_A = $(LIBFT_PRINTF_DIR)/libftprintf.a

ALL_LIBS = $(LIBFT_PRINTF_A) $(LIBFT_A)

# ========== compilation ==========
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAFS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
INCLUDES_LOCAL = -I$(SRCS_DIR) -I$(LIBFT_DIR) -I$(LIBFT_PRINTF_DIR)
# ========== rules ==========
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(INCLUDES_LOCAL) $(ALL_LIBS) $(HEADERS) $(MLX_FLAFS) -o $(NAME)

%.o: %.c $(HEADERS) makelibs
	$(CC) $(CFLAGS) $(INCLUDES_LOCAL) -I/usr/include -Imlx_linux -c $< -o $@ 

makelibs:
	make bonus -C $(LIBFT_DIR)
	make -C $(LIBFT_PRINTF_DIR)

clean: cleanlibs
	rm $(OBJ)

fclean: fcleanlibs
	rm $(OBJ) $(NAME)

cleanlibs:
	make clean -C $(LIBFT_DIR)
	make clean -C $(LIBFT_PRINTF_DIR)

fcleanlibs:
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(LIBFT_PRINTF_DIR)

test:
	@echo $(OBJ)

.PHONY: all clean fclean re makelibs test