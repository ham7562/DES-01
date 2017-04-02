#include <stdio.h>
#include <Windows.h>

int main()
{
	unsigned long on1 = 12321415, i = 0;

	printf("%d\n", on1);
	InitialPermutation(&on1);//초기 순열




	InverseInitialPermutation(&on1);// 역 초기 순열
	printf("test1 %d\n", on1);



	return 0;
}