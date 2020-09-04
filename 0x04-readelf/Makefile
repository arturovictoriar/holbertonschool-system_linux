.PHONY = 0-hreadelf 1-hreadelf 2-hreadelf all clean re

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic
OBJDIR = targets/
SRC1 = 0-hreadelf.c print_elf_header_utils1.c print_elf_header_utils2.c print_elf_header_utils3.c print_elf_header_utils4.c print_elf_header_utils5.c
SRC2 = 1-hreadelf.c
SRC3 = 2-hreadelf.c
OBJ1 = $(addprefix $(OBJDIR), $(SRC1:%.c=%.o))
OBJ2 = $(addprefix $(OBJDIR), $(SRC2:%.c=%.o))
OBJ3 = $(addprefix $(OBJDIR), $(SRC3:%.c=%.o))

all: 0-hreadelf 1-hreadelf 2-hreadelf

0-hreadelf: header_elf.h $(OBJDIR) $(OBJ1)
	gcc $(CFLAGS) -o $@ $(OBJ1)

1-hreadelf: header_elf.h $(OBJDIR) $(OBJ2)
	gcc $(CFLAGS) -o $@ $(OBJ2)

2-hreadelf: header_elf.h $(OBJDIR) $(OBJ3)
	gcc $(CFLAGS) -o $@ $(OBJ3)

$(OBJDIR)%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	-rm -rf $(OBJDIR)
	-rm -r 0-hreadelf
	-rm -r 1-hreadelf
	-rm -r 2-hreadelf

re: clean 0-hreadelf