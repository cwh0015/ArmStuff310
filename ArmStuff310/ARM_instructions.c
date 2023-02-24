#include "ARM_instructions.h"
#include "utility.h"

/*----------------------------\
	   assembly_instructs
\----------------------------*/
// arry containing all of the _assm functions
#define ASSM_COUNT 5 // <-- count needs to be increased when a function is added
int(*assembly_instructs[ASSM_COUNT])(char*) = {
	// function names are placed below in a comma seperated list
	movs_assm,
	movw_assm,
	lsrs_assm,
	adds_assm,
	mov_assm
};

/*----------------------------\
	   instructs_16_bit
\----------------------------*/
// arry containing all of the _bin functions for 16 bit instructions
#define BIT_16_COUNT 3 // <-- count needs to be increased when a function is added
int(*instructs_16_bit[ASSM_COUNT])(uint16_t) = {
	// function names are placed below in a comma seperated list
	movs_immd_bin,
	lsrs_bin,
	adds_bin
};

/*----------------------------\
       instructs_32_bit     
\----------------------------*/
// arry containing all of the _bin functions for 32 bit instructions
#define BIT_32_COUNT 2 // <-- count needs to be increased when a function is added
int(*instructs_32_bit[ASSM_COUNT])(uint32_t) = {
	// function names are placed below in a comma seperated list
	movw_bin,
	mov_bin
};

/*
	Name: init_instructs
	Discription: sets the default vslaues for the instruction varables
	Params: none
	Return: none
*/
void init_instructs() {
	// set the assm_instruct to empty, and inst16 & inst32 to 0;
	memset(assm_instruct, '\0', 50);
	inst16 = 0x0;
	inst32 = 0x0;
}

/*
	Name: encode_assembly
	Discription: runs through each _assm function and trys to encode the provide line
	Params: char* line - assembly string to encode
	Return: none
*/
void encode_assembly(char* line) {
	inst16 = 0x00;
	inst32 = 0x00;

	int code;

	for (int i = 0; i < ASSM_COUNT; i++) {
		code = (*assembly_instructs[i])(line);

		if (code != WRONG_COMMAND) {
			break;
		}
	}

	if (result_print(code) == 0) {
		if (inst16 != 0) {
			print_16(inst16);
		}
		else {
			print_32(inst32);
		}
	}
}

/*
	Name: decode_16
	Discription: runs through each _bin funstion for 16 bits and trys to decode the
		provided instruction
	Params: uint16_t command - instruction to decode
	Return: none
*/
void decode_16(uint16_t command) {
	memset(assm_instruct, '\0', 50);
	int code;

	for (int i = 0; i < BIT_16_COUNT; i++) {
		code = (*instructs_16_bit[i])(command);

		if (code != WRONG_COMMAND) {
			break;
		}
	}

	if (result_print(code) == 0) {
		puts(assm_instruct);
	}
}

/*
	Name: decode_32
	Discription: runs through each _bin funstion for 32 bits and trys to decode the
		provided instruction
	Params: uint32_t command - instruction to decode
	Return: none
*/
void decode_32(uint32_t command) {
	memset(assm_instruct, '\0', 50);
	int code;

	for (int i = 0; i < BIT_32_COUNT; i++) {
		code = (*instructs_32_bit[i])(command);

		if (code != WRONG_COMMAND) {
			break;
		}
	}

	if (result_print(code) == 0) {
		puts(assm_instruct);
	}
}

/*
	Name: result_print
	Discription: prints the approriate message based on the code given
	Params: in code - the code to print a message for
	Return: int returns whether the instrucion should be printed 0 for true, 1 for false
*/
int result_print(int code) {
	switch (code) {
	case COMPLETE: {
		return 0;
	}
	case WRONG_COMMAND: {
		puts("Unrecognized command");
		break;
	}
	case MISSING_DESTINATION: {
		puts("Expected destination register");
		break;
	}
	case INVALID_REG: {
		puts("Register provided is invalid for specified command");
		break;
	}
	case MISSING_PARAM: {
		puts("Expected a parameter");
		break;
	}
	case INVALID_PARAM: {
		puts("Parameter provided is invalid for specified command");
		break;
	}
	case UNEXPECTED_PARAM: {
		puts("Parameter was provided when none were expected");
		break;
	}
	case INVALID_IMMED: {
		puts("Provided immediate value is invalid");
		break;
	}
	case MISSING_SPACE: {
		puts("Expected a space and found none");
		break;
	}
	case MISSING_COMMA: {
		puts("Expected a comma and found none");
		break;
	}
	default: {
		puts("Unknow error occured.");
		break;
	}
	}
	return 1;
}

/*     Instruction Functions     */
/*
	Functions start with instruction name and are appended with _assm
	or _bin. _assm indicates that it will convert a instruction string
	into binary and _bin indicates it will converts binary into a
	instruction string. _assm will take a char* of the line to translate,
	_bin will take either a uint32_t or uint16_t depending on if it is
	a 32 or 16 bit instruction, and both will return a int that indicates
	what code the function finished with.
*/

/*     ADDS_BIN		*/
int adds_bin(uint16_t command) {

	// checks if the required bits match
	if (range_equals_16(command, 15, "0001100") != 0) {
		return WRONG_COMMAND;
	}



	// retrieves the register value
	int Rd = get_range_16(command, 2, 3);

	// checks that the register value is valid
	if (Rd == -1) {
		return INVALID_REG;
	}

	// retrieves the register value
	int Rm = get_range_16(command, 8, 3);

	// checks that the register value is valid
	if (Rm == -1) {
		return INVALID_REG;
	}


	// retrieves the register value
	int Rn = get_range_16(command, 5, 3);

	// checks that the register value is valid
	if (Rn == -1) {
		return INVALID_REG;
	}

	// combines the parts of the command into the assm_instruct string
	sprintf(assm_instruct, "ADDS R%d, R%d, R%d", Rd, Rn, Rm);


	return COMPLETE;
}

/* ADDS_ASSM */
int adds_assm(char* line) {

	// checks if it matches the MOVS
	if (expect_prefix(line, "ADDS") == 0) {
		line = remove_prefix(line, "ADDS");

		inst16 = 0x00;
		set_range_16(&inst16, 15, "0001100");
	}
	else {
		return WRONG_COMMAND;
	}



	// checks that the space is present
	if (expect_prefix(line, " ") == 0) {
		// removes the space
		line = remove_prefix(line, " ");
	}
	else {
		return MISSING_SPACE;
	}



	// checks for the start of a register paramater
	if (expect_prefix(line, "R") == 0) {
		// remove the R
		line = remove_prefix(line, "R");

		// converts the register number
		int Rd = atoi(line);

		// checks if the register is valid for MOVW
		if (Rd > 7 || Rd < 0) {
			return INVALID_REG;
		}
		else {
			// removes the register digits
			line = trim_digit(line);
			set_range_16(&inst16, 10, btoa(Rd, 3));

		}
	}
	else {
		return MISSING_DESTINATION;
	}



	// clears any white space
	line = trim_space(line);



	// checks that the comma is present
	if (expect_prefix(line, ",") == 0) {
		// removes the comma
		line = remove_prefix(line, ",");
	}
	else {
		return MISSING_COMMA;
	}



	// clears any white space
	line = trim_space(line);


	// checks for the start of a register paramater
	if (expect_prefix(line, "R") == 0) {
		// remove the R
		line = remove_prefix(line, "R");

		// converts the register number
		int Rn = atoi(line);

		// checks if the register is valid for ADDS
		if (Rn > 7 || Rn < 0) {
			return INVALID_REG;
		}
		else {
			// removes the register digits
			line = trim_digit(line);
			set_range_16(&inst16, 10, btoa(Rn, 3));

		}
	}



	// clears any white space
	line = trim_space(line);



	// checks that the comma is present
	if (expect_prefix(line, ",") == 0) {
		// removes the comma
		line = remove_prefix(line, ",");
	}
	else {
		return MISSING_COMMA;
	}



	// clears any white space
	line = trim_space(line);


	// checks for the start of a register paramater
	if (expect_prefix(line, "R") == 0) {
		// remove the R
		line = remove_prefix(line, "R");

		// converts the register number
		int Rm = atoi(line);

		// checks if the register is valid for ADDS
		if (Rm > 7 || Rm < 0) {
			return INVALID_REG;
		}
		else {
			// removes the register digits
			line = trim_digit(line);
			set_range_16(&inst16, 10, btoa(Rm, 3));

		}
	}
	else if (*line != '\0') { // if there is a parameter, but it is not expected
		return INVALID_PARAM;
	}
	else { // there is no other parameter
		return MISSING_PARAM;
	}







	// clears any white space
	line = trim_space(line);



	// checks that there is no more paramaters
	if (*line != '\0') {
		return UNEXPECTED_PARAM;
	}



	return COMPLETE;
}
/*     MOVS     */
int movs_assm(char* line) {

	// checks if it matches the MOVS
	if (expect_prefix(line, "MOVS") == 0) {
		line = remove_prefix(line, "MOVS");

		inst16 = 0x00;
		set_range_16(&inst16, 15, "00100");
	}
	else {
		return WRONG_COMMAND;
	}



	// checks that the space is present
	if (expect_prefix(line, " ") == 0) {
		// removes the space
		line = remove_prefix(line, " ");
	}
	else {
		return MISSING_SPACE;
	}



	// checks for the start of a register paramater
	if (expect_prefix(line, "R") == 0) {
		// remove the R
		line = remove_prefix(line, "R");

		// converts the register number
		int Rd = atoi(line);

		// checks if the register is valid for MOVW
		if (Rd > 7 || Rd < 0) {
			return INVALID_REG;
		}
		else {
			// removes the register digits
			line = trim_digit(line);
			set_range_16(&inst16, 10, btoa(Rd, 3));

		}
	}
	else {
		return MISSING_DESTINATION;
	}



	// clears any white space
	line = trim_space(line);



	// checks that the comma is present
	if (expect_prefix(line, ",") == 0) {
		// removes the comma
		line = remove_prefix(line, ",");
	}
	else {
		return MISSING_COMMA;
	}



	// clears any white space
	line = trim_space(line);



	// checks for the next paramater
	if (expect_prefix(line, "#") == 0) { // if it is an immediate
		line = remove_prefix(line, "#");

		int imm8;

		// checks if the immediate value is in hexadecimal or decimal
		if (expect_prefix(line, "0x") == 0) {
			imm8 = atox(line);
			line = remove_prefix(line, "0x");
		}
		else {
			imm8 = atoi(line);
		}

		
		// checks if the immediate vlaue is valid for MOVS
		if (imm8 > 0xFF || imm8 < 0x0) {
			return INVALID_IMMED;
		}
		else {

			// removes the immediate digits
			line = trim_digit(line);
			set_range_16(&inst16, 7, btoa(imm8, 8));
		}
	}
	else if (*line != '\0') { // if there is a parameter, but it is not expected
		return INVALID_PARAM;
	}
	else { // there is no other parameter
		return MISSING_PARAM;
	}



	// clears any white space
	line = trim_space(line);



	// checks that there is no more paramaters
	if (*line != '\0') {
		return UNEXPECTED_PARAM;
	}



	return COMPLETE;
}

int movs_immd_bin(uint16_t command) {

	// checks if the required bits match
	if (range_equals_16(command, 15, "00100") != 0) {
		return WRONG_COMMAND;
	}



	// retrieves the register value
	int Rd = get_range_16(command, 10, 3);

	// checks that the register value is valid
	if (Rd == -1) {
		return INVALID_REG;
	}


	// retrieves the immediate value
	int imm8 = get_range_16(command, 7, 8);

	// checks that the register value is valid
	if (imm8 == -1) {
		return INVALID_IMMED;
	}



	// combines the parts of the command into the assm_instruct string
	sprintf(assm_instruct, "MOVS R%d, #0x%02X", Rd, imm8);


	return COMPLETE;
}

/*     MOVW     */
int movw_assm(char* line) {

	// checks what command the line has
	if (expect_prefix(line, "MOVW") == 0) {
		// clears the 32 bit instruction
		inst32 = 0x0;

		// sets the required bits for MOVW
		set_range_32(&inst32, 31, "1111 0x10 0100 xxxx 0");

		// removes the MOVW
		line = remove_prefix(line, "MOVW");
	}
	else {
		return WRONG_COMMAND;
	}



	// checks that the space is present
	if (expect_prefix(line, " ") == 0) {
		// removes the space
		line = remove_prefix(line, " ");
	}
	else {
		return MISSING_SPACE;
	}



	// checks for the start of a register paramater
	if (expect_prefix(line, "R") == 0) {
		// remove the R
		line = remove_prefix(line, "R");

		// converts the register number
		int Rd = atoi(line);

		// checks if the register is valid for MOVW
		if (Rd > 15 || Rd < 0) {
			return INVALID_REG;
		}
		else {
			// removes the register digits
			line = trim_digit(line);

			// sets the register value
			set_range_32(&inst32, 11, btoa(Rd, 4));
		}
	}
	else {
		return MISSING_DESTINATION;
	}



	// clears any white space
	line = trim_space(line);



	// checks that the comma is present
	if (expect_prefix(line, ",") == 0) {
		// removes the comma
		line = remove_prefix(line, ",");
	}
	else {
		return MISSING_COMMA;
	}



	// clears any white space
	line = trim_space(line);



	// checks for the next paramater
	if (expect_prefix(line, "#") == 0) { // if it is an imeediate value
		line = remove_prefix(line, "#");

		int imm16;

		// checks if the immediate value is in hexadecimal or decimal
		if (expect_prefix(line, "0x") == 0) {
			imm16 = atox(line);
			line = remove_prefix(line, "0x");
		}
		else {
			imm16 = atoi(line);
		}

		// checks if the immediate vlaue is valid for MOVS
		if (imm16 > 0xFFFF || imm16 < 0x0) {
			return INVALID_IMMED;
		}
		else {

			// removes the immediate digits
			line = trim_digit(line);

			// sets the imm8 value and then clears the bits out
			set_range_32(&inst32, 7, btoa((imm16 & 0xFF), 8));
			imm16 = imm16 >> 8;

			// sets the imm3 value and then clears the bits out
			set_range_32(&inst32, 14, btoa((imm16 & 0x7), 3));
			imm16 = imm16 >> 3;

			// sets the i value and then clears the bits out
			set_range_32(&inst32, 26, btoa((imm16 & 0x1), 1));
			imm16 = imm16 >> 1;

			// sets the imm4 value
			set_range_32(&inst32, 19, btoa((imm16 & 0xF), 4));
		}
	}
	else if (*line != '\0') { // if there is a parameter, but it is not expected
		return INVALID_PARAM;
	}
	else {
		return MISSING_PARAM;
	}



	// clears any white space
	line = trim_space(line);



	// checks that there is no more paramaters
	if (*line != '\0') {
		return UNEXPECTED_PARAM;
	}



	return COMPLETE;
}

int movw_bin(uint32_t command) {
	
	// checks if the required bits match
	if (range_equals_32(command, 31, "1111 0x10 0100 xxxx 0") != 0) {
		return WRONG_COMMAND;
	}



	// retrieves the register value
	int Rd = get_range_32(command, 11, 4);

	// checks that the register value is valid
	if (Rd == -1) {
		return INVALID_REG;
	}

	// retrieves the immediate value parts
	int imm4 = get_range_32(command, 19, 4);
	int i = get_range_32(command, 26, 1);
	int imm3 = get_range_32(command, 14, 3);
	int imm8 = get_range_32(command, 7, 8);

	// combines the immediate value
	uint32_t immd = (imm4 << 12) | (i << 11) | (imm3 << 8) | (imm8);

	// checks that the register value is valid
	if (immd == -1) {
		return INVALID_IMMED;
	}



	// combines the parts of the command into the assm_instruct string
	sprintf(assm_instruct, "%s R%d, #0x%04X", "MOVW", Rd, immd);

	return COMPLETE;
}

int lsrs_assm(char* line)
{
	/**
	 * @brief parses left shift command from assembly to binary
	 * @param line user input to be parsed
	 * @return 
	*/
	if (expect_prefix(line, "LSRS") == 0) {
		line = remove_prefix(line, "LSRS");

		inst16 = 0x00;
		set_range_16(&inst16, 15, "00001");
	}
	else {
		return WRONG_COMMAND;
	}
	
	// checks that the space is present
	if (expect_prefix(line, " ") == 0) {
		// removes the space
		line = remove_prefix(line, " ");
	}
	else {
		return MISSING_SPACE;
	}
	
	if (expect_prefix(line, "R") == 0) {
		// remove the R
		line = remove_prefix(line, "R");

		// converts the register number
		int Rd = atoi(line);

		// checks if the register is valid for MOVW
		if (Rd > 7 || Rd < 0) {
			return INVALID_REG;
		}
		else {
			// removes the register digits
			line = trim_digit(line);
			set_range_16(&inst16, 2, btoa(Rd, 3));

		}
	}
	else {
		return MISSING_DESTINATION;
	}

	// checks that the comma is present
	if (expect_prefix(line, ",") == 0) {
		// removes the comma
		line = remove_prefix(line, ",");
	}
	else {
		return MISSING_COMMA;
	}

	// clears any white space
	line = trim_space(line);

	// checks for the start of a register paramater
	if (expect_prefix(line, "R") == 0) {
		// remove the R
		line = remove_prefix(line, "R");

		// converts the register number
		int Rm = atoi(line);

		// checks if the register is valid for MOVW
		if (Rm > 7 || Rm < 0) {
			return INVALID_REG;
		}
		else {
			// removes the register digits
			line = trim_digit(line);
			set_range_16(&inst16, 5, btoa(Rm, 3));

		}
	}
	else {
		return MISSING_PARAM;
	}

	// checks that the comma is present
	if (expect_prefix(line, ",") == 0) {
		// removes the comma
		line = remove_prefix(line, ",");
	}
	else {
		return MISSING_COMMA;
	}

	// clears any white space
	line = trim_space(line);

	if (expect_prefix(line, "#") == 0) { // if it is an immediate
		line = remove_prefix(line, "#");

		int imm5;

		// checks if the immediate value is in hexadecimal or decimal
		if (expect_prefix(line, "0x") == 0) {
			imm5 = atox(line);
			line = remove_prefix(line, "0x");
		}
		else {
			imm5 = atoi(line);
		}


		// checks if the immediate vlaue is valid for MOVS
		if (imm5 > 0x20 || imm5 < 0x1) {
			return INVALID_IMMED;
		}
		else {

			// removes the immediate digits
			line = trim_digit(line);
			set_range_16(&inst16, 10, btoa(imm5, 5));
		}
	}
	else if (*line != '\0') { // if there is a parameter, but it is not expected
		return INVALID_PARAM;
	}
	else { // there is no other parameter
		return MISSING_PARAM;
	}



	// clears any white space
	line = trim_space(line);



	// checks that there is no more paramaters
	if (*line != '\0') {
		return UNEXPECTED_PARAM;
	}



	return COMPLETE;
}

int lsrs_bin(uint16_t command)
{
	// checks if the required bits match
	if (range_equals_16(command, 15, "00001") != 0) {
		return WRONG_COMMAND;
	}

	int Rd = get_range_16(command, 2, 3);

	if (Rd == -1) {
		return INVALID_REG;
	}

	int Rm = get_range_16(command, 5, 3);

	if (Rm == -1) {
		return INVALID_REG;
	}

	int imm5 = get_range_16(command, 10, 5);

	// checks that the register value is valid
	if (imm5 == -1) {
		return INVALID_IMMED;
	}

	sprintf(assm_instruct, "LSRS R%d, R%d, #0x%02X", Rd, Rm, imm5);

	return COMPLETE;
}
int mov_assm(char* line) {

	// checks what command the line has
	if (expect_prefix(line, "MOV") == 0) {
		// clears the 32 bit instruction
		inst32 = 0x0;

		// sets the required bits for MOVW
		set_range_32(&inst32, 31, "1110 1010 010x 1111 0000 xxxx 0000 xxxx");

		// removes the MOVW
		line = remove_prefix(line, "MOV");
	}
	else {
		return WRONG_COMMAND;
	}

	if (expect_prefix(line, "S") == 0) {
		line = remove_prefix(line, "S");
		set_range_32(&inst32, 20, btoa(1, 1));
	}
	else {
		set_range_32(&inst32, 20, btoa(0, 1));
	}

	// checks that the space is present
	if (expect_prefix(line, " ") == 0) {
		// removes the space
		line = remove_prefix(line, " ");
	}
	else {
		return MISSING_SPACE;
	}

	// checks for the start of a register paramater
	if (expect_prefix(line, "R") == 0) {
		// remove the R
		line = remove_prefix(line, "R");

		// converts the register number
		int Rd = atoi(line);

		// checks if the register is valid for MOVW
		if (Rd > 15 || Rd < 0) {
			return INVALID_REG;
		}
		else {
			// removes the register digits
			line = trim_digit(line);

			// sets the register value
			set_range_32(&inst32, 11, btoa(Rd, 4));
		}
	}
	else {
		return MISSING_DESTINATION;
	}



	// clears any white space
	line = trim_space(line);



	// checks that the comma is present
	if (expect_prefix(line, ",") == 0) {
		// removes the comma
		line = remove_prefix(line, ",");
	}
	else {
		return MISSING_COMMA;
	}



	// clears any white space
	line = trim_space(line);


	if (expect_prefix(line, "R") == 0) {
		// remove the R
		line = remove_prefix(line, "R");

		// converts the register number
		int Rd = atoi(line);

		// checks if the register is valid for MOVW
		if (Rd > 15 || Rd < 0) {
			return INVALID_REG;
		}
		else {
			// removes the register digits
			line = trim_digit(line);

			// sets the register value
			set_range_32(&inst32, 3, btoa(Rd, 4));
		}
	}
	else {
		return MISSING_DESTINATION;
	}



	// clears any white space
	line = trim_space(line);



	// checks that there is no more paramaters
	if (*line != '\0') {
		return UNEXPECTED_PARAM;
	}



	return COMPLETE;
}

int mov_bin(uint32_t command) {

	// checks if the required bits match
	if (range_equals_32(command, 31, "1110 1010 010x 1111 0000 xxxx 0000 xxxx") != 0) {
		return WRONG_COMMAND;
	}



	// retrieves the register value
	int Rd = get_range_32(command, 11, 4);

	int Rm = get_range_32(command, 3, 4);

	int S = get_range_32(command, 20, 1);

	// checks that the register value is valid
	if (Rd == -1) {
		return INVALID_REG;
	}

	if (Rm == -1) {
		return INVALID_REG;
	}

	// combines the parts of the command into the assm_instruct string
	sprintf(assm_instruct, "%s%d R%d, R%d", "MOV", S, Rd, Rm);

	return COMPLETE;
}