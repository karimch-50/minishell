NAME = minishell
# NAME_B = minishell_bonus

# LIBFT = libft/libft.a

# SRCS = 

# SRCS_B = 

OBJS = $(SRCS:.c=.o)

OBJS_B = $(SRCS_B:.c=.o)

RDL = -lreadline

FLAGS = -Wall -Wextra -Werror

CCe = cc

# all: $(LIBFT) $(NAME)

# $(LIBFT):
# 	make -C libft && make clean -C libft 

%.o : %.c
	$(CCe) $(FLAGS) -c $< -o $@

# $(NAME): $(OBJS)
# 	$(CCe) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# bonus: $(LIBFT) $(NAME_B)

$(NAME_B) : $(OBJS_B)
	$(CCe) $(FLAGS) $(OBJS_B) $(LIBFT) -o $(NAME_B)

clean:
	rm -rf $(OBJS) $(OBJS_B)

fclean: clean
	rm -rf $(NAME) $(NAME_B) $(LIBFT)

re : fclean all

.PHONY: all clean fclean re bonus