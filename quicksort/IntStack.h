// Int stack header file

#ifndef ___IntStack
#define ___IntStack

// Struct for int stack
typedef struct {
	int max;		// Max capacity of stack
	int ptr;		// Stack pointer position
	int *stk;		// Stack pointer
} IntStack;

int Initialize(IntStack *s, int max);
int Push(IntStack *s, int x);
int Pop(IntStack *s, int *x);
int Peek(const IntStack *s, int *x);
void Clear(IntStack *s);
int Capacity(const IntStack *s); // Check max capacity of stack
int Size(const IntStack *s); // Check num of elements in stack
int IsEmpty(const IntStack *s);
int IsFull(const IntStack *s);
int Search(const IntStack *s, int x);
void Print(const IntStack *s); // Print all elements in stack
void Terminate(IntStack *s);

#endif
