#include "utility.h"

// string used for convetingnumbers to text
char conversion[50];

/*
	Name: atox
	Description: converts a hex string into a integer
	Params: char* str - the string to convert
	Returns: int - the converted number
*/
int atox(char* str) {
	// starting value
	int value = 0;

	// removes any leading hex identifier
	if (*str == '0') {
		str++;
	}

	if (*str == 'X' || *str == 'x') {
		str++;
	}

	// Loops while we are not at the end of the string
	while (*str != '\0') {
		// Checks which character the digit is and adds the appropriate value
		switch (toupper(*str)) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			value = (value * 16) + *(str)-48;
			break;

		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
			value = (value * 16) + toupper(*(str))-55;
			break;

		case ' ':
			break;
		default:
			return value;
		}

		// iterates the position in the string
		str++;
	}

	// returns the final value
	return value;
}

/*
	Name: atob
	Description: converts a binary string into a integer
	Params: char* str - the string to convert
	Returns: int - the converted number
*/
int atob(char* str) {
	// initial value
	int value = 0;

	// removes any leading binary identifier
	if (*str == '0') {
		str++;
	}

	if (*str == 'b' || *str == 'B') {
		str++;
	}

	// Loops while we are not at the end of the string
	while (*str != '\0') {
		// Checks which character the digit is and adds the appropriate value
		switch (*str) {
		case '0':
		case '1':
			value = (value * 2) + *(str)-48;
			break;
		case ' ':
			break;
		default:
			return value;
		}

		// returns the final value
		str++;
	}

	return value;
}

/*
	Name: btoi
	Description: converts a number into a stirng of binary
	Params: int n - number to convert, char* str- string to store the result in, int size - minimum number rof digits needed
	Returns: returns the string of binary with leading zeros if needed
*/
char* btoa(int n, int size) {
	memset(conversion, '\0', 50);
	int index = 0;

	while (n != 0) {
		if (n % 2 == 0) {
			conversion[index++] = '0';
		}
		else {
			conversion[index++] = '1';
		}

		n = n / 2;
	}

	while (strlen(conversion) < size && index < 40) {
		conversion[index++] = '0';
	}

	index--;

	int i = 0;
	while (i < index) {
		char c = conversion[i];
		conversion[i] = conversion[index];
		conversion[index] = c;
		index--;
		i++;
	}

	return conversion;
}

/*
	Name: set_range_16
	Description: sets the specified numebr of bits starting at the specified bit
	Params: uint16_t* data - value to change, int start_bit - bit to start at, char* val - string of bits to put in
	Returns: 1 on success, -1 on error
*/
int set_range_16(uint16_t* data, int start_bit, char* val) {

	// checks that parameters are valid
	if (strlen(val) == 0) {
		puts("Invalid string");
		return -1;
	}

	if (start_bit > 15 || start_bit < 0) {
		puts("Start bit is invlaid");
		return -1;
	}

	// starts the counter variable
	int i = start_bit;

	while (1) {
		// exits loop if we have gone past bit 0
		if (i < 0) {
			break;
		}

		// exits the loop if we have run out of string
		if (*val == '\0') {
			break;
		}

		// eats any misc spaces
		if (*val == ' ') {
			val++;
			continue;
		}

		// sets a bit if the string has a 1
		// clears a bit if the string has a 0
		// ignores a bit if the string has X or x
		// otherwise it errors
		if (*val == '1') {
			(*data) |= 0x1 << i;
			i--;
			val++;
		}
		else if (*val == '0') {
			(*data) &= ~(0x1 << i);
			i--;
			val++;
		}
		else if (*val == 'X' || *val == 'x') {
			i--;
			val++;
		}
		else {
			return -1;
		}


	}

	return 1;
}

/*
	Name: set_range_32
	Description: sets the specified numebr of bits starting at the specified bit
	Params: uint32_t* data - value to change, int start_bit - bit to start at, char* val - string of bits to put in
	Returns: 1 on success, -1 on error
*/
int set_range_32(uint32_t* data, int start_bit, char* val) {

	// checks that parameters are valid
	if (strlen(val) == 0) {
		puts("Invalid comparison string");
		return -1;
	}

	if (start_bit > 31 || start_bit < 0) {
		puts("Start bit is invlaid");
		return -1;
	}

	// starts the counter variable
	int i = start_bit;

	while (1) {
		// exits loop if we have gone past bit 0
		if (i < 0) {
			break;
		}

		// exits the loop if we have run out of string
		if (*val == '\0') {
			break;
		}

		// eats any misc spaces
		if (*val == ' ') {
			val++;
			continue;
		}

		// sets a bit if the string has a 1
		// clears a bit if the string has a 0
		// ignores a bit if the string has X or x
		// otherwise it errors
		if (*val == '1') {
			(*data) |= 0x1 << i;
			i--;
			val++;
		}
		else if (*val == '0') {
			(*data) &= ~(0x1 << i);
			i--;
			val++;
		}
		else if (*val == 'X' || *val == 'x') {
			i--;
			val++;
		}
		else {
			return -1;
		}


	}

	return 1;
}

/*
	Name: range_equals_16
	Description: checks if the range stattng at the specified bit matches the specified str
	Params: uint16_t data - value to check, int start_bit - bit to start at, char* str - string to compare to
	Returns: returns 0 for true, 1 for false, -1 for error
*/
int range_equals_16(uint16_t data, int start_bit, char* str) {
	// checks that parameters are valid
	if (strlen(str) == 0) {
		puts("Invalid comparison string");
		return -1;
	}

	if (start_bit > 15 || start_bit < 0) {
		puts("Start bit is invlaid");
		return -1;
	}

	// starts the counter bit
	int i = start_bit;

	while (1) {
		// breaks if we have gone past bit 0
		if (i < 0) {
			break;
		}

		// breaks if we are at the end of the string
		if (*str == '\0') {
			break;
		}

		// eats any spaces
		if (*str == ' ') {
			str++;
			continue;
		}

		// skips any x's
		if (charcmp_ignore_case(*str, 'x') == 0) {
			str++;
			i--;
			continue;
		}

		// checks the bit
		if (((data >> i) & 1) != (*str - 48)) {
			return 1;
		}

		// itertates the counter and str
		i--;
		str++;
	}

	return 0;
}

/*
	Name: range_equals_32
	Description: checks if the range stattng at the specified bit matches the specified str
	Params: uint32_t data - value to check, int start_bit - bit to start at, char* str - string to compare to
	Returns: returns 0 for true, 1 for false, -1 for error
*/
int range_equals_32(uint32_t data, int start_bit, char* str) {
	// checks that parameters are valid
	if (strlen(str) == 0) {
		puts("Invalid comparison string");
		return -1;
	}

	if (start_bit > 31 || start_bit < 0) {
		puts("Start bit is invlaid");
		return -1;
	}

	// starts the counter bit
	int i = start_bit;

	while (1) {
		// breaks if we have gone past bit 0
		if (i < 0) {
			break;
		}

		// breaks if we are at the end of the string
		if (*str == '\0') {
			break;
		}

		// eats any spaces
		if (*str == ' ') {
			str++;
			continue;
		}

		// skips any x's
		if (charcmp_ignore_case(*str, 'x') == 0) {
			str++;
			i--;
			continue;
		}

		// checks the bit
		if (((data >> i) & 1) != (*str - 48)) {
			return 1;
		}

		// itertates the counter and str
		i--;
		str++;
	}

	return 0;
}

/*
	Name: get_range_16
	Description: converts the specified range into a number
	Params:uint16_t data - source of the value, int start_bit - bit to start at, int size - number of bits to pull
	Returns: value on sucess, -1 on error
*/
int get_range_16(uint16_t data, int start_bit, int size) {
	// checks that the range is valid
	if (start_bit > 15 || start_bit < 0) {
		puts("Invalid start bit");
		return -1;
	}

	if (size < 0 || (start_bit - size) < -1) {
		puts("Not enough bit to retreive");
		return -1;
	}

	// starts the converted value
	int output = 0;

	// compiles each bit into the value
	for (int i = start_bit; i > start_bit - size; i--) {
		output = output * 2;
		output = output + ((data >> i) & 1);
	}

	// returns the value
	return output;
}

/*
	Name: get_range_32
	Description: converts the specified range into a number
	Params:uint32_t data - source of the value, int start_bit - bit to start at, int size - number of bits to pull
	Returns: value on sucess, -1 on error
*/
int get_range_32(uint32_t data, int start_bit, int size) {
	// checks that the range is valid
	if (start_bit > 31 || start_bit < 0) {
		puts("Invalid start bit");
		return -1;
	}

	if (size < 0 || (start_bit - size) < -1) {
		puts("Not enough bit to retreive");
		return -1;
	}

	// starts the converted value
	int output = 0;

	// compiles each bit into the value
	for (int i = start_bit; i > start_bit - size; i--) {
		output = output * 2;
		output = output + ((data >> i) & 1);
	}

	// returns the value
	return output;
}

/*
	Name: trim_space
	Description: trims leading spaces from the string
	Params: char* input - string to trim
	Returns: returns a ptr to the trimmed string
*/
char* trim_space(char* input) {
	if (input == NULL) {
		return input;
	}

	// iterates the pointer until there isnt a leading space
	while (*input == ' ') {
		input++;
	}

	//returns the pointer
	return input;
}

/*
	Name: trim_digit
	Description: trims leading digits from the string
	Params: char* input - string to trim
	Returns: returns a ptr to the trimmed string
*/
char* trim_digit(char* input) {
	if (input == NULL) {
		return input;
	}

	// iterates the pointer until there isnt a leading hex character
	while (*input != '\0') {

		switch (toupper(*input)) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F': {
			input++;
			break;
		}
		default: {
			return input++;
		}
		}
	}


	//returns the pointer
	return input;
}

/*
	Name: expect_prefix
	Description: checks for the specified prefix, case insensitive, in the given string
	Params: char* input - string to check, char* prefix - prefix to expect
	Returns: returns 0 if the prefix is found, 1 if the prefix is not present, -1 on error
*/
int expect_prefix(char* input, char* prefix) {
	// checks tha the pointers are not null
	if (prefix == NULL || input == NULL) {
		return -1;
	}

	// loops through each position and compares the characters, until prefix is empty
	while (*prefix != '\0') {
		//if the characters are not equal, return 1 (false)
		if (charcmp_ignore_case(*input, *prefix) != 0) {
			return 1;
		}

		// iterate both pointers
		input++;
		prefix++;
	}

	// if prefix ran out, return 0 (true)
	return 0;
}

/*
	Name: remove_prefix
	Description: removes for the specified prefix, case insensitive, in the given string
	Params: char* input - string to check, char* prefix - prefix to remove
	Returns: returns a ptr to the adjusted string, NULL on error
*/
char* remove_prefix(char* input, char* prefix) {
	// checks tha the pointers are not null
	if (prefix == NULL || input == NULL) {
		return NULL;
	}

	// loops through each position and compares the characters, until prefix is empty
	while (*prefix != '\0') {
		//if the characters are not equal, return NULL
		if (charcmp_ignore_case(*input, *prefix) != 0) {
			return NULL;
		}

		// iterate both pointers
		input++;
		prefix++;
	}

	// if prefix ran out, return the adjusted pointer
	return input;
}

/*
	Name: print_16
	Description: prints a uint16_t
	Params: uint16_t value value to print
	Returns: none
*/
void print_16(uint16_t value) {
	printf("Hex: 0x%04X\tBinary:", value);

	for (int i = 15; i > -1; i--) {
		printf("%d", (value >> i) & 1);

		if (i % 4 == 0) {
			printf(" ");
		}
	}

	printf("\n");
}

/*
	Name: print_32
	Description: prints a uint32_t
	Params: uint32_t value value to print
	Returns: none
*/
void print_32(uint32_t value) {
	printf("Hex: 0x%04X\tBinary:", value);

	for (int i = 31; i > -1; i--) {
		printf("%d", (value >> i) & 1);

		if (i % 4 == 0) {
			printf(" ");
		}
	}

	printf("\n");
}

/*
	Name: strcmp_ignore_case
	Description: compares 2 strings ignoring case
	Params: char* str1 - first stirng to compare, char* str2 - second string to compare
	Returns: 0 if equal, 1 if not
*/
int strcmp_ignore_case(char* str1, char* str2) {
	// loops through until at least one of the strings is finished
	while (*str1 != '\0' && *str2 != '\0') {
		// if the current char isnt equal, return -1
		if (charcmp_ignore_case(*str1, *str2) != 0) {
			return 1;
		}

		// iterates both strings
		str1++;
		str2++;
	}

	// if bothstrings were finished, then return 0
	if (*str1 == '\0' && *str2 == '\0') {
		return 0;
	}
	else {
		return 1;
	}
}

/*
	Name: charcmp_ignore_case
	Description: compares 2 characters
	Params: char c1 - first char to compare, char c2 - second char to compare
	Returns: 0 if equal, 1 if not
*/
int charcmp_ignore_case(char c1, char c2) {
	// if c1 is lowercase, convers to uppercase
	if (c1 >= 'a' && c1 <= 'z') {
		c1 = c1 - 32;
	}

	// if c2 is lowercase, convers to uppercase
	if (c2 >= 'a' && c2 <= 'z') {
		c2 = c2 - 32;
	}

	// compares them
	if (c1 == c2) {
		return 0;
	}
	else {
		return -1;
	}
}