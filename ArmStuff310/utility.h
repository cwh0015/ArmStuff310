#ifndef _UTILITY_H_
#define _UTILITY_H_

#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* 
	gets(char* buffer, int size)
	gets is depreciated and not considered safe, this define replaces
	it with a safe version the works virtually identically
*/
#define gets(x,y); if(fgets(x,y,stdin) != NULL){x[strlen(x)-1] = '\0';}

// code constants to indicate statuses
enum code {
	COMPLETE,
	WRONG_COMMAND,
	MISSING_DESTINATION,
	INVALID_REG,
	MISSING_PARAM,
	INVALID_PARAM,
	UNEXPECTED_PARAM,
	INVALID_IMMED,
	MISSING_SPACE,
	MISSING_COMMA
};

/*
	Name: atox
	Description: converts a hex string into a integer
	Params: char* str - the string to convert
	Returns: int - the converted number
*/
int atox(char* str);

/*
	Name: atob
	Description: converts a binary string into a integer
	Params: char* str - the string to convert
	Returns: int - the converted number
*/
int atob(char* str);

/*
	Name: btoa
	Description: converts a number into a stirng of binary
	Params: int n - number to convert, int size - minimum number of digits needed
	Returns: returns the string of binary with leading zeros if needed
*/
char* btoa(int n, int size);

/*
	Name: set_range_16
	Description: sets the specified number of bits starting at the specified bit
	Params: uint16_t* data - value to change, int start_bit - bit to start at, char* val - string of bits to put in
	Returns: 1 on success, -1 on error
*/
int set_range_16(uint16_t* data, int start_bit, char* val);

/*
	Name: set_range_32
	Description: sets the specified number of bits starting at the specified bit
	Params: uint32_t* data - value to change, int start_bit - bit to start at, char* val - string of bits to put in
	Returns: 1 on success, -1 on error
*/
int set_range_32(uint32_t* data, int start_bit, char* val);

/*
	Name: range_equals_16
	Description: checks if the range stattng at the specified bit matches the specified str
	Params: uint16_t data - value to check, int start_bit - bit to start at, char* str - string to compare to
	Returns: returns 0 for true, 1 for false, -1 for error
*/
int range_equals_16(uint16_t data, int start_bit, char* str);

/*
	Name: range_equals_32
	Description: checks if the range stattng at the specified bit matches the specified str
	Params: uint16_t data - value to check, int start_bit - bit to start at, char* str - string to compare to
	Returns: returns 0 for true, 1 for false, -1 for error
*/
int range_equals_32(uint32_t data, int start_bit, char* str);

/*
	Name: get_range_16
	Description: converts the specified range into a number
	Params:uint16_t data - source of the value, int start_bit - bit to start at, int size - number of bits to pull
	Returns: value on sucess, -1 on error
*/
int get_range_16(uint16_t data, int start_bit, int size);

/*
	Name: get_range_32
	Description: converts the specified range into a number
	Params:uint32_t data - source of the value, int start_bit - bit to start at, int size - number of bits to pull
	Returns: value on sucess, -1 on error
*/
int get_range_32(uint32_t data, int start_bit, int size);

/*
	Name: trim_space
	Description: trims leading spaces from the string
	Params: char* input - string to trim
	Returns: returns a ptr to the trimmed string
*/
char* trim_space(char* input);

/*
	Name: trim_digit
	Description: trims leading digits from the string
	Params: char* input - string to trim
	Returns: returns a ptr to the trimmed string
*/
char* trim_digit(char* input);

/*
	Name: expect_prefix
	Description: checks for the specified prefix, case insensitive, in the given string
	Params: char* input - string to check, char* prefix - prefix to expect
	Returns: returns 0 if the prefix is found, 1 if the prefix is not present, -1 on error
*/
int expect_prefix(char* input, char* prefix);

/*
	Name: remove_prefix
	Description: removes for the specified prefix, case insensitive, in the given string
	Params: char* input - string to check, char* prefix - prefix to remove
	Returns: returns a ptr to the adjusted string, NULL on error
*/
char* remove_prefix(char* input, char* prefix);

/*
	Name: print_16
	Description: prints a uint16_t
	Params: uint16_t value value to print
	Returns: none
*/
void print_16(uint16_t value);

/*
	Name: print_32
	Description: prints a uint32_t
	Params: uint32_t value value to print
	Returns: none
*/
void print_32(uint32_t value);

/*
	Name: strcmp_ignore_case
	Description: compares 2 strings ignoring case
	Params: char* str1 - first stirng to compare, char* str2 - second string to compare
	Returns: 0 if equal, 1 if not
*/
int strcmp_ignore_case(char* str1, char* str2);

/*
	Name: charcmp_ignore_case
	Description: compares 2 characters
	Params: char c1 - first char to compare, char c2 - second char to compare
	Returns: 0 if equal, 1 if not
*/
int charcmp_ignore_case(char c1, char c2);

/*
	Name: get_input
	Description: compares 2 characters
	Params: char c1 - first char to compare, char c2 - second char to compare
	Returns: 0 if equal, 1 if not
*/
int get_input(char* bufer, int size);

#endif