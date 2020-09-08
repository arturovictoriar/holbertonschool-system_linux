.PHONY = 0-hreadelf 1-hreadelf 2-hreadelf all clean re

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g
OBJDIR = targets/
SRC1_1 = 0-hreadelf.c print_elf_header_utils1.c print_elf_header_utils2.c print_elf_header_utils3.c
SRC1_2 = print_elf_header_utils4.c print_elf_header_utils5.c utils_elf_1.c convert_endian_1.c convert_endian_2.c
SRC1 = $(SRC1_1) $(SRC1_2)
SRC2_1 = 1-hreadelf.c utils_elf_1.c convert_endian_1.c convert_endian_2.c convert_endian_3.c utils_elf_section_1.c
SRC2_2 = print_elf_section_header_utils1.c print_elf_section_header_utils2.c
SRC2 = $(SRC2_1) $(SRC2_2)
SRC3_1 = 2-hreadelf.c utils_elf_1.c convert_endian_1.c convert_endian_2.c convert_endian_3.c utils_elf_program_1.c
SRC3_2 = print_elf_program_header_utils1.c print_elf_program_header_utils2.c utils_elf_section_1.c
SRC3 = $(SRC3_1) $(SRC3_2)
SRC4 = 100-hreadelf.c utils_elf_1.c convert_endian_1.c convert_endian_2.c convert_endian_3.c
OBJ1 = $(addprefix $(OBJDIR), $(SRC1:%.c=%.o))
OBJ2 = $(addprefix $(OBJDIR), $(SRC2:%.c=%.o))
OBJ3 = $(addprefix $(OBJDIR), $(SRC3:%.c=%.o))
OBJ4 = $(addprefix $(OBJDIR), $(SRC4:%.c=%.o))

all: 0-hreadelf 1-hreadelf 2-hreadelf 100-hreadelf

0-hreadelf: header_elf.h $(OBJDIR) $(OBJ1)
	gcc $(CFLAGS) -o $@ $(OBJ1)

1-hreadelf: header_elf.h $(OBJDIR) $(OBJ2)
	gcc $(CFLAGS) -o $@ $(OBJ2)

2-hreadelf: header_elf.h $(OBJDIR) $(OBJ3)
	gcc $(CFLAGS) -o $@ $(OBJ3)

100-hreadelf: header_elf.h $(OBJDIR) $(OBJ4)
	gcc $(CFLAGS) -o $@ $(OBJ4)

$(OBJDIR)%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	-rm -rf $(OBJDIR)
	-rm -r 0-hreadelf
	-rm -r 1-hreadelf
	-rm -r 2-hreadelf
	-rm -r 100-hreadelf

re: clean 0-hreadelf 1-hreadelf 2-hreadelf 100-hreadelf
