////////////////////////////////////////////////////////
// Definition of member structure
////////////////////////////////////////////////////////
#ifndef ___Member
#define ___Member

#define MEMBER_NO		1
#define MEMBER_NAME		2

#define MAX_MEMBER_NAME		256

// Member data
typedef struct {
	int  no;
	char name[MAX_MEMBER_NAME];
} Member;

int MemberNoCmp(const Member *x, const Member *y);
int MemberNameCmp(const Member *x, const Member *y);
void PrintMember(const Member *x);
void PrintLnMember(const Member *x);
Member ScanMember(const char *message, int sw);

#endif
