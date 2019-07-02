#ifndef ___HanoiStack
#define ___HanoiStack

typedef struct {
	int num;		//Disk num
	char from;		//Tower A
	char work;		//Tower B
	char dest;		//Tower C
} Hanoi;

typedef struct {
	int max;		//Stack capacity
	int ptr;		//Stack pointer
	Hanoi *stk;		//Pointer to stack data
} HanoiStack;

int Initialize(HanoiStack *s, int max);
int Push(HanoiStack *s, Hanoi x);
int Pop(HanoiStack *s, Hanoi *x);
int Peek(const HanoiStack *s, Hanoi *x);
void Clear(HanoiStack *s);
int Capacity(const HanoiStack *s);
int Size(const HanoiStack *s);
int IsEmpty(const HanoiStack *s);
int IsFull(const HanoiStack *s);
void Print(const HanoiStack *s);
void Terminate(HanoiStack *s);

#endif
