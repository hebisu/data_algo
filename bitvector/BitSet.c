////////////////////////////////////////////////////////
// Integer set calculation with 32bit vector (source file)
// Created by Hiro Ebisu
////////////////////////////////////////////////////////
#include <stdio.h>
#include "BitSet.h"

// Check if n is a member of s
int IsMember(BitSet set, int n)
{
	return set & SetOf(n);
}

// Add n to s
void Add(BitSet *set, int n)
{
	*set |= SetOf(n);
}

// Remove n from s
void Remove(BitSet *set, int n)
{
	*set &= ~SetOf(n);
}

// Print size of s
int Size(BitSet set)
{
	int n = 0;

	for (; set != BitSetNull; n++)
		set &= set - 1;
	return n;
}

// Print all elements of s
void Print(BitSet set)
{
	int i;

	printf("{ ");
	for (i = 0; i < BitSetBits; i++)
		if (IsMember(set, i))
			printf("%d ", i);
	printf("}");
}

// Print all elements of s (\n)
void PrintLn(BitSet set)
{
	Print(set);
	putchar('\n');
}
