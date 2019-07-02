// ConsoleApplication2.cpp: определяет точку входа для консольного приложения.
//

#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <tchar.h>


int getInt();
void getInfo();
void getContact();
int getUserGuess();
void rateCalculate();
void showMenuItems();
void getInfo_byIndex(int index);
int chooseMenuItem(int user_guess);


int main()
{
	int checker ;
	setlocale(LC_ALL, "Rus");
	do {
		system("CLS");
		showMenuItems();
		checker = chooseMenuItem(getUserGuess());

	} while (checker != 4);
    return 0;
}



int getInt() {
	int number;
	char c;
	while (1) {
		if (!scanf_s("%d", &number) || getchar() != '\n') {
			while ((c = getchar()) != '\n');
		}
		else if (number < 0 );
		else return number;
		printf("Введите число ещё раз: ");
	}
}

void getInfo() {
   	printf("\n \n1.Безлимитище \nМинуты внутри сети: Unlimited \nМинуты другим операторам: 0\nМинуты на городскую линию: 0\nKоличество SMS: 0\nМобильный Интернет: Unlimited ");
	printf("\n \n2.4G лайт \nМинуты внутри сети: 250\nМинуты другим операторам: 0\nМинуты на городскую линию: 0\nKоличество SMS: 0 \nМобильный Интернет: 500МБ.");
	printf("\n \n3.4G мини \nМинуты внутри сети: 500\nМинуты другим операторам: 0 \nМинуты на городскую линию: 100\nKоличество SMS: 0 \nМобильный Интернет: 1.5ГБ.");
	printf("\n \n4.4G мега \nМинуты внутри сети: 2.000\nМинуты другим операторам: 0 \nМинуты на городскую линию: 0\nKоличество SMS: 0 \nМобильный Интернет: 6ГБ.");
	printf("\n \n5.ULTRA \nМинуты внутри сети: 1.000\nМинуты другим операторам: 1.000 \nМинуты на городскую линию: 0\nKоличество SMS: 1.000 \nМобильный Интернет: 10ГБ.");
	printf("\n \n6.Легко сказать \nМинуты внутри сети: 90\nМинуты другим операторам: 90\nМинуты на городскую линию: 0\nKоличество SMS: 0\nМобильный Интернет: 0МБ.");
	printf("\n \nНажмите любую клавишу, чтобы закрыть информацию о тарифах");
	_getch();
}

void getContact() { 
printf("8 017 237-98-98 круглосуточно");	
printf("\n \nНажмите любую клавишу, чтобы закрыть информацию о контактах");
_getch();
}

void rateCalculate() {
	int mtc_min, other_min, city_min, count_sms, count_inter, count_plus[6], index;
	printf("\nВведите количество минут внутри сети: ");
	mtc_min = getInt();
	printf("\nВведите количество в другие сети: ");
	other_min = getInt();
	printf("\nВведите количество на городскую линию: ");
	city_min = getInt();
	printf("\nВведите количество SMS: ");
	count_sms = getInt();
	printf("\nВведите количество МБ интернет трафика: ");
	count_inter = getInt();
	
	for (int i = 0; i < 6; i++)count_plus[i] = 0;
	
	if (mtc_min <= 90) count_plus[5]++;
	else if (mtc_min <= 250)  count_plus[1]++;
	else if (mtc_min <= 500) count_plus[2]++;
	else if (mtc_min <= 1000) count_plus[4]++;
	else if (mtc_min <= 2000) count_plus[3]++;
	else count_plus[0]++;

	if(other_min==0)
		{
			count_plus[0]++;
			count_plus[1]++;
			count_plus[2]++;
			count_plus[3]++;
		}
	else if (other_min <= 90)count_plus[5]++;
	else count_plus[4]++;


    if (city_min == 0) {
		count_plus[0]++;
		count_plus[1]++;
		count_plus[4]++;
		count_plus[3]++;
		count_plus[5]++;
	}
    else count_plus[2]++;

	if (count_sms == 0) {
		count_plus[0]++;
		count_plus[1]++;
		count_plus[2]++;
		count_plus[3]++;
		count_plus[5]++;
	}
	else count_plus[4]++;

	if(count_inter==0) count_plus[5]++;
	else if(count_inter<=500) count_plus[1]++;
	else if (count_inter <= 1500) count_plus[2]++;
	else if (count_inter <= 6000) count_plus[3]++;
	else if (count_inter <= 10000) count_plus[4]++;
	else count_plus[0]++;

	for (int i = 0, max_count; i < 6; i++) {
		if (i == 0) {
			index = i;
			max_count = count_plus[i];
			continue;
		}

		if (count_plus[i] > max_count) {
			index = i;
			max_count = count_plus[i];
		}

	}
	getInfo_byIndex(index);
}

void getInfo_byIndex(int index) {
	switch (index)
	{
	case 0:
		printf("\n \nБезлимитище \nМинуты внутри сети: Unlimited \nМинуты другим операторам: 0     \nМинуты на городскую линию: 0   \nKоличество SMS: 0      \nМобильный Интернет: Unlimited ");
		break;
	case 1:
		printf("\n \n4G лайт \nМинуты внутри сети: 250           \nМинуты другим операторам: 0     \nМинуты на городскую линию: 0   \nKоличество SMS: 0      \nМобильный Интернет: 500МБ.");
		break;
	case 2:
		printf("\n \n4G мини \nМинуты внутри сети: 500           \nМинуты другим операторам: 0     \nМинуты на городскую линию: 100 \nKоличество SMS: 0      \nМобильный Интернет: 1.5ГБ.");
		break;
	case 3:
		printf("\n \n4G мега \nМинуты внутри сети: 2.000         \nМинуты другим операторам: 0     \nМинуты на городскую линию: 0   \nKоличество SMS: 0      \nМобильный Интернет: 6ГБ.");
		break;
	case 4:
		printf("\n \nULTRA \nМинуты внутри сети: 1.000           \nМинуты другим операторам: 1.000 \nМинуты на городскую линию: 0   \nKоличество SMS: 1.000  \nМобильный Интернет: 10ГБ.");
		break;
	case 5:
		printf("\n \nЛегко сказать \nМинуты внутри сети: 90                      \nМинуты другим операторам: 90    \nМинуты на городскую линию: 0   \nKоличество SMS: 0      \nМобильный Интернет: 0МБ.");
		break;
	default:
		break;
	}
	printf("\n \nНажмите любую клавишу, чтобы закрыть информацию о тарифах");
	_getch();
}

int getUserGuess() {
	int checker = 0, user_guess;

	do {
		if (checker != 0) printf("\nВведите число ещё раз: ");
		if (checker == 0) checker++;
		user_guess = getInt();
	} while (user_guess < 0 || user_guess>4);

	return user_guess;
}

void showMenuItems() {
	printf("Выберите нуный пункт меню \n1)Калькулятор тарифов \n2)Информация о тарифах\n3)Обратная сявзь\n4)Выйти из программы\n");
}


int chooseMenuItem(int user_guess) {

	switch (user_guess)
	{
	case 1:
		rateCalculate();
		break;
	case 2:
		getInfo();
		break;
	case 3:
		getContact();
		break;
	default:
		break;
	}
	return user_guess;
}
