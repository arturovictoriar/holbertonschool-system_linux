#include "multithreading.h"

/**
* primeFactors - built the list of prime factors
* @n: number to get the prime factors
* @l: the list of prime factors
* Return: Nothing
*/
void primeFactors(unsigned long n, list_t *l)
{
	unsigned long i = 0, *prime = NULL;

	while (n % 2 == 0)
	{
		prime = calloc(1, sizeof(unsigned long));
		*prime = 2;
		list_add(l, prime);
		n /= 2;
	}

	i = 3;
	while (i * i <= n)
	{
		while (n % i == 0)
		{
			prime = calloc(1, sizeof(unsigned long));
			*prime = i;
			list_add(l, prime);
			n /= i;
		}
		i += 2;
	}

	if (n > 2)
	{
		prime = calloc(1, sizeof(unsigned long));
		*prime = n;
		list_add(l, prime);
	}
}

/**
* prime_factors - get the prime factor of a given number
* @s: string representation of a number
* Return: a list of prime factor of a given number
*/
list_t *prime_factors(char const *s)
{
	unsigned long n = 0;
	int i = 0;
	list_t *list_prime = NULL;

	list_prime = calloc(1, sizeof(list_t));
	if (!list_prime)
		return (NULL);

	list_init(list_prime);

	i = 0;
	n = 0;
	while (s[i])
	{
		n = (n * 10) + (s[i] - '0');
		i++;
	}

	primeFactors(n, list_prime);

	return (list_prime);
}
