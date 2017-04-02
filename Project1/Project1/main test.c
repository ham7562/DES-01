#include <stdio.h>
#include <Windows.h>

InitialPermutation(unsigned long *Data);
Round(DWORD *dWord, DWORD RoundKey1, DWORD RoundKey0);
InverseInitialPermutation(unsigned long *Data);//�� �ʱ����

KeySchedule(char *Key, DWORD *RoundKey);


//-----------------------------------------------------------------------



//---------------------------------------------




int main()
{
	unsigned long original[2] = { 12321415,2222222 }, i = 0;
	char key[] = {'a','b'};

	printf("%u,%u\n", original[0], original[1]);
	InitialPermutation(original);//�ʱ� ����
	
	//start Ű ����
	DWORD rKey[32] = {0,};//����Ű
	KeySchedule(key, rKey);
	//end Ű ����

	for (int i = 0; i < 16; i++)
	{
		Round(original, rKey[2*i], rKey[2*i+1]);
		printf("test%d %u,%u\n", i + 1, original[0], original[1]);
	}
	printf("test end1 %u,%u\n", original[0], original[1]);

	InverseInitialPermutation(original);// �� �ʱ� ����


	printf("test end2 %u,%u\n", original[0], original[1]);

	InitialPermutation(original);//�ʱ� ����

	for (int i = 15; i >= 0; i--)
	{
		Round(original, rKey[2 * i], rKey[2 * i + 1]);
		printf("test%d %u,%u\n", i + 1, original[0], original[1]);
	}

	InverseInitialPermutation(original);// �� �ʱ� ����


	printf("decoding test end2 %u,%u\n", original[0], original[1]);

	system("pause");
	return 0;
}