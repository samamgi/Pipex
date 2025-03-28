SRC =		pipex.c					\
	
BONUS_SRC =	src/pipexbb.c				\

NAME =		pipex

BONUS_NAME = 

CFLAGS =	-Wall -Werror -Wextra -g3 

CC =		cc

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(BONUS_SRC:.c=.o)

all:		$(NAME)

$(NAME): $(OBJ) libft/libft.a
		$(CC) $(CFLAGS) -o $@ $^

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ)
		$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
		rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: clean fclean all re bonus