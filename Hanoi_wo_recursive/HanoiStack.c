#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hanoiStack.h"

int Initialize(HanoiStack *s, int max)
{
	s->ptr = 0;
	if ((s->stk = calloc(max, sizeof(Hanoi))) == NULL) {
		s->max = 0;
		return -1;
	}
	s->max = max;
	return 0;
}

int Push(HanoiStack *s, Hanoi x)
{
	if (s->ptr >= s->max)
		 return -1;
	s->stk[s->ptr].num = x.num;
	s->stk[s->ptr].from = x.from;
	s->stk[s->ptr].work = x.work;
	s->stk[s->ptr].dest = x.dest;
	s->ptr++;

	return 0;
}

int Pop(HanoiStack *s, Hanoi *x)
{
	if (s->ptr <= 0)
		return -1;
	s->ptr--;
	x->num = s->stk[s->ptr].num;
	x->from = s->stk[s->ptr].from;
	x->work = s->stk[s->ptr].work;
	x->dest = s->stk[s->ptr].dest;
	return 0;
}

int Peek(const HanoiStack *s, Hanoi *x)
{
	if (s->ptr <= 0)
		return -1;
	x->num = s->stk[s->ptr - 1].num;
	x->from = s->stk[s->ptr - 1].from;
	x->work = s->stk[s->ptr - 1].work;
	x->dest = s->stk[s->ptr - 1].dest;
	return 0;
}

void Clear(HanoiStack *s)
{
	s->ptr = 0;
}

int Capacity(const HanoiStack *s)
{
	return s->max;
}

int Size(const HanoiStack *s)
{
	return s->ptr;
}

int IsEmpty(const HanoiStack *s)
{
	return s->ptr <= 0;
}

int IsFull(const HanoiStack *s)
{
	return s->ptr >= s->max;
}

void Print(const HanoiStack *s)
{
	int i;

	for (i = 0; i < s->ptr; i++)
		printf("%d, %c, %c, %c\n", s->stk[i].num, s->stk[i].from, s->stk[i].work, s->stk[i].dest);
	putchar('\n');
}

void Terminate(HanoiStack *s)
{
	if (s->stk != NULL)
		free(s->stk);
	s->max = s->ptr = 0;
}
