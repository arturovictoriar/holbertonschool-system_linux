#include "header_elf.h"

/**
* little_big_uint32_t - Convert big to little endian 32 bit
* @x: 32 variable
* Return: x converted
*/
uint32_t little_big_uint32_t(uint32_t x)
{
	return (((x & 0xff) << 24) |
			((x & 0xff00) << 8) |
			((x & 0xff0000) >> 8) |
			((x & 0xff000000) >> 24));
}

/**
* little_big_Elf64_Addr - Convert big to little endian 64 bit
* @x: 64 variable
* Return: x converted
*/
Elf64_Addr little_big_Elf64_Addr(Elf64_Addr x)
{
	return (((x & 0xff) << 56) |
			((x & 0xff00) << 40) |
			((x & 0xff0000) << 24) |
			((x & 0xff000000) << 8) |
			((x & 0xff00000000) >> 8) |
			((x & 0xff0000000000) >> 24) |
			((x & 0xff000000000000) >> 40) |
			((x & 0xff00000000000000) >> 56));
}

/**
* little_big_Elf64_Off - Convert big to little endian 64 bit
* @x: 64 variable
* Return: x converted
*/
Elf64_Off little_big_Elf64_Off(Elf64_Off x)
{
	return (((x & 0xff) << 56) |
			((x & 0xff00) << 40) |
			((x & 0xff0000) << 24) |
			((x & 0xff000000) << 8) |
			((x & 0xff00000000) >> 8) |
			((x & 0xff0000000000) >> 24) |
			((x & 0xff000000000000) >> 40) |
			((x & 0xff00000000000000) >> 56));
}

/**
* little_big_Elf32_Addr - Convert big to little endian 32 bit
* @x: 32 variable
* Return: x converted
*/
Elf32_Addr little_big_Elf32_Addr(Elf32_Addr x)
{
	return (((x & 0xff) << 24) |
			((x & 0xff00) << 8) |
			((x & 0xff0000) >> 8) |
			((x & 0xff000000) >> 24));
}

/**
* little_big_Elf32_Off - Convert big to little endian 32 bit
* @x: 32 variable
* Return: x converted
*/
Elf32_Off little_big_Elf32_Off(Elf32_Off x)
{
	return (((x & 0xff) << 24) |
			((x & 0xff00) << 8) |
			((x & 0xff0000) >> 8) |
			((x & 0xff000000) >> 24));
}
