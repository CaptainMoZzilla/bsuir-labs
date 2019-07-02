#include <stdio.h>
#include <tchar.h>
#include <locale.h>

#define bool int
#define true 1
#define false 0

int getInt();
int* createArray();
void showInsuction();
FILE* openFile(char File[]);
void showGistogram(int *array);
void add2Array(int *array, char c);
void createGistogram(FILE* file, int *array);


int main()
{
	setlocale(LC_ALL, "RU-ru");
	int checker;
	const char File[] = "file.txt";

	do {
		system("CLS");
		FILE *file = openFile(File);
		
		int *array = createArray();
		createGistogram(file, array);
		
		showGistogram(array);
		
		fclose(file);
		
		showInsuction();
		
		checker = getInt();
	} while (checker == 1);


	return 0;
}



FILE* openFile(char File[]) {
 FILE*	file = fopen(File, "r");
 
 if (file == NULL) {
	 printf("\nТакого фалйла не существует");
	 return NULL;
 }
 else return file;
}



int* createArray() {
	int *array = (int*)malloc(sizeof(int)*26);
	for (int i = 0; i < 26; i++)array[i] = 0;
	return array;
}



void createGistogram(FILE* file, int *array) {
	char c = 'a';
	bool number = false;
	int lastIndex = 0, check = 0;

	while (!feof(file)) {
		if (fscanf(file, "%d", &check) == 1) {
			number = true;
			continue;
		}

		fscanf(file, "%c", &c);
		if (c >= 'a' && c <= 'z') {
			add2Array(array, c);
			lastIndex = c-'a';
		}
		number = false;
	}
	if (number == false) array[lastIndex]--;

}


void add2Array(int *array, char c) {
		array[c - 'a'] ++;
}



void showGistogram(int *array) {
	int count = 0;
	double percent;
	for (int i = 0; i < 26; i++)count += array[i];

	for (int i = 0; i < 26; i++) {
		if (array[i] != 0)
			percent =(double) array[i] / count;
		else
			continue;
		int percent2int = percent * 100;

		printf("%c (~%d", 'a'+i,percent2int );

		if (percent2int < 10) printf(" %%):");
		else printf("%%):");

		for (int a = 1; a < percent * 100; a++) {
			printf("0");
		}
		printf("\n");

	}

}

void showInsuction() {
	printf("\nСейчас вы можете изменить файл(!!!)\nДля того, чтобы прождолжить, введите '1': ");

}


int getInt() {
	int number;
	char c;
	while (1) {
		if (!scanf_s("%d", &number) || getchar() != '\n') {
			while ((c = getchar()) != '\n');
		}
		else return number;
		printf("Введите число ещё раз: ");
	}
	return number;
}
