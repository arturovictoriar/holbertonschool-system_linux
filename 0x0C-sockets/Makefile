.PHONY: all clean re

OBJDIR = targets/
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g
SERVER = server.c
SRC0 = api_rest_0.c $(SERVER)
OBJ0 = $(addprefix $(OBJDIR), $(SRC0:%.c=%.o))
SRC1 = api_rest_1.c $(SERVER)
OBJ1 = $(addprefix $(OBJDIR), $(SRC1:%.c=%.o))
SRC2 = api_rest_2.c $(SERVER)
OBJ2 = $(addprefix $(OBJDIR), $(SRC2:%.c=%.o))
SRC3 = api_rest_3.c $(SERVER)
OBJ3 = $(addprefix $(OBJDIR), $(SRC3:%.c=%.o))

all : todo_api_0

todo_api_0: $(OBJDIR) $(OBJ0)
	$(CC) $(CFLAGS) -o $@ $(OBJ0)

todo_api_1: $(OBJDIR) $(OBJ1)
	$(CC) $(CFLAGS) -o $@ $(OBJ1)

todo_api_2: $(OBJDIR) $(OBJ2)
	$(CC) $(CFLAGS) -o $@ $(OBJ2)

todo_api_3: $(OBJDIR) $(OBJ3)
	$(CC) $(CFLAGS) -o $@ $(OBJ3)

$(OBJDIR)%.o: %.c api.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	-rm -rf $(OBJDIR)

re: clean all
