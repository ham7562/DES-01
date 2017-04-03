#include <stdio.h>
#include <Windows.h>

InitialPermutation(unsigned long *Data);
Round(DWORD *dWord, DWORD RoundKey1, DWORD RoundKey0);
InverseInitialPermutation(unsigned long *Data);//�� �ʱ����

KeySchedule(char *Key, DWORD *RoundKey);

DE_KeySchedule(char *Key, DWORD *RoundKey);





int main()
{
	unsigned long original[2] = { 12321415,2222222 };
	char key[] = {'a','b'};

	printf("%u,%u\n", original[0], original[1]);
	InitialPermutation(original);//�ʱ� ����
	
	//start Ű ����
	DWORD rKey[32] = {0,};//����Ű
	KeySchedule(key, rKey);
	//end Ű ����

	for (int i = 0; i < 16; i++)
	{
		printf("�������� %lu, %lu, Ű�� %u,%u, ���� Ű�� %u,%u \n", original[0], original[1], rKey[2 * i], rKey[2 * i + 1], 2 * i, 2 * i + 1);
		Round(original, rKey[2 * i], rKey[2 * i + 1]);//���� ����
		printf("test%d %u,%u\n", i + 1, original[0], original[1]);
	}
	printf("test end1 %u,%u\n", original[0], original[1]);

	InverseInitialPermutation(original);// �� �ʱ� ����


	printf("test end2 %u,%u\n", original[0], original[1]);

	DWORD deRKey[32] = { 0, };//����Ű
	KeySchedule(key, deRKey);

	InitialPermutation(original);//�ʱ� ����
	
	for (int i = 15; i >= 0; i--)
	{
		printf("�������� %lu, %lu, Ű�� %u,%u, ���� Ű�� %u,%u \n", original[0], original[1], deRKey[2 * i], deRKey[2 * i + 1], 2 * i, 2 * i + 1);
		Round(original, deRKey[2 * i], deRKey[2 * i + 1]);//���� ����
		printf("test%d %u,%u\n", i + 1, original[0], original[1]);
	}

	InverseInitialPermutation(original);// �� �ʱ� ����


	printf("decoding test end2 %u,%u\n", original[0], original[1]);

	system("pause");
	return 0;
}