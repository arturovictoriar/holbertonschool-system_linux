.PHONY = strace_0 strace_1 strace_2 strace_3 strace_4 strace_5 strace_6 strace_7 strace_8 clean re

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g
OBJDIR = targets/

SRC0 = 0-ptrace.c
OBJ0 = $(addprefix $(OBJDIR), $(SRC0:%.c=%.o))

SRC1 = 1-ptrace.c
OBJ1 = $(addprefix $(OBJDIR), $(SRC1:%.c=%.o))

SRC2 = 2-ptrace.c
OBJ2 = $(addprefix $(OBJDIR), $(SRC2:%.c=%.o))

SRC3 = 3-ptrace.c
OBJ3 = $(addprefix $(OBJDIR), $(SRC3:%.c=%.o))

SRC4 = 4-ptrace.c
OBJ4 = $(addprefix $(OBJDIR), $(SRC4:%.c=%.o))

SRC5 = 5-ptrace.c
OBJ5 = $(addprefix $(OBJDIR), $(SRC5:%.c=%.o))

SRC6 = 6-ptrace.c
OBJ6 = $(addprefix $(OBJDIR), $(SRC6:%.c=%.o))

SRC7 = 7-ptrace.c
OBJ7 = $(addprefix $(OBJDIR), $(SRC7:%.c=%.o))

SRC8 = 8-ptrace.c
OBJ8 = $(addprefix $(OBJDIR), $(SRC8:%.c=%.o))

strace_0: syscalls.h $(OBJDIR) $(OBJ0)
	gcc $(CFLAGS) -o $@ $(OBJ0)

strace_1: syscalls.h $(OBJDIR) $(OBJ1)
	gcc $(CFLAGS) -o $@ $(OBJ1)

strace_2: syscalls.h $(OBJDIR) $(OBJ2)
	gcc $(CFLAGS) -o $@ $(OBJ2)

strace_3: syscalls.h $(OBJDIR) $(OBJ3)
	gcc $(CFLAGS) -o $@ $(OBJ3)

strace_4: syscalls.h $(OBJDIR) $(OBJ4)
	gcc $(CFLAGS) -o $@ $(OBJ4)

strace_5: syscalls.h $(OBJDIR) $(OBJ5)
	gcc $(CFLAGS) -o $@ $(OBJ5)

strace_6: syscalls.h $(OBJDIR) $(OBJ6)
	gcc $(CFLAGS) -o $@ $(OBJ6)

strace_7: syscalls.h $(OBJDIR) $(OBJ7)
	gcc $(CFLAGS) -o $@ $(OBJ7)

strace_8: syscalls.h $(OBJDIR) $(OBJ8)
	gcc $(CFLAGS) -o $@ $(OBJ8)

$(OBJDIR)%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	-rm -rf $(OBJDIR)
	-rm -r strace_0
	-rm -r strace_1
	-rm -r strace_2
	-rm -r strace_3
	-rm -r strace_4
	-rm -r strace_5
	-rm -r strace_6
	-rm -r strace_7
	-rm -r strace_8

re: clean strace_0 strace_1 strace_2 strace_3 strace_4 strace_5 strace_6 strace_7 strace_8
