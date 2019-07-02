// Task1.cpp: определяет точку входа для консольного приложения.
//

#include <stdio.h>
#include <tchar.h>

void writeInstruction();
struct number* createList();
long long  getInt(char name[]);
void findNOD(struct number* list);
void deleteList(struct number* list);
void checkNumbers(struct number* list);
void add2List(struct number* list, int num);

struct number{
	long long tempNumber;

	struct number *prev;
	struct number *next;
};


int main()
{
	int checker;
	do {
		system("CLS");
		struct number* list = createList();

		printf("Enter first number(<1 bill.): ");
		list->tempNumber = getInt("X1");

		printf("\nEnter second number(<1 bill.): ");
		add2List(list, getInt("X2"));

		checkNumbers(list);
		findNOD(list);
		deleteList(list);

		writeInstruction();
		checker = getInt("Checker");

	} while (checker != 1);
 	
    return 0;
}


struct number* createList() {
	struct number* list = (struct number*)malloc(sizeof(struct number));
	list->prev = NULL;
	list->next = NULL;
	return list;
}


void add2List(struct number* list, int num) {
	 struct number* temp = (struct number*)malloc(sizeof(struct number));

	 list->next = temp;
	 temp->prev = list;
	 temp->tempNumber = num;
}


long long getInt(char name[]) {
	long long number;
	const MAX_NUMBER = 100000000000;
	char c;
	while (1) {
		printf("\n%s = ", name);
		if (!scanf_s("%lld", &number) || getchar()!='\n') {
			while ((c = getchar()) != '\n');
		}
		else if (number == 0 || number > MAX_NUMBER || number <-MAX_NUMBER) continue;
		else return number;
	}
	return number;
}


void findNOD(struct number* list) {
	while (list->next->tempNumber != 0) {
		add2List(list->next, list->tempNumber % list->next->tempNumber);
		list = list->next;
	}
	printf("\nNOD: %d \n", list->tempNumber);
}


void checkNumbers(struct number* list) {

	long temp;
	if (list->tempNumber < list->next->tempNumber) {
		temp = list->tempNumber;
		list->tempNumber = list->next->tempNumber;
		list->next->tempNumber = temp;
	}
}


void writeInstruction() {
	printf("\nIf you want exit, enter '1', else any number ");
}


void deleteList(struct number* list) {
	struct number* temp;

	while (list) {
		temp = list->prev;
		free(list);
		list = temp;
	}
}
