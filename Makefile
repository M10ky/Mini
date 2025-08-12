NAME_CLIENT = client
NAME_SERVER = server
NAME_CLIENT_BONUS = client_bonus
NAME_SERVER_BONUS = server_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_PRINTF = \
	ft_printf/ft_check.c \
	ft_printf/ft_print_char.c \
	ft_printf/ft_print_hex.c \
	ft_printf/ft_print_int.c \
	ft_printf/ft_print_pointer.c \
	ft_printf/ft_print_string.c \
	ft_printf/ft_print_unsigned.c \
	ft_printf/ft_printf.c \
	ft_printf/ft_utils.c

SRC_CLIENT = client.c ft_utils.c
SRC_SERVER = server.c ft_utils.c

SRC_CLIENT_BONUS = client_bonus.c ft_utils.c
SRC_SERVER_BONUS = server_bonus.c ft_utils.c

OBJ_PRINTF = $(SRC_PRINTF:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT_BONUS = $(SRC_CLIENT_BONUS:.c=.o)
OBJ_SERVER_BONUS = $(SRC_SERVER_BONUS:.c=.o)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT) $(OBJ_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(OBJ_PRINTF)

$(NAME_SERVER): $(OBJ_SERVER) $(OBJ_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJ_SERVER) $(OBJ_PRINTF)

bonus: $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

$(NAME_CLIENT_BONUS): $(OBJ_CLIENT_BONUS) $(OBJ_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT_BONUS) $(OBJ_CLIENT_BONUS) $(OBJ_PRINTF)

$(NAME_SERVER_BONUS): $(OBJ_SERVER_BONUS) $(OBJ_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME_SERVER_BONUS) $(OBJ_SERVER_BONUS) $(OBJ_PRINTF)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_CLIENT_BONUS) $(OBJ_SERVER_BONUS) $(OBJ_PRINTF)

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

re: fclean all
