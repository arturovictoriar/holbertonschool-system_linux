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

CRUD_SERVER = crud_server_req.c crud_server_res.c parse.c todo.c
SRC4 = post_method.c check_req_1.c $(CRUD_SERVER)
OBJ4 = $(addprefix $(OBJDIR), $(SRC4:%.c=%.o))
SRC5 = post_method.c get_method.c check_req_2.c $(CRUD_SERVER)
OBJ5 = $(addprefix $(OBJDIR), $(SRC5:%.c=%.o))
SRC6 = post_method.c get_method.c check_req_2.c $(CRUD_SERVER)
OBJ6 = $(addprefix $(OBJDIR), $(SRC6:%.c=%.o))
SRC7 = post_method.c get_method.c delete_method.c check_req_3.c $(CRUD_SERVER)
OBJ7 = $(addprefix $(OBJDIR), $(SRC7:%.c=%.o))

all : todo_api_0

todo_api_0: $(OBJDIR) $(OBJ0)
	$(CC) $(CFLAGS) -o $@ $(OBJ0)

todo_api_1: $(OBJDIR) $(OBJ1)
	$(CC) $(CFLAGS) -o $@ $(OBJ1)

todo_api_2: $(OBJDIR) $(OBJ2)
	$(CC) $(CFLAGS) -o $@ $(OBJ2)

todo_api_3: $(OBJDIR) $(OBJ3)
	$(CC) $(CFLAGS) -o $@ $(OBJ3)

todo_api_4: $(OBJDIR) $(OBJ4)
	$(CC) $(CFLAGS) -o $@ $(OBJ4)

todo_api_5: $(OBJDIR) $(OBJ5)
	$(CC) $(CFLAGS) -o $@ $(OBJ5)

todo_api_6: $(OBJDIR) $(OBJ6)
	$(CC) $(CFLAGS) -o $@ $(OBJ6)

todo_api_7: $(OBJDIR) $(OBJ7)
	$(CC) $(CFLAGS) -o $@ $(OBJ7)

$(OBJDIR)%.o: %.c api.h crud.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	-rm -rf $(OBJDIR)

re: clean all
