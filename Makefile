NAME	:= fractol

NAME_BONUS	:= fractol_bonus

CFLAGS	:= -Wextra -Wall -Werror

LIBMLX	:= ./MLX42

LIBLIBFT	:= ./libft/complete_Libft

HEADERS	:= -I ./include -I $(LIBMLX)/include -I $(LIBLIBFT)
HEADERS_BONUS	:= -I ./include -I $(LIBMLX)/include -I $(LIBLIBFT)

LIBS	:= $(LIBMLX)/build/libmlx42.a -L$(LIBLIBFT) -lft -ldl -lglfw -pthread -lm

SRCS	:= ./src/fractol.c ./src/mandelbrot.c ./src/colors.c ./src/hooks.c ./src/utils.c
SRCS_BONUS	:= ./bonus/colors_bonus.c ./bonus/fractol_bonus.c ./bonus/hooks_bonus.c ./bonus/mandelbrot_bonus.c ./bonus/utils_bonus.c ./bonus/color_shift.c

OBJS	:= ${SRCS:.c=.o}
OBJS_BONUS	:= ${SRCS_BONUS:.c=.o}

RM = rm -rf

all: libft libmlx $(NAME)

bonus: libft libmlx $(NAME_BONUS)

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

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) $(OBJS_BONUS) $(LIBS) $(HEADERS_BONUS) -o $(NAME_BONUS)
	@echo "$(NAME_BONUS) compiled successfully with bonuses.\n"
	
.bonus: $(OBJS_BONUS)
	@$(CC) @(OBJS_BONUS) $(LIBS) $(HEADERS_BONUS) -o $(NAME_BONUS)
	@echo "Bonus build completed.\n"
	@touch .bonus

clean:
	@$(RM) $(OBJS) $(OBJS_BONUS)
	@$(RM) $(LIBMLX)/build
	@$(MAKE) -C $(LIBLIBFT) clean

fclean: clean
	@$(RM) $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIBLIBFT) fclean

re: fclean all

.PHONY: all clean fclean re libmlx libft
