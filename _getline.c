#include "main.h"

/**
 * _getline - init data
 * @d: data struct input
 * @shell_name: string input
 * Return: void
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t bytesRead = 0;
	size_t position = 0;
	static char buf[READ_BUF_SIZE];
	static size_t bufSize = 0;
	static size_t bufPos = 0;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return -1;
	if (*lineptr == NULL || *n == 0)
	{
		*n = 128;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return -1;
	}

	while (1) {
			if (bufPos >= bufSize) {
				bytesRead = read(fileno(stream), buf, READ_BUF_SIZE);
				if (bytesRead <= 0) {
					if (position == 0) {
						return -1; 
					} else {
						break;
					}
				}
				bufSize = bytesRead;
				bufPos = 0;
			}

			
			if (position >= *n - 1) {
				size_t newSize = *n * 2;
				char *newBuffer = realloc(*lineptr, newSize);
				if (newBuffer == NULL) {
					return -1;
				}
				*lineptr = newBuffer;
				*n = newSize;
			}

			(*lineptr)[position++] = buf[bufPos++];
			if ((*lineptr)[position - 1] == '\n') {
				break;
			}
		}

    (*lineptr)[position] = '\0';

    return (position);
}