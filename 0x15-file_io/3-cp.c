#include "main.h"
#include <stdio.h>
#include <stdlib.h>

char *create_buffer(char *file);
void close_file(int fd);
/**
 * create_buffer - allocates 1024 bytes for a buffer
 * @file: the name of the file buffer is storing chars for
 * Return: a pointer to the newly allocated buffer
 */
char *create_buffer(char *file)
{
	char *b;

	b = malloc(sizeof(char) * 1024);
	if (b == NULL)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't write to %s/n", file);
		exit(99);
	}
	return (b);
}
/**
 * close_file - closes file descriptors
 * @fd: the file descriptor to be closed
 */
void close_file(int fd)
{
	int c;

	c = close(fd);
	if (c == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d/n", fd);
		exit(100);
	}
}
/**
 * main - copies the content of a file to another file
 * @argc: the number of arguments supplied to the program
 * @argv: an array of pointers to the arguments
 * Return: 0 on Success
 * Description: if the argument count is in correct exit 97
 * if file_from does'nt con't be read or doesn't exit exit code 98
 * if file_to can't be created or written to exit 99
 * if file_to or file_from can't be closed exit 100
 */
int main(int argc, char *argv[])
{
	int f, t, r, w;
	char *b;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}
	b = create_buffer(argv[2]);
	f = open(argv[1], O_RDONLY);
	r = read(f, b, 1024);
	t = open(argv[2], O_CREATE | O_WRONLY | O_TRUNC, 0664);
	do {
		if (f == -1 || r == -1)
		{
			dprintf(STDERR_FILENO,
					"Error: Can't read from file %s\n", argv[1]);
			free(b);
			exit(98);
		}
		r = read(f, b, 1024);
		t = open(argv[2], O_WRONLY | O_APPEND);
	} while (r > 0);
	free(b);
	close_file(f);
	close_file(t);
	return (0);
}
