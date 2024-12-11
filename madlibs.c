#include <stdio.h>
#include <stdbool.h>
#define MAX_LINES 100
#define MAX_LENGTH 100

int stringLength(const char *str) {
	int length = 0;
	while (str[length] != '\0') {
		length++;
	}
	return length;
}

void stringCopy(char *dest, const char *src) {
	int i = 0;
	while (src[i] != '\0') {
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void removeNewline(char *str) {
	int length = stringLength(str);
	if (length > 0 && str[length - 1] == '\n') {
		str[length - 1] = '\0';
	}
}

void makefile(){
	FILE * filename = fopen("filename.txt", "w");
	
	fprintf(filename, "Bob went for a walk in the park. As he walked down the/nN/nhe/nV/n the view. Soon he reached the/nN/n in the park, where he just stood for a moment to enjoy the/nA/n view. After some time Bob finally decided it was time to head back to/nN/n for the rest of the day.");
	
	fclose(filename);
	}
void loadFile(const char *filename, char lines[][MAX_LENGTH], int *lineCount) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		printf("Error: Cannot open file %s\n", filename);
		return;
	}
	*lineCount = 0;
	while (fgets(lines[*lineCount], MAX_LENGTH, file)) {
		removeNewline(lines[*lineCount]);
		(*lineCount)++;
	}
	fclose(file);
}

bool isPlaceholder(const char *line) {
	return stringLength(line) == 1 && (line[0] == 'A' || line[0] == 'N' || line[0] == 'V');
}

void getUserInputs(char placeholders[], char userInputs[][MAX_LENGTH], int count) {
	for (int i = 0; i < count; i++) {
		if (placeholders[i] == 'A') {
			printf("Enter an adjective: ");
		} else if (placeholders[i] == 'N') {
			printf("Enter a noun: ");
		} else if (placeholders[i] == 'V') {
			printf("Enter a verb: ");
		}
		fgets(userInputs[i], MAX_LENGTH, stdin);
		removeNewline(userInputs[i]);
	}
}

void replacePlaceholders(char lines[][MAX_LENGTH], char placeholders[], char userInputs[][MAX_LENGTH], int lineCount) {
	int inputIndex = 0;
	for (int i = 0; i < lineCount; i++) {
		if (isPlaceholder(lines[i])) {
			stringCopy(lines[i], userInputs[inputIndex++]);
		}
	}
}

void printMadlib(char lines[][MAX_LENGTH], int lineCount) {
	for (int i = 0; i < lineCount; i++) {
		printf("%s ", lines[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <filename>\n", argv[0]);
		return 1;
	}
		
	char lines[MAX_LINES][MAX_LENGTH];
	char placeholders[MAX_LINES];
	char userInputs[MAX_LINES][MAX_LENGTH];
	int lineCount = 0, placeholderCount = 0;
		
	loadFile(argv[1], lines, &lineCount);
		
	for (int i = 0; i < lineCount; i++) {
		if (isPlaceholder(lines[i])) {
			placeholders[placeholderCount++] = lines[i][0];
		}
	}
	
	getUserInputs(placeholders, userInputs, placeholderCount);
	replacePlaceholders(lines, placeholders, userInputs, lineCount);
	printMadlib(lines, lineCount);
	return 0;
}
