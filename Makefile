SERVER = server
SERVER_SRC = server.c
CLIENT = client
CLIENT_SRC = client.c
PRINTF = ft_printf
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: library $(SERVER) $(CLIENT)

library:
	@make -C $(PRINTF)

$(SERVER):
	cc $(SERVER_SRC) $(CFLAGS) -L $(PRINTF) -o $(SERVER) -lftprintf

$(CLIENT):
	cc $(CLIENT_SRC) $(CFLAGS) -L $(PRINTF) -o $(CLIENT) -lftprintf

clean:
	$(RM) $(CLIENT) $(SERVER)
	@make clean -C $(PRINTF)

fclean: clean
	$(RM) $(CLIENT) $(SERVER)
	@make fclean -C $(PRINTF)

re:	fclean all

.PHONY: all, re, fclean, clean
