.PHONY = hnm hobjdump all clean re

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g
OBJDIR = targets/
SRC5_1 = 0-nm.c utils_elf_1.c convert_endian_1.c convert_endian_2.c convert_endian_3.c utils_elf_section_1.c
SRC5_2 = print_elf_symbol_header_utils1.c utils_elf_symbol_1.c convert_endian_4.c
SRC5 = $(SRC5_1) $(SRC5_2)
SRC6_1 = 1-objdump.c utils_elf_1.c convert_endian_1.c convert_endian_2.c convert_endian_3.c utils_elf_section_1.c
SRC6_2 = print_elf_section_content_utils1.c utils_elf_symbol_1.c convert_endian_4.c utils_elf_section_content_1.c
SRC6 = $(SRC6_1) $(SRC6_2)
OBJ5 = $(addprefix $(OBJDIR), $(SRC5:%.c=%.o))
OBJ6 = $(addprefix $(OBJDIR), $(SRC6:%.c=%.o))

all: hnm hobjdump

hnm: header_elf.h $(OBJDIR) $(OBJ5)
	gcc $(CFLAGS) -o $@ $(OBJ5)

hobjdump: header_elf.h $(OBJDIR) $(OBJ6)
	gcc $(CFLAGS) -o $@ $(OBJ6)

$(OBJDIR)%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	-rm -rf $(OBJDIR)
	-rm -r hnm
	-rm -r hobjdump

re: clean hnm hobjdump
