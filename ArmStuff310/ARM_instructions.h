#ifndef _ARM_INSTUCTIONS_H_
#define _ARM_INSTUCTIONS_H_

#pragma warning(disable : 4996)

#include <stdint.h>
#include <string.h>

// global instruction variables
char assm_instruct[50];
uint16_t inst16;
uint32_t inst32;

/*
	Name: init_instructs
	Discription: sets the default vslaues for the instruction varables
	Params: none
	Return: none
*/
void init_instructs();

/*
	Name: encode_assembly
	Discription: runs through each _assm function and trys to encode the provide line
	Params: char* line - assembly string to encode
	Return: none
*/
void encode_assembly(char* line);

/*
	Name: decode_16
	Discription: runs through each _bin funstion for 16 bits and trys to decode the
		provided instruction
	Params: uint16_t command - instruction to decode
	Return: none
*/
void decode_16(uint16_t command);

/*
	Name: decode_32
	Discription: runs through each _bin funstion for 32 bits and trys to decode the
		provided instruction
	Params: uint32_t command - instruction to decode
	Return: none
*/
void decode_32(uint32_t command);

/*
	Name: result_print
	Discription: prints the approriate message based on the code given
	Params: in code - the code to print a message for
	Return: int returns whether the instrucion should be printed 0 for true, 1 for false
*/
int result_print(int code);


/*     Instruction Functions     */

/*     MOVS     */
int movs_assm(char* line);

int movs_immd_bin(uint16_t command);

/*     MOVW     */
int movw_assm(char* line);

int movw_bin(uint32_t command);

/*		LSRS		*/
int lsrs_assm(char* line);

int lsrs_bin(uint32_t);

#endif