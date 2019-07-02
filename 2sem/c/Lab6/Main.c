// Task1.cpp: определяет точку входа для консольного приложения.
//

#include <stdio.h>
#include <tchar.h>
#include <string.h>

int getInt();
int isLetter(char a);
void printInstruction();
char* readLine(FILE *file);
char* createArray(int size);
FILE* openFile(char File[]);
void clearTree(struct Tree* x);
struct Tree* createTree(FILE* file);
struct Tree* createBranch(char *line);
void printNecessaryWords(struct Tree *x);
int compareLines(char* line1, char* line2);
void addToTree(struct Tree *tree, char* line);
char* add2Array(char* line2, char c, int counter);


struct Tree
{
	char *line;

	struct Tree *left;
	struct Tree *right;
};

int main()
{
	int checker = 0;
	FILE *file;	
	struct Tree* head;
	const char name[] = "Text.txt";

	do {
		system("CLS");
		file = openFile(name);

	    head = createTree(file);

		if (!head)
		{
			printf("There's no such words\n");
		}

		else printNecessaryWords(head);

		fclose(file);
		clearTree(head);
		printInstruction();
		checker = getInt();
	} while (checker == 1);

    return 0;
}


FILE* openFile(char File[]) {
	FILE* file = fopen(File, "r");

	if (file == NULL) {
		printf("\nThere is no such file\n");
		system("pause");
		exit(0);
	}
	else return file;
}


char* readLine(FILE *file) {
	int counter = 1;
	char c, *line = createArray(0);
	
	line[0] = '\0';

	while(!feof(file)) {

		fscanf(file, "%c", &c);
		if (c == ' ' ) break;
		line = add2Array(line, c, counter);
		counter++;
	}

	if(counter!=1) return line;
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
	return line;
}


char* createArray(int size) {
	char *line;
	do {
		line = (char*)malloc(sizeof(char)*(size + 1));

	} while (line == NULL);
	return line;
}


struct Tree* createTree(FILE* file) {
   	struct Tree *head = NULL, *temp;
	int checker = 0;
	char *line;

	while (!feof(file)) {
		temp = head;
		line = readLine(file);

		if (head == NULL) {
			head = createBranch(line);
			checker = 1;
			continue;
		}
		
		else {
		
			addToTree(head, line);
		}

	}

	return head;
}

void addToTree(struct Tree *temp, char* line) {

		switch (compareLines(temp->line, line))
		{

		case 0:
			if (!temp->left) {
				temp->left = createBranch(line);
				break;
			}
			else
				addToTree(temp->left, line);

		case 1:
			if (!temp->right) {
				temp->right = createBranch(line);
				break;
			}
	
			else
				addToTree(temp->right, line);

		default:
			break;
	
		}
}


struct Tree* createBranch(char *line) {
	for (int i = 0; i < strlen(line); i++) 
		if (!isLetter(line[i])) 
			return NULL;

	struct Tree* temp = (struct Tree*)malloc(sizeof(struct Tree));
	
	temp->left = NULL;
	temp->right = NULL;
	temp->line = line;

	return temp;
}


int compareLines(char* line1, char* line2) {
	char temp_a, temp_b;

	for (int i = 0; i <= strlen(line1) && i <= strlen(line2); i++) {

		if (!isLetter(line2[i])) return 2;

		if (isupper(line1[i])) temp_a = line1[i];
		else temp_a = toupper(line1[i]);

		if (isupper(line2[i])) temp_b = line2[i];
		else temp_b = toupper(line2[i]);

		if (temp_a > temp_b) return 1;
		else if (temp_a < temp_b) return 0;//1 - меньше
	}

	if (strlen(line1) == strlen(line2)) {
		return 2;//0 - больше
	}
	else {
		return 0;//2 - пропустить
	}
}



int isLetter(char a) {
	return ( a >= 'a' && a <= 'z') ? 1 : ( a >= 'A' && a <= 'Z') ? 1 : 0;
}

void printNecessaryWords(struct Tree *x) {
	char temp_a, temp_b;
	if (x != NULL ) {	
		printNecessaryWords(x->right);

		temp_a = x->line[0];
		temp_b = x->line[strlen(x->line) - 1];
		if (!isupper(temp_a)) temp_a = toupper(temp_a);
		if (!isupper(temp_b)) temp_b = toupper(temp_b);
		
		if (temp_a == temp_b) {
			printf("->%s\n",x->line);
		}
		printNecessaryWords(x->left);
	}
}

void printInstruction() {
	printf("\nNow you can correct file\nIf you want continue, enter '1'\nYour's choice = ");
}

int getInt() {
	int number;
	scanf_s("%d", &number);
	return number;
}

void clearTree(struct Tree* x) {
	if (x != NULL) {

		clearTree(x->left);
		clearTree(x->right);
		free(x->line);
		free(x);
	}
}
