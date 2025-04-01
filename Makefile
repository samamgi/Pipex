SRC =		src/cmdexec.c \
			src/pipex.c \
			src/utils.c
NAME =		pipex


CFLAGS =	-Wall -Werror -Wextra -g3

CC =		cc

OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft

LIBFT_OBJ = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_OBJ)
		$(CC) $(CFLAGS) -o $@ $^ 

%.o: %.c inc/pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_OBJ):
		$(MAKE) -C $(LIBFT_DIR)

clean:
		rm -f $(OBJ)
		$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
		rm -f $(NAME)
		$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: clean fclean all re bonus
