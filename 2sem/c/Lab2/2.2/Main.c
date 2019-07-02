// ConsoleApplication4.cpp: определяет точку входа для консольного приложения.
//


#include <stdio.h>
#include <tchar.h>
#include <locale.h>
#include <conio.h>
#include <math.h>

double getDouble();
void showFinalInfo();
void showResults(long double x, long double y0);
long double calcSqrt(long double x, long double eps);

int main()
{ 
	char checker = 'y';
    long double x, eps;
	setlocale(LC_ALL, "Rus");
	do {
     	system("CLS");

		//printf("Введите x = ");
		x = getDouble();
		
		printf("\nВведите точность(вводится с запятой, например 0,123) = ");
		eps = getDouble();

		showResults(x, calcSqrt(x, eps));
		
		showFinalInfo();
		checker = getchar();

	} while (checker == 'y');

	return 0;
}



double getDouble()
{
	double number;
	char c;
	while (1) {
		printf("Введите число : ");
		if (!scanf_s("%lf", &number) ) {
			while ((c = getchar()) != '\n');
		}
		else if (number <= 0)
			continue;

		else 
			return number;
	}
	return number;
}



long double calcSqrt(long double x, long double eps) {
	long double y0, y2;
	int counter = 0;

	y0 = x;
	do {
		y2 = y0;
		y0 = 0.5*(y0 + (x / y0));
		counter++;
	} while (y2 - y0 > eps);

	printf("\nПотребовалось %d итераций", counter);
	return y0;
}

void showResults(long double x, long double y0) {
	printf("\nКорень из x:\nСтандартной функцией = %g \nПо формуле = %g \n", sqrt(x), y0);

}

void showFinalInfo() {
	printf("\nЧтобы продолжить - введите 'y':\n");
}
