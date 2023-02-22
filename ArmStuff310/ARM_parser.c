#include "ARM_parser.h"
#include "ARM_instructions.h"
#include "utility.h"

// main function starts the menu loop
void main() {
	// initializes the global instruction variables
	init_instructs();

	// initializes the buffer used for input
	char buff[BUFF_SIZE] = { '\0' };

	// checks that the buffer was able to be allocated
	if (buff == NULL) {
		puts("Could not allocate buffer");
		exit(1);
	}

	// loops infinitely
	while (1) {
		// clears the buffer
		memset(buff, '\0', BUFF_SIZE);

		// prints the menu
		puts("\nSelect Option:");
		puts("\t1) Assembly to Binary");
		puts("\t2) Binary to Assembly");
		puts("\t3) Quit");

		// take a line of input
		gets(buff, BUFF_SIZE);

		// checks that the line isnt empty, restarts the loop if it is
		// if the line exists, calls the appropriate function
		// otherwise, exits the infinite loop
		if (strlen(buff) == 0) {
			continue;
		}
		else if (strcmp(buff, "1\0") == 0) {
			assembly_to_binary(buff);
		}
		else if (strcmp(buff, "2\0") == 0) {
			memory_to_assembly(buff);
		}
		else if (strcmp(buff, "3\0") == 0) {
			break;
		}
	}
}

/*
	Name: assembly_to_binary
	Discription: prompts for a assembly instruction and then translates it
	Params: char* buff - buffer to use for input
	Return: none
*/
void assembly_to_binary(char* buff){

	// starts an infinite loop
	while (1) {
		// Clears the buffer and prints the prompt
		memset(buff, '\0', BUFF_SIZE);
		puts("\nEnter Assembly:");

		// take input
		gets(buff, BUFF_SIZE);

		// checks that the buffer is not empty
		if (strlen(buff) == 0) {
			return;
		}

		// encodes the instruction
		encode_assembly(buff);
	}
}

/*
	Name: memory_to_binary
	Discription: prompts for a values from memory and then translates it to assembly
	Params: char* buff - buffer to use for input
	Return: none
*/
void memory_to_assembly(char* buff) {
	// loops infinitely
	while (1) {
		// clears the buffer
		memset(buff, '\0', BUFF_SIZE);

		// prints the menu
		puts("\nSelect Option:");
		puts("\t1) Provide Hex");
		puts("\t2) Provide Binary");

		// take a line of input
		gets(buff, BUFF_SIZE);

		// checks that the line isnt empty, restarts the loop if it is
		// if the line exists, calls the appropriate function
		// otherwise, exits the infinite loop
		if (strlen(buff) == 0) {
			return;
		}
		else if (strcmp(buff, "1\0") == 0) {
			hex_to_assembly(buff);
		}
		else if (strcmp(buff, "2\0") == 0) {
			binary_to_assembly(buff);
		}
	}
}

/*
	Name: binary_to_assembly
	Discription: prompts for a binary string and then translates it
	Params: char* buff - buffer to use for input
	Return: none
*/
void binary_to_assembly(char* buff) {
	// creates a variable to hold the value of the instruction
	int command;

	// starts an infinite loop
	while (1) {
		// Clears the buffer and prints the prompt
		memset(buff, '\0', BUFF_SIZE);
		puts("\nEnter Binary:");

		// take input
		gets(buff, BUFF_SIZE);

		// checks that the buffer is not empty
		if (strlen(buff) == 0) {
			return;
		}

		// converts the binary string into a number
		command = atob(buff);

		// checks if it is a 16 bit or 32 bit instruction and decodes it
		if (command < 0x10000) {
			decode_16(command);
		}
		else {
			decode_32(command);
		}
	}
}

/*
	Name: hex_to_assembly
	Discription: prompts for a hex string and then translates it
	Params: char* buff - buffer to use for input
	Return: none
*/
void hex_to_assembly(char* buff) {
	// creates a variable to hold the value of the instruction
	uint32_t command;

	// starts an infinite loop
	while (1) {
		// Clears the buffer and prints the prompt
		memset(buff, '\0', BUFF_SIZE);
		puts("\nEnter Hex:");

		// take input
		gets(buff, BUFF_SIZE);

		// checks that the buffer is not empty
		if (strlen(buff) == 0) {
			return;
		}

		// converts the hex string into a number
		command = atox(buff);

		// checks if it is a 16 bit or 32 bit instruction and decodes it
		if (command < 0x10000) {
			decode_16(command);
		}
		else {
			decode_32(command);
		}
	}
}