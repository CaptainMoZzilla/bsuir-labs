#include <stdio.h>
#include <tchar.h>
#include <windows.h>


#define DEFAULT_NAME "NoName"
#define CMP_EQ(a, b) ((a) == (b))

int getChoise();
int getMenuItem();
void clearScreen();
void clearBuffer();
void showStatistics();
void startAnimation();
void clearStatistics();
void printInstruction();
char* getInfoAboutUser();
void startTest(int checker);
char* createArray(int size);
void printAnswers(FILE *file);
int readRightAnswer(FILE *file);
FILE* openFile(char File[], char mod[]);
void skipQuestions(FILE *file, int counter);
void printQuestion(char *line, int counter);
void printTempResuts(int number, int number2);
char* addToArray(char* line2, char c, int counter);
char* readLine(FILE *file, enum maintask checkTask);
void saveStatistics(char* username, int rightAnswers);
int calcLevelOfKnowledges(int numAnsw, int numCorrAnsw);
void backupResult(int numAnsw, int numCorrAnsw, char* username);
void loadResultsFromSave(int *numAnsw, int *numCorrAnsw, char* username);

enum maintask{task, answer};

int main()
{
	int checker = 0;
	system("chcp 1251");
	clearScreen();
	//startAnimation();
			
		do {
			clearScreen();
			printInstruction();

			switch (getMenuItem()) {
			case 1:
				startTest(0);
				break;

			case 2:
				startTest(1);
				break;

			case 3:
				showStatistics();
				break;

			case 4:
				clearStatistics();
				break;

			case 5:
				checker = 1;
				break;
			}
		} while (!checker);

	system("pause");
	return 0;
}

void startTest(int checker) {
	system("color f9");
	clearScreen();

	int numAnsw = 1, numCorrAnsw = 0;
	const char Tasks[] = "Tasks.txt";
	char  *username = createArray(9);
	FILE* file = openFile(Tasks, "r");

	if (checker) {
		loadResultsFromSave(&numAnsw, &numCorrAnsw, username);
		skipQuestions(file, numAnsw);
	}
	else {
		username = getInfoAboutUser();
	}

	while (!feof(file)) {
		clearScreen();

		if (numAnsw != 0) {
			printTempResuts(numCorrAnsw, numAnsw);
		}
		printQuestion(readLine(file, task), numAnsw);
		printAnswers(file);

		if (CMP_EQ(getChoise(), readRightAnswer(file)) ? 1 : 0){
			numCorrAnsw++;
		}

		numAnsw++;
		backupResult(numAnsw, numCorrAnsw, username);
	}

	clearScreen();
	printf("%s, твой уровень знаний языка С:[%d%%]\n \n", username, calcLevelOfKnowledges(numAnsw, numCorrAnsw));
	
	backupResult(0, 0, DEFAULT_NAME);
	saveStatistics(username, numCorrAnsw);
	system("pause");
}

char* readLine(FILE *file, enum maintask checkTask) {
	int counter = 1;
	char c, *line = createArray(0), checker;

	if (checkTask == task) checker = '<';
	else checker = '>';
	line[0] = '\0';

	while (!feof(file) && ((c = getc(file)) != checker)) {

		if (c == '\n') continue;	
		else if (c == ' ' || c =='\t' && counter == 1) continue;
		else if (c == '`')c = '\n';

		line = addToArray(line, c, counter);
		counter++;
	}

		return line;
}

char* addToArray(char* line2, char c, int counter) {
	char* line = createArray(counter);

	for (int i = 0, j = 0; i <= counter; i++, j++) {
		if (i == counter - 1) {
			line[i] = c;
			j--;
			continue;
		}
		line[i] = line2[j];
	}
	return line;
}

char* createArray(int size) {
	char *line;
	do {
		line = (char*)malloc(sizeof(char)*(size + 1));

	} while (line == NULL);
	for (int i = 0; i < (size + 1); i++) {
		line[i] = ' ';
	}
	return line;
}

void printQuestion(char *line, int counter) {
	printf("Вопрос #(%d)\n->%s\n\n",counter, line);
}

int readRightAnswer(FILE *file) {
	int number = 0;
	fscanf(file, "%d", &number);

	if (!number) {
		printf("Некорректная информация в файле с заданиями\nИсправьте и перезапустите программу\n");
		system("pause");
		exit(0);
	}
	else return number;
}

void printAnswers(FILE *file) {
	const MAX_AMOUNT = 4, MAX_SIZE = 30;
	char* line;

	for (int i = 0; i < MAX_AMOUNT; i++) {
		printf("%d)%s", i + 1, line = readLine(file, answer));
		if (!(i % 2)) {
			for (int a = 0; a < MAX_SIZE - strlen(line); a++)printf(" ");
		}
		else printf("\n");
	}
	printf("\n");
}

void printTempResuts(int number, int number2) {
	printf("[%d%%] Правильных ответов!\n\n", (number*100)/number2);
}

int getChoise() {
	int number;
	do {
		printf("\nПравильный ответ: ");
		scanf_s("%d",&number);
		clearBuffer();
	} while (number < 1 || number>4);
	return number;
}

char* getInfoAboutUser() {
	const MAX_SIZE = 10;
	char c, *nameOfUser;
	
	printf("Введите ваш никнейм\nОбщее количество символов - 9\nNickname: ");
	nameOfUser = (char*)malloc(sizeof(char)*MAX_SIZE);
	nameOfUser[MAX_SIZE-1] = '\0';

	for (int i = 0; i < MAX_SIZE - 1; i++) {
		c = getchar();
		if (c == '\n') c = ' ';
		nameOfUser[i] = c;
	}
		clearBuffer();

	return nameOfUser;
}

void saveStatistics(char* username, int numCorrAnsw) {
	const MAX_SIZE = 10;
	const char statistic[] = "Statistics.txt";
	FILE *stat = openFile(statistic, "a");

	fprintf(stat, "%s ", username);
	for (int i = 0; i < (MAX_SIZE - strlen(username)); i++) fprintf(stat, " ");
	
	fprintf(stat,"|%d\n", numCorrAnsw);
	fclose(stat);
}

void showStatistics() {
	system("color f2");
	clearScreen();

	char c;
	const char statistic[] = "Statistics.txt";
	FILE *stat = openFile(statistic, "r");

	printf("Последние рез.: \n\nUsername   |+\n");

	while (!feof(stat)) {
		printf("%c", fgetc(stat));
	}

	system("pause");
	fclose(stat);
}

void clearStatistics() {
	const char statistic[] = "Statistics.txt";
	remove(statistic);
}

void backupResult(int numAnsw, int numCorrAnsw, char* username) {
	const char backup[] = "TempResults.txt";
	FILE *file = openFile(backup, "w+");
	fprintf_s(file, "<%s> %d %d", username, numAnsw, numCorrAnsw);
	fclose(file);
}

void loadResultsFromSave(int *numAnsw, int *numCorrAnsw, char* username) {
	char c;
	const MAX_SIZE = 10;
	const char backup[] = "TempResults.txt";

	FILE *file = openFile(backup, "r");
	username[MAX_SIZE - 1] = '\0';

	for (int i = 0; !feof(file) && i < (MAX_SIZE-1); i++) {
		if ((c = getc(file)) == '<') {
			i--;
			continue;
		}
		else if (c == '>') break;
		username[i] = c;
	}
	while ((c = getc(file)) == '>') continue;//Очистка файла от лишних пробелов

	fscanf_s(file, "%d%d", numAnsw, numCorrAnsw);
	fclose(file);
}

void skipQuestions(FILE *file, int counter) {
	char c;
	int checker = 0;
	while (checker < (counter ) * 4) {
		if ((c = getc(file)) == '>') checker++;
	}
}

void startAnimation() {

	char line[][33] = { "| Тест по языку программиров. C|",
	                    "|##############################|",
						"|##     Design. by Andrey    ##|",
						"|######## Good Luck!!! ########|"};

	for (int a = 0; a < 4; a++) {
		for (int b = 0; b < strlen(line[a]); b++) {
			printf("%c", line[a][b]);
			Sleep(35);
		}
		printf("\n");
	}
	printf("\n");
}   

void printInstruction() {
	clearScreen();
	printf("Выберите пункт меню:\n1)Запуск тестирования\n2)Продолжить прошлое тестирование\n3)Вывести статистику\n4)Очистить статистику\n5)Выход");
}

int getMenuItem() {
	int number;
	do {
		printf("\nПункт меню: ");
		scanf_s("%d", &number);
		clearBuffer();
	} while (number < 1 || number>5);
	return number;
}

FILE* openFile(char FileName[], char mod[]) {
	FILE* file = fopen(FileName, mod);

	if (file == NULL) {
		printf("Отсутстует нужный файл\nИсправьте проблему и перезапустите программу\n");
		system("pause");
		exit(0);

	}
	else return file;
}

void clearScreen() {
	system("CLS");
}

void clearBuffer() {
	char c;
	while ((c = getchar()) != '\n');
}

int calcLevelOfKnowledges(int numAnsw, int numCorrAnsw) {
	return ((numCorrAnsw * 100) / numAnsw);
}
