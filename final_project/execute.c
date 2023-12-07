#include "instructions.h"

void initialState(State* state){
	for(int i=0; i<8; i++){
		state->registers[i] = 0;
	}
	state->cc = 0;
	state->pc = 0;
}

long int convertToDecimal(const char *binary_ori) {
	long int result;
	int length = strlen(binary_ori);
	char* binary = (char*)malloc((length + 1) * sizeof(char));
	strncpy(binary, binary_ori, length);
	binary[length] = '\0';
	
	if(binary[0] == '1' && strlen(binary) > 3){
		binary[0] = '0';
		result = strtol(binary, NULL, 2) - (long int)pow(2, length-1);
	}else{
		result = strtol(binary, NULL, 2);
	}
	
	free(binary);

    return result;
}

long int substring(const char* str, int start_index, int length) {
    char* substr = (char*)malloc((length + 1) * sizeof(char));
	strncpy(substr, str + start_index, length);
    substr[length] = '\0';
	
	long int res = convertToDecimal(substr);
	
	free(substr);
	
    return res;
}

long int memoryFind(Memory* memory, long int addr, long int num){
	for(int i=0; i<num; i++){
		if(convertToDecimal(memory[i].address) == addr) return i;
	}
}

void modifyNZP(State* state, long int data){
	if(data < 0){
		state->cc = -1;  // postive -- N
	}else if (data == 0){
		state->cc = 0; // negative -- Z
	}else{
		state->cc = 1; // zero -- P
	}

}

void LD(State* state, Memory* memory, int i, long int num){
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
	long int reg, s1, s2, classify, data;
	reg = substring(memory[i].content, 4, 3);
	s1 = substring(memory[i].content, 7, 3);
	classify = substring(memory[i].content, 10, 1); // classify two kinds of add instructions

	if(classify == 0){
		s2 = substring(memory[i].content, 13, 3);
		state->registers[reg] = state->registers[s1] + state->registers[s2]; // the sum of the values of two source registers
	}else{
		data = substring(memory[i].content, 11, 5);
		state->registers[reg] = state->registers[s1] + data; // the sum of the value of one source register and an immediate operand
	}
	modifyNZP(state, state->registers[reg]); // set the NZP
}

void BRp(State* state, Memory* memory, int i, long int num){
	long int p, step;
	p = substring(memory[i].content, 6, 1); // p determines whether to jump
	
	if(p != 1 || state->cc != 1) return; 
	
	step = substring(memory[i].content, 7, 9);
	state->pc = state->pc + step; // jump to the destination
}

void STR(State* state, Memory* memory, int i, long int num){
	long int sr, offset, addr, base, data_index, data;
	sr = substring(memory[i].content, 4, 3);
	base = substring(memory[i].content, 7, 3);
	offset = substring(memory[i].content, 10, 6);
	
	addr = state->registers[base] + offset;  // data address = base + offset
	data = state->registers[sr];
		
	unsigned short addr_16bit = (unsigned short)(addr & 0xFFFF);
    printf("%X %ld\n", addr_16bit, data);
}