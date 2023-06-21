#include "monty.h"

/**
 * is_number - checks if a string is a number
 * @str: string to check
 * Return: 1 if true, 0 if false
 */
int is_number(char *str)
{
	int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}

	return (1);
}

/**
 * free_stack - frees a stack_t list
 * @head: head of list
 */
void free_stack(stack_t *head)
{
	stack_t *temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}

/**
 * free_all - frees all malloc'd memory
 * @head: head of stack_t list
 * @line: line buffer
 * @file: file pointer
 */
void free_all(stack_t *head, char *line, FILE *file)
{
	free_stack(head);
	free(line);
	fclose(file);
}

/**
 * get_op_func - selects the correct function to perform the operation
 * @s: operation to perform
 * Return: pointer to function that performs the operation
 */
void (*get_op_func(char *s))(stack_t **, unsigned int)
{
	instruction_t ops[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{NULL, NULL}
	};
	int i;

	for (i = 0; ops[i].opcode; i++)
	{
		if (strcmp(s, ops[i].opcode) == 0)
			return (ops[i].f);
	}

	return (NULL);
}

/**
 * access - checks if a file exists
 * @filename: name of file
 * @mode: mode to check with
 * Return: 0 if true, -1 if false
 */
int access(const char *filename, int mode)
{
	FILE *file;

	file = fopen(filename, mode);
	if (file)
	{
		fclose(file);
		return (0);
	}
	else
	{
		return (-1);
	}
}

/**
 * check_args - checks if the arguments are valid
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: 0 if valid, 1 if invalid
 */
int check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (1);
	}

	if (access(argv[1], F_OK) == -1)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (1);
	}

	return (0);
}

