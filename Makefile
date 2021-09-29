PATH_WIN = ./srcs/window

PATH_TOOLS = ./srcs/tools

PATH_GNL = ./srcs/gnl

SRCS_SEGMENT = $(PATH_WIN)/segment/segment.c $(PATH_WIN)/segment/segment_draw.c $(PATH_WIN)/segment/segment_start.c $(PATH_WIN)/segment/segment_tools.c

SRCS_BREN = $(PATH_WIN)/bresenham/bresenham_tools.c $(PATH_WIN)/bresenham/bresenhan.c $(PATH_WIN)/bresenham/bresenham_two.c

SRCS_WIN = $(PATH_WIN)/main.c

SRCS_PARSE = ./srcs/parse_map/parse.c

SRCS_TOOLS = $(PATH_TOOLS)/close.c $(PATH_TOOLS)/ft_isspace.c $(PATH_TOOLS)/ft_swap.c $(PATH_TOOLS)/pixel.c

SRCS_GNL = $(PATH_GNL)/get_next_line.c $(PATH_GNL)/get_next_line_utils.c

OBJS_SEGMENT = $(SRCS_SEGMENT:.c=.o)

OBJS_BREN = $(SRCS_BREN:.c=.o)

OBJS_WIN = $(SRCS_WIN:.c=.o)

OBJS_PARSE = $(SRCS_PARSE:.c=.o)

OBJS_TOOLS = $(SRCS_TOOLS:.c=.o)

OBJS_GNL = $(SRCS_GNL:.c=.o)

NAME = fdf

RM = rm -f

.c.o:
	clang -Wall -Wextra -Werror -Iincludes -Ilibft -Iminilibx-linux -L./minilibx-linux -Isrcs/gnl -c $< -o $(<:.c=.o)

$(NAME): $(OBJS_BREN) $(OBJS_SEGMENT) $(OBJS_WIN) $(OBJS)
	make -C libft
