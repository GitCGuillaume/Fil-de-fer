PATH_WIN = ./srcs/window

PATH_TOOLS = ./srcs/tools

PATH_GNL = ./srcs/gnl

SRCS_SEGMENT = $(PATH_WIN)/segment/segment.c $(PATH_WIN)/segment/segment_draw.c $(PATH_WIN)/segment/segment_start.c $(PATH_WIN)/segment/segment_tools.c

SRCS_BREN = $(PATH_WIN)/bresenham/bresenham_tools.c $(PATH_WIN)/bresenham/bresenham_two.c $(PATH_WIN)/bresenham/bresenham.c

SRCS_WIN = $(PATH_WIN)/main.c

SRCS_PARSE = ./srcs/parse_map/parse.c

SRCS_TOOLS = $(PATH_TOOLS)/close.c $(PATH_TOOLS)/ft_isspace.c $(PATH_TOOLS)/ft_swap.c $(PATH_TOOLS)/pixel.c

SRCS_GNL = $(PATH_GNL)/get_next_line.c $(PATH_GNL)/get_next_line_utils.c

SRCS_MAIN = ./srcs/main.c

SRCS_LIBFT = ./libft/ft_strchr.o ./libft/ft_putstr_fd.o ./libft/ft_isdigit.o ./libft/ft_isprint.o \
	     ./libft/ft_strlen.o ./libft/ft_atoi.o ./libft/ft_strjoin.o ./libft/ft_strdup.o ./libft/ft_substr.o \
	     ./libft/ft_split.o ./libft/ft_strnstr.o ./libft/ft_strcmp.c

OBJS_SEGMENT = $(SRCS_SEGMENT:.c=.o)

OBJS_BREN = $(SRCS_BREN:.c=.o)

OBJS_WIN = $(SRCS_WIN:.c=.o)

OBJS_PARSE = $(SRCS_PARSE:.c=.o)

OBJS_TOOLS = $(SRCS_TOOLS:.c=.o)

OBJS_GNL = $(SRCS_GNL:.c=.o)

OBJS_MAIN = $(SRCS_MAIN:.c=.o)

NAME = fdf

RM = rm -f

.c.o:
	clang -Wall -Wextra -Werror -Iincludes -Ilibft -Iminilibx-linux -Isrcs/gnl -c $< -o $(<:.c=.o)

$(NAME): $(OBJS_BREN) $(OBJS_SEGMENT) $(OBJS_WIN) $(OBJS_PARSE) $(OBJS_GNL) $(OBJS_TOOLS) $(OBJS_MAIN)
	make all -C ./libft
	make -C ./minilibx-linux
	clang -Wall -Wextra -Werror -Iincludes -Ilibft -Iminilibx-linux -L./minilibx-linux -Isrcs/gnl -o $(NAME) $(SRCS_LIBFT) $(OBJS_GNL) $(OBJS_TOOLS) $(OBJS_PARSE) $(OBJS_BREN) $(OBJS_SEGMENT) $(OBJS_WIN) $(OBJS_MAIN) -lm -lmlx -lXext -lX11

all:	$(NAME)

clean:
	$(RM) $(OBJS_BREN) $(OBJS_SEGMENT) $(OBJS_WIN) $(OBJS_PARSE) $(OBJS_GNL) $(OBJS_TOOLS) $(OBJS_MAIN)
	make clean -C ./libft
	make clean -C ./minilibx-linux

fclean:
	make clean
	make fclean -C ./libft
	make clean -C ./minilibx-linux
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re
