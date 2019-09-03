////////////////////////////////////////////////////////
// Integer set calculation with 32bit vector (header file)
// Created by Hiro Ebisu
////////////////////////////////////////////////////////

#ifndef ___BitSet
#define ___BitSet

typedef unsigned long BitSet;	// Typedef for bitset (ull)

#define BitSetNull		(BitSet)0	// Empty set
#define BitSetBits		32			// Number of valid bits

#define SetOf(no)	((BitSet)1 << (no)) // set{no}

// Check if n is a member of set
int IsMember(BitSet set, int n);

// Add n to set
void Add(BitSet *set, int n);

// Remove n from sets
void Remove(BitSet *set, int n);

// Print size of set
int Size(BitSet set);

// Print all elements of set
void Print(BitSet set);

// Print all elements of set (\n)
void PrintLn(BitSet set);

#endif
