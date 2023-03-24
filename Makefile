NAME = pipex
# FLAGS = -Wall -Wextra -Werror
FLAGS = -g -Wall -Wextra
SRC_DIR = sources
SRCS = main.c parsing_utils.c parse_argv.c create_command.c execute_commands.c pipes.c parsing.c
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
LIBFT_DIR = libft
LIBFTNAME = libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_DIR)/$(LIBFTNAME)
	$(CC) $(FLAGS) $^ -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(FLAGS) $< -o $@

$(LIBFT_DIR)/$(LIBFTNAME):
	$(MAKE) -C $(LIBFT_DIR) bonus

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

TEST_SRCS = test.c test_is_trail_space.c test_is_separator_space.c test_count_words.c test_split_argv.c test_create_command.c test_ft_printf_fd.c
test: $(NAME)
	$(CC) -g $(FLAGS) $(addprefix tests/, $(TEST_SRCS)) sources/parsing_utils.c sources/parse_argv.c sources/create_command.c sources/pipes.c sources/parsing.c $(LIBFT_DIR)/$(LIBFTNAME) -o test.out

.PHONY: all clean fclean re test
