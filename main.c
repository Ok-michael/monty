#include "monty.h"

bus_t bus = {NULL, NULL, NULL, 0};

/**
 * main - this is the entry point to the monty code interpreter
 * @argc: Argument count
 * @argv: the second element of the commandline arguments which
 * is the monty file location.
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	ssize_t lineRead = 1;
	stack_t *stack = NULL;
	unsigned int cnt = 0;
	char *content;
	FILE *file;
	size_t size = 0;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	bus.file = file;
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while (lineRead > 0)
	{
		content = NULL;
		lineRead = getline(&content, &size, file);
		bus.content = content;
		cnt++;
		if (lineRead > 0)
			execute(content, &stack, cnt, file);
		free(content);
	}
	free_stack(stack);
	fclose(file);
	return (0);
}
