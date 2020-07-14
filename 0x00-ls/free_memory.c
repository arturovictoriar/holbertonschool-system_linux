#include "headerls.h"

/**
  * free_memory_messages - free memory heaps for a pointer of message
  * @chain_str: pointer with the string messages
  * Return: nothing
  */
void free_memory_messages(char *chain_str)
{
	free(chain_str);
}
