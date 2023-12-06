#include "instructions.h"

void initialState(State* state){
	for(int i=0; i<8; i++){
		state->registers[i] = 0;
	}
	state->cc = 0;
	state->pc = 0;
}

long int convertToDecimal(const char *binary) {
    return strtol(binary, NULL, 2);
}

char* substring(const char* str, int start_index, int length) {
    char* substr = (char*)malloc((length + 1) * sizeof(char));
    
	strncpy(substr, str + start_index, length);
	
    substr[length] = '\0';
	
    return substr;
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
	reg = convertToDecimal(substring(memory[i].content, 4, 3));
	offset = convertToDecimal(substring(memory[i].content, 7, 9));
	addr = state->pc + offset;  // data address = pc + offset
	
	data_index = memoryFind(memory, addr, num);
	data = convertToDecimal(memory[data_index].content); // find the data in the main memory
	state->registers[reg] = data;  // load the data to the register
	modifyNZP(state, data); // set the NZP
}

void LDR(State* state, Memory* memory, int i, long int num){
	long int reg, offset, addr, data_index, data, base;
	reg = convertToDecimal(substring(memory[i].content, 4, 3));
	offset = convertToDecimal(substring(memory[i].content, 10, 6));
	base = convertToDecimal(substring(memory[i].content, 7, 3));
	addr = state->registers[base] + offset;  // data address = base + offset
	
	data_index = memoryFind(memory, addr, num);
	data = convertToDecimal(memory[data_index].content); // find the data in the main memory
	state->registers[reg] = data;  // load the date to the register
	modifyNZP(state, data); // set the NZP
	
}

void ADD(State* state, Memory* memory, int i, long int num){
	long int reg, s1, s2, classify, data;
	reg = convertToDecimal(substring(memory[i].content, 4, 3));
	s1 = convertToDecimal(substring(memory[i].content, 7, 3));
	classify = convertToDecimal(substring(memory[i].content, 10, 1)); // classify two kinds of add instructions

	if(classify == 0){
		s2 = convertToDecimal(substring(memory[i].content, 13, 3));
		state->registers[reg] = state->registers[s1] + state->registers[s2]; // the sum of the values of two source registers
	}else{
		data = convertToDecimal(substring(memory[i].content, 11, 5));
		state->registers[reg] = state->registers[s1] + data; // the sum of the value of one source register and an immediate operand
	}
	modifyNZP(state, state->registers[reg]); // set the NZP
}

void BRp(State* state, Memory* memory, int i, long int num){
	long int p, step;
	p = convertToDecimal(substring(memory[i].content, 6, 1)); // p determines whether to jump
	
	if(p == 0) return; 
	
	step = convertToDecimal(substring(memory[i].content, 7, 9));
	state->pc = state->pc + step; // jump to the destination
}

void STR(State* state, Memory* memory, int i, long int num){
	long int sr, offset, addr, data, base;
	sr = convertToDecimal(substring(memory[i].content, 4, 3));
	base = convertToDecimal(substring(memory[i].content, 7, 3));
	offset = convertToDecimal(substring(memory[i].content, 10, 6));
	
	addr = state->registers[base] + offset;  // data address = base + offset
	data = state->registers[sr];
		
	printf("%lx %ld\n", addr, data);
}