#include <stdio.h>
#include <tchar.h>
#include <conio.h>

int main()
{
	int guess =0;
	do {
		printf("\n Enter number \n");
		int a, temp1, array[4], checker = 1;
		char c;
		while (1)
		{
			if (!scanf_s("%d", &a) || getchar() != '\n')
			{
				while ((c = getchar()) != '\n');
			}
			else if (a < 0 || a>9999 ||a<1000);
			else break;
			printf_s("Reenter number: ");
		}



		for (int i = 3, z = 10; i >= 0; z *= 10, i--)
		{
			if (i == 3) {
				array[i] = a % z;
				temp1 = a % z;
				continue;
			}
			array[i] = ((a%z) - temp1) / (z / 10);
			temp1 = a % z;
		}

		for (int i = 0; i < 2; i++) {
			temp1 = array[i];
			array[i] = array[i + 2];
			array[i + 2] = temp1;
		}

		for (int i = 0; i < 4; i++) {
		  if (checker == 1 && array[i]==0) continue;
		  else {
			  printf("%d", array[i]);
			  checker = 0;
		  }
		}
	} while (1==1);
		_getch();
    return 0;
}

