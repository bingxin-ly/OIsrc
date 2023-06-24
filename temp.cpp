#include <stdio.h>

#define max 999

int minx(int a[])
{

	int i, j, min = 999;

	for (i = 0; i < 6; i++)
	{

		if (a[i] != 0 && a[i] < min)
		{

			min = a[i];

			j = i;
		}
	}

	return j;
}

int main()
{

	int i, j, k = 0;

	int a[6][6] = {{0, 6, 6, 4, max, max},

				   {6, 0, 1, 2, max, max},

				   {6, 1, 0, 2, 5, 3},

				   {4, 2, 2, 0, max, 4},

				   {max, max, 5, max, 0, 4},

				   {max, max, 3, 4, 4, 0}};

	int end[6] = {0, 6, 6, 4, max, max};

	int start[6] = {0, 0, 0, 0, 0, 0};

	printf("%c", k + 65);

	for (i = 0; i < 5; i++)

	{

		k = minx(end);

		printf("-%c", k + 65);

		end[k] = 0;

		for (j = 0; j < 6; j++)

		{

			if (a[k][j] < end[j])

			{

				end[j] = a[k][j];

				start[j] = k;
			}
		}
	}

	return 0;
}
