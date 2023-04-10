# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cherrewi <cherrewi@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/04/10 16:19:18 by cherrewi      #+#    #+#                  #
#    Updated: 2023/04/10 16:37:59 by cherrewi      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = pipex
FLAGS = -Wall -Wextra -Werror
SRC_DIR = sources
SRCS =	main.c parsing_utils.c parse_argv.c execute_commands.c pipes.c \
		parsing.c path_utils.c error_handling.c set_file_descriptors.c
SRCS_BONUS =	main_bonus.c parsing_utils.c parse_argv.c execute_commands.c \
				pipes.c parsing.c path_utils.c error_handling.c \
				set_file_descriptors.c
OBJ_DIR = obj
OBJS_REG = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
OBJS_BONUS = $(addprefix $(OBJ_DIR)/, $(SRCS_BONUS:.c=.o))
ifdef PIPEX_BONUS
OBJS = $(OBJS_BONUS)
else
OBJS = $(OBJS_REG)
endif

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

bonus: $(OBJS_BONUS)
	$(MAKE) PIPEX_BONUS=1

TEST_SRCS = test.c test_is_trail_space.c test_is_separator_space.c test_count_words.c test_split_argv.c test_create_command.c test_ft_printf_fd.c test_trim_quotes.c
test: $(NAME)
	$(CC) -g $(FLAGS) $(addprefix tests/, $(TEST_SRCS)) sources/parsing_utils.c sources/parse_argv.c sources/pipes.c sources/parsing.c sources/path_utils.c sources/error_handling.c sources/set_file_descriptors.c $(LIBFT_DIR)/$(LIBFTNAME) -o test.out

.PHONY: all clean fclean re test
