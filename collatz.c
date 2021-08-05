#include <gmp.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Apply the ruleset of the Collatz Conjecture
void next_step(mpz_t hailstone)
{
	mpz_t mod_of_stone;
	mpz_mod_ui(mod_of_stone, hailstone, 2uL);

	mpz_t hailstone_cpy;
	mpz_mul_ui(hailstone_cpy, hailstone, 1uL);

	if(!mpz_cmp_si(mod_of_stone, 1L))
	{
		mpz_mul_ui(hailstone, hailstone_cpy, 3uL);
		mpz_mul_ui(hailstone_cpy, hailstone, 1uL);
		mpz_add_ui(hailstone, hailstone_cpy, 1uL);
	}
	else
	{
		mpz_divexact_ui(hailstone, hailstone_cpy, 2uL);
	}
}

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr, "Usage: %s [positive integer]\n", argv[0]);
		return -1;
	}

	int i, len;
	char *input;
	input = argv[1];
	len = (int)strlen(input);

	for(i = 0; i < len; ++i) if(!isdigit(input[i]))
	{
		fprintf(stderr, "Usage: %s [positive integer]\n", argv[0]);
		return -1;
	}

	mpz_t stone;
	gmp_sscanf(argv[1], "%Zd", stone);

	long long int steps;
	steps = 0LL;

	while(mpz_cmp_si(stone, 1L))
	{
		++steps;
		next_step(stone);
	}

	printf("Steps: %lld\n", steps);
	return 0;
}
