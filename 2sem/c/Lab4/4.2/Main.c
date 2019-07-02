// Task1.cpp: определяет точку входа для консольного приложения.
//

#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <locale.h>

char* readLine();
void writeInstruction();
int getSize(char *line);
char* createArray(int size);
void showModLine(char *line, int size);
char* add2Array(char* line2, char c, int counter);

int main()
{
	char *line;
	do {
		writeInstruction();
		line = readLine();
		showModLine(line, getSize(line));

	} while (line[0] != '0');

	system("pause");
}


char* readLine() {
	int counter = 1;
	char c, *line = createArray(0);
	line[0] = '\0';

	while ((c = getchar()) != '\n') {
		line = add2Array(line, c, counter);
		counter++;
		
	}


	return line;
}

char* add2Array(char* line2, char c, int counter) {
	char* line = createArray(counter);

	for (int i = 0, j = 0; i <= counter; i++, j++) {
		if (i == counter-1) {
			line[i] = c;
			j--;
			continue;
		}
		line[i] = line2[j];
	}
   //printf("\nStroka: %s ", line);Проверка считывания
	return line;
}

void writeInstruction() {
	printf("\n \nEnter line\nIf you want to stop the program - start your line with '0'\nLine: ");
}



int getSize(char *line) {
	int size = 0, i =  0;
	while (line[i] != '\0') {
		size++;
		i++;
	}
	return size + 1;//Т.к. есть ещё \0

}

void showModLine(char *line, int size) {
	
	printf("\nYour mod. line:\n");
	if (size == 2) {
		for (int i = 0; i < 39; i++)
		{
			printf(" ");
		}
	}
	else {
		for (int i = 0; i < 41 - size/2; i++) {
			printf(" ");
		}
		}
	printf("%s \n \n", line);
	
}

char* createArray(int size) {
	char *line;
	do {
		line = (char*)malloc(sizeof(char)*(size + 1));

	} while (line == NULL);
		return line;
}
