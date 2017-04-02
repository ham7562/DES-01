#include <stdio.h>
#include <Windows.h>


unsigned char PC_1[] = {
	57, 49, 41, 33, 25, 17,  9,
	1, 58, 50, 42, 34, 26, 18,
	10,  2, 59, 51, 43, 35, 27,
	19, 11,  3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14,  6, 61, 53, 45, 37, 29,
	21, 13,  5, 28, 20, 12,  4
};
PermutedChoice1(DWORD *Key)
{
	DWORD tmpMask;
	DWORD KeyMask;
	DWORD NewKey[2] = { 0,0 };
	tmpMask = 0x00000001;

	for (int i = 0; i < 28; i++)
	{
		KeyMask = 0x08000000 >> i;

		if ((PC_1[i] <= 32) && (Key[1] & (tmpMask << (32 - PC_1[i])))) {
			NewKey[1] = NewKey[1] | KeyMask;
		}
		else if ((PC_1[i] > 32) &&
			(Key[0] & (tmpMask << (64 - PC_1[i])))) {
			NewKey[1] = NewKey[1] | KeyMask;
		}
	}

	for (int i = 28; i < 56; i++)
	{
		KeyMask = 0x08000000 >> (i - 28);

		if ((PC_1[i] <= 32) && (Key[1] & (tmpMask << (32 - PC_1[i])))) {
			NewKey[0] = NewKey[0] | KeyMask;
		}
		else if ((PC_1[i] > 32) &&
			(Key[0] & (tmpMask << (64 - PC_1[i])))) {
			NewKey[0] = NewKey[0] | KeyMask;
		}
	}

	Key[0] = NewKey[0];
	Key[1] = NewKey[1];
}

unsigned char PC_2[] = {
	14, 17, 11, 24,  1,  5,  3, 28,
	15,  6, 21, 10, 23, 19, 12,  4,
	26,  8, 16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55, 30, 40,
	51, 45, 33, 48, 44, 49, 39, 56,
	34, 53, 46, 42, 50, 36, 29, 32,
};

PermutedChoice2(DWORD *Key)
{
	DWORD tmpMask;
	DWORD KeyMask;
	DWORD NewKey[2] = { 0,0 };

	tmpMask = 0x00000001;
	for (int i = 0; i < 24; i++)
	{
		KeyMask = 0x00800000 >> i;
		if ((PC_2[i] <= 28) && (Key[1] & (tmpMask << (28 - PC_2[i])))) {
			NewKey[1] = NewKey[1] | KeyMask;
		}
		else if ((PC_2[i] > 28) && (Key[0] & (tmpMask << (56 - PC_2[i])))) {
			NewKey[1] = NewKey[1] | KeyMask;
		}
	}
	for (int i = 24; i < 48; i++)
	{
		KeyMask = 0x00800000 >> (i - 24);

		if ((PC_2[i] <= 28) && (Key[1] & (tmpMask << (28 - PC_2[i])))) {
			NewKey[0] = NewKey[0] | KeyMask;
		}
		else if ((PC_2[i] > 28) &&
			(Key[0] & (tmpMask << (56 - PC_2[i])))) {
			NewKey[0] = NewKey[0] | KeyMask;
		}
	}
	Key[0] = NewKey[0];
	Key[1] = NewKey[1];
}

const unsigned char LSHIFT[] = {
	1,1,2,2,
	2,2,2,2,
	1,2,2,2,
	2,2,2,1
};

KeySchedule(char *Key, DWORD *RoundKey)
{
	int SHIFT = 0;
	DWORD dwKey[2] = { 0,0 };
	DWORD tmp0, tmp1;

	for (int i = 0; i < 4; i++)
	{
		SHIFT = ((3 - i) * 8);
		dwKey[1] ^= ((DWORD)Key[i]) << SHIFT;
		dwKey[0] ^= ((DWORD)Key[i + 4]) << SHIFT;
	}
	PermutedChoice1(dwKey);//64비트 -> 56비트후 28비트로 나눠 저장

	for (int i = 0; i < 16; i++)
	{
		//Left Shift
		if (LSHIFT[i] == 1)
		{
			tmp0 = ((dwKey[0] & 0x08000000) >> 27);
			tmp0 |= ((dwKey[0] & 0x07FFFFFF) << 1);
			dwKey[0] = tmp0;
			tmp1 = ((dwKey[1] & 0x08000000) >> 27);
			tmp1 |= ((dwKey[1] & 0x07FFFFFF) << 1);
			dwKey[1] = tmp1;
		}
		else //2bit-shift
		{
			tmp0 = ((dwKey[0] & 0x0c000000) >> 26);
			tmp0 |= ((dwKey[0] & 0x03FFFFFF) << 2);
			dwKey[0] = tmp0;
			tmp1 = ((dwKey[1] & 0x0c000000) >> 26);
			tmp1 |= ((dwKey[1] & 0x03FFFFFF) << 2);
			dwKey[1] = tmp1;
		}
		PermutedChoice2(dwKey);

		RoundKey[2 * i + 1] = dwKey[1];
		RoundKey[2 * i] = dwKey[0];

		dwKey[1] = tmp1;
		dwKey[0] = tmp0;
	}
}

void swap32bit(DWORD *Data)

{
	DWORD temp;
	temp = Data[0];
	Data[0] = Data[1];
	Data[1] = temp;
}