#ifndef _ARM_PARSER_H_
#define _ARM_PARSER_H_

#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// buffer size constant
#define BUFF_SIZE 100

/*
	Name: assembly_to_binary
	Discription: prompts for a assembly instruction and then translates it
	Params: char* buff - buffer to use for input
	Return: none
*/
void assembly_to_binary(char* buff);

/*
	Name: memory_to_binary
	Discription: prompts for a values from memory and then translates it to assembly
	Params: char* buff - buffer to use for input
	Return: none
*/
void memory_to_assembly(char* buff);

/*
	Name: binary_to_assembly
	Discription: prompts for a binary string and then translates it
	Params: char* buff - buffer to use for input
	Return: none
*/
void binary_to_assembly(char* buff);

/*
	Name: hex_to_assembly
	Discription: prompts for a hex string and then translates it
	Params: char* buff - buffer to use for input
	Return: none
*/
void hex_to_assembly(char* buff);


#endif