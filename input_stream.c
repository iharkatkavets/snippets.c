#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <strings.h>


char* readline() {
	size_t alloc_length = 1024;
	size_t data_length = 0;
	char *data = (char *)malloc(alloc_length);
	while (true) {
		char *cursor = data + data_length;
		char *line = fgets(cursor, alloc_length-data_length, stdin);
		if (line == NULL && !data_length) { 
			free(data);
			data = NULL;
			break;	
		}

		data_length += strlen(line);
		if (data_length < alloc_length) { break; }

		alloc_length <<= 1;
		data = (char *)realloc(data, alloc_length); 
		if (!data) { break; }
	}

	if (data == NULL) {
		return data;
	}

	if (data[data_length] != '\0') {
		data[++data_length] = '\0';
	}

	if (data_length < alloc_length) {
		data = (char *)realloc(data, data_length);
	}

	return data;	
}

char* read_stdin() {
	size_t alloc_length = 1024;
	size_t data_length = 0;
	char *data = (char *)malloc(alloc_length);
	while (true) {
		char *cursor = data + data_length;
		ssize_t read_length =  read(STDIN_FILENO, cursor, alloc_length-data_length);
		if (!read_length && !data_length) {
			free(data);
			data = NULL;
			break;
		}

		printf("\nread_length=[%lu] strlen=[%lu]", read_length, strlen(cursor));
		if (cursor[read_length-1] == '\n') {
			printf("\n newline");
		}
		if (cursor[read_length] == '\0') {
			printf("\n end");
		}

		data_length += read_length;
		if (data_length < alloc_length) { break; }

		alloc_length <<= 1;
		data = (char *)realloc(data, alloc_length); 
		if (!data) { break; }
	}

	if (data == NULL) {
		return data;
	}

	if (data[data_length] != '\0') {
		data[++data_length] = '\0';
	}

	if (data_length < alloc_length) {
		data = (char *)realloc(data, data_length);
	}

	return data;	
}
