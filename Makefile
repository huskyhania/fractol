NAME	:= fractol
CFLAGS	:= -Wextra -Wall -Werror
LIBMLX	:= ./MLX42
LIBLIBFT	:= ./libft/complete_Libft

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBLIBFT)
LIBS	:= $(LIBMLX)/build/libmlx42.a -L$(LIBLIBFT) -lft -ldl -lglfw -pthread -lm
SRCS	:= ./src/fractol.c ./src/mandelbrot_bonus.c ./src/colors_bonus.c ./src/hooks.c ./src/values.c
OBJS	:= ${SRCS:.c=.o}

RM = rm -rf

all: libft libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@$(MAKE) -C $(LIBLIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) $< -c -o $@ $(HEADERS) 
	@printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "$(NAME) compiled successfully.\n"
clean:
	@$(RM) $(OBJS)
	@$(RM) $(LIBMLX)/build
	@$(MAKE) -C $(LIBLIBFT) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBLIBFT) fclean

re: fclean all

.PHONY: all clean fclean re libmlx libft
