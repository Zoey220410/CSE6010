#include "instructions.h"

int main(int argc, char *argv[]) {
	FILE *file = fopen(argv[1], "r");
	
	long int num, i;
	i = 0;
    fscanf(file, "%ld", &num);
	Memory* memory = (Memory*) malloc(num * sizeof(Memory));
	
	for(int i=0; i<num; i++){
		fscanf(file, "%s %s", memory[i].address, memory[i].content);
	}
	
	fclose(file);
	
	State* state = (State*) malloc(sizeof(State));
	initialState(state);
	
	while(state->pc < num) {
		i = state->pc;
		state->pc = state->pc + 1;
		
        /* Execute instructions based on opcode*/
		//LD
        if (strncmp(memory[i].content, "0010", 4) == 0) {
            LD(state, memory, i, num);
        }
        // LDR
		else if (strncmp(memory[i].content, "0110", 4) == 0) {
			LDR(state, memory, i, num);
        }
		// ADD
		else if (strncmp(memory[i].content, "0001", 4) == 0) {
			ADD(state, memory, i, num);
        }
		//BRp
		else if (strncmp(memory[i].content, "0000", 4) == 0) {
			BRp(state, memory, i, num);
        }
		//STR
		else if (strncmp(memory[i].content, "0111", 4) == 0) {
			STR(state, memory, i, num);
        }
        // FIN
        else if (strncmp(memory[i].content, "1101", 4) == 0) {
			break;
        }
    }
	
	free(memory);
	free(state);
	
	return 0;		
}