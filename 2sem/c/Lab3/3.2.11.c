// 3.2.11.cpp: определяет точку входа для консольного приложения.
//

#include <stdio.h>
#include <tchar.h>
#include <locale.h>


int getInt();
int getSize();
void showFinalInfo();
void showStartInfo();
int** createArray(int size);
void showArray(int** array, int size);
void fillArray(int **array, int size);
int checkX_Y(int a, int  b, int x, int y);
int getCoordinatesOfExit(int size, int x, int**array);
void printWay(int **array, int size, int y_get);
void findWay(int ** array, int size, int x, int y);

int main()
{
	setlocale(LC_ALL, "Rus");
	char guess = 'Y';

	do {
		int size = 0, **array, x, y;
		size = getSize();

		array = createArray(size);
		fillArray(array, size);
		showArray(array, size);

		x = size - 1;
		y = getCoordinatesOfExit(size,x, array);


		findWay(array, size, x, y);
		
		showFinalInfo();
		guess = getchar();


	} while (guess == 'y' || guess == 'Y');
	return 0;
}


int getInt() {
	int number;
	char c;
	while (1) {
		if (!scanf_s("%d", &number) || getchar() != '\n') {
			while ((c = getchar()) != '\n');
		}
		else if (number < 0);
		else return number;
		printf("Введите число ещё раз: ");
	}
	return number;
}


int** createArray(int size) {
	int **array = (int**)malloc(size * sizeof(int*));
	for (int i = 0; i < size; i++) array[i] = (int*)malloc(size * sizeof(int));
	return array;
}


void fillArray(int **array, int size) {
	srand(time(NULL));
	for (int a = 0; a < size; a++) {
		for (int b = 0; b < size; b++) {
			if (a == 0 && b == 0) array[a][b] = 0;
			else if (rand() % 3) array[a][b] = 0;
			else array[a][b] = 1;
		}
	}
}

void showArray(int** array, int size) {
	for (int a = 0; a < size; a++) {
		printf("\n");
		for (int b = 0; b < size; b++) {
			printf("%d", array[a][b]);
			if (array[a][b] / 10 < 1 && array[a][b]>=0)printf("  ");
			else printf(" ");
		}
	}
}



void findWay(int ** array, int size, int x, int y) {
	int checker_finish = 0, check_count = 1 , finalSearch = 0, isAvaliable = 0;


	for (int a = 0; a < size; a++) {
		for (int b = 0; b < size; b++) {
			if (array[a][b] == 0)array[a][b] = -1;
			else array[a][b] = -2;
		}
	}

	

	for (int c = 0; c < size && isAvaliable !=size-1; c++) {//Сама проверка
		isAvaliable = 0;

		for (int a = 0; a < size; a++) {//Для строк
			check_count = 0;

			for (int b = 0; b < size; b++) {

				if (a == 0 && b == 0 && finalSearch == 0) {
					if (array[a + 1][b] == -1) {
						array[a + 1][b] = 10 * a + b;
						check_count = 1;
						if (checkX_Y(a + 1, b , x, y) == 1) {
							checker_finish = 1;
							break;
						}
					}

					if (array[a][b + 1] == -1) {//Клетка правее
						array[a][b + 1] = 10 * a + b;
						check_count = 1;
						if (checkX_Y(a, b + 1, x, y) == 1) {
							checker_finish = 1;
							break;
						}
					}
					finalSearch++;
					continue;
				}

				else if (array[a][b] != -1 && array[a][b] != -2) {

					if (a == 0 && b == 0 || (a == size - 1 && b == size - 1)) continue;

					if (a != size - 1) {
						if (array[a + 1][b] == -1) {
							array[a + 1][b] = 10 * a + b;
							check_count = 1;
							if (checkX_Y(a + 1, b, x, y) == 1) {
								checker_finish = 1;
								break;
							}
						}
					}
					if (a != 0) {
						if (array[a - 1][b] == -1) {
							array[a - 1][b] = 10 * a + b;
							check_count = 1;
							if (checkX_Y(a - 1, b, x, y) == 1) {
								checker_finish = 1;
								break;
							}
						}
					}

					if (b != size - 1) {
						if (array[a][b + 1] == -1) {
							array[a][b + 1] = 10 * a + b;
							check_count = 1;
							if (checkX_Y(a, b + 1, x, y) == 1) {
								checker_finish = 1;
								break;
							}
						}
					}
					if (b != 0) {
						if (array[a][b - 1] == -1) {
							array[a][b - 1] = 10 * a + b;
							check_count = 1;
							if (checkX_Y(a, b - 1, x, y) == 1) {
								checker_finish = 1;
								break;
							}
						}
					}
				}

	    	}

			if (checker_finish == 1)break;
			if (check_count == 0) isAvaliable++;
		}

		if (checker_finish == 1)break;
	}

	if (checker_finish == 1) {
		printf("\nПуть есть!");
		printWay(array, size, y);
	}
	else printf("\nПути нет! \n");
}

int checkX_Y(int a, int  b, int x, int y) {
	if (a == y && b == x) return 1;
	else return 0;
}

int getSize() {
	int number, counter=0;
	do {
		system("CLS");
		printf("Введите разменость массива(<=11 && >5): ");
		number = getInt();
		
	} while (number <= 5 || number >11);
	return number;
}


void printWay(int **array, int size, int y_get) {
    int a, b, x = size - 1, y = y_get;
	do {
		a = y;
		b = x;
		
		if (x == size - 1 && size == 11 && array[a][b]%10==0) {
			y = (array[a][b] - 10) / 10;
			array[a][b] = -3;
		}
		else {
			x = array[a][b] % 10;
			y = array[a][b] / 10;
			array[a][b] = -3;
		}
	} while (a != 0 || b != 0);


	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (array[i][j] != -3)array[i][j] = 8;
			else array[i][j] = 0;
		}
	}
	printf("\n \n");
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (array[i][j] != 0) printf("0  ");
			else printf("*  ");
		}
		printf("\n");
	}
}

int getCoordinatesOfExit(int size,int x ,int**array) {
	int y;
	do {
		printf("\nY(Выход не может быть стеной) = ");
		y = getInt();
	} while (y >= size || array[y][x] == 1);
	return y;
}

void showStartInfo() {
	printf("\n \nВведите строку, на которой находится выход(Y - по вертикали, за Х автоматически берется последний столбец)");
}

void showFinalInfo() {
	printf("\n \nЖелаете продолжить? \nДа(Y/y) или \nНет(Любая другая буква)\n");
}
