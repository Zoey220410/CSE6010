#include "instructions.h"

void initialState(State* state){
	/* In the beginning, all the system state is zero.*/
	for(int i=0; i<8; i++){
		state->registers[i] = 0;
	}
	state->cc = 0;
	state->pc = 0;
}

long int convertToDecimal(const char *binary_ori) {
	/* convert substring to decimal number*/
	long int result;
	int length = strlen(binary_ori);
	char* binary = (char*)malloc((length + 1) * sizeof(char)); // create a string copy, to avoid modifying the origin one
	strncpy(binary, binary_ori, length); // copy the string
	binary[length] = '\0'; 
	
	// process the two's complement binary
	if(binary[0] == '1' && strlen(binary) > 3){
		binary[0] = '0';
		result = strtol(binary, NULL, 2) - (long int)pow(2, length-1); // calculate the negative number
	}else{
		result = strtol(binary, NULL, 2);
	}
	
	free(binary);

    return result;
}

long int substring(const char* str, int start_index, int length) {
	/* Extract the required bits from the instruction, and then convert it to the decimal.*/
    char* substr = (char*)malloc((length + 1) * sizeof(char));
	strncpy(substr, str + start_index, length); // extract the required bits
    substr[length] = '\0';
	
	long int res = convertToDecimal(substr); // convert string to the decimal
	
	free(substr);
	
    return res;
}

long int memoryFind(Memory* memory, long int addr, long int num){
	/* Find the corresponding data in main memory according to the address provided*/
	for(int i=0; i<num; i++){
		if(convertToDecimal(memory[i].address) == addr) return i;
	}
}

void modifyNZP(State* state, long int data){
	/* control the state->cc, according to the registers' numbers change.*/
	if(data < 0){
		state->cc = -1;  // postive -- N
	}else if (data == 0){
		state->cc = 0; // negative -- Z
	}else{
		state->cc = 1; // zero -- P
	}

}

void LD(State* state, Memory* memory, int i, long int num){
	/* load the data from the main memory to the registers, based on pc and offset*/
	long int reg, offset, addr, data_index, data;
	reg = substring(memory[i].content, 4, 3);
	offset = substring(memory[i].content, 7, 9);
	addr = state->pc + offset;  // data address = pc + offset
	
	data_index = memoryFind(memory, addr, num);
	data = convertToDecimal(memory[data_index].content); // find the data in the main memory
	state->registers[reg] = data;  // load the data to the register
	modifyNZP(state, data); // set the NZP
}

void LDR(State* state, Memory* memory, int i, long int num){
	/* load the data from the main memory to the registers, based on the address in one register and offset*/
	long int reg, offset, addr, data_index, data, base;
	reg = substring(memory[i].content, 4, 3);
	offset = substring(memory[i].content, 10, 6);
	base = substring(memory[i].content, 7, 3);
	addr = state->registers[base] + offset;  // data address = base + offset
	
	data_index = memoryFind(memory, addr, num);
	data = convertToDecimal(memory[data_index].content); // fetch the data from the main memory
	state->registers[reg] = data;  // load the date to the register
	modifyNZP(state, data); // set the NZP
	
}

void ADD(State* state, Memory* memory, int i, long int num){
	/* add two numbers, and put the result into one register*/
	long int reg, s1, s2, classify, data;
	reg = substring(memory[i].content, 4, 3);
	s1 = substring(memory[i].content, 7, 3);
	classify = substring(memory[i].content, 10, 1); // classify two kinds of add instructions

	if(classify == 0){
		// two numbers are from two registers
		s2 = substring(memory[i].content, 13, 3);
		state->registers[reg] = state->registers[s1] + state->registers[s2]; // the sum of the values of two source registers
	}else{
		// one number is from a register and the other is an immediate operand
		data = substring(memory[i].content, 11, 5);
		state->registers[reg] = state->registers[s1] + data; // the sum of the value of one source register and an immediate operand
	}
	modifyNZP(state, state->registers[reg]); // set the NZP
}

void BRp(State* state, Memory* memory, int i, long int num){
	/* Depending on the state->cc and p to determine whether to jump to another part of the program*/
	long int p, step;
	p = substring(memory[i].content, 6, 1); // p determines whether to jump
	
	if(p != 1 || state->cc != 1) return; 
	
	step = substring(memory[i].content, 7, 9);
	state->pc = state->pc + step; // jump to the destination
}

void STR(State* state, Memory* memory, int i, long int num){
	/* output the address based on a register's data and offset and the data of a register*/
	long int sr, offset, addr, base, data_index, data;
	sr = substring(memory[i].content, 4, 3);
	base = substring(memory[i].content, 7, 3);
	offset = substring(memory[i].content, 10, 6);
	
	addr = state->registers[base] + offset;  // data address = base + offset
	data = state->registers[sr];
		
	unsigned short addr_16bit = (unsigned short)(addr & 0xFFFF); // when the data is negative, intercepts only the last 16 bits
    printf("%X %ld\n", addr_16bit, data); 
}