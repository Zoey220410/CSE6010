#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    char address[17];  // 16 bits + '\0'
    char content[17]; // 16 bits + '\0'
} Memory;

typedef struct {
    long int registers[8];        // General-purpose registers
    int cc;            // Condition codes: N(-1), Z(0), P(1)
    long int pc;            // Program Counter
} State;

void initialState(State* state);
long int convertToDecimal(const char *binary_ori);
long int memoryFind(Memory* memory, long int address, long int num);
long int substring(const char* str, int start_index, int length);
void modifyNZP(State* state, long int data);

void LD(State* state, Memory* memory, int i, long int num);
void LDR(State* state, Memory* memory, int i, long int num);
void ADD(State* state, Memory* memory, int i, long int num);
void BRp(State* state, Memory* memory, int i, long int num);
void STR(State* state, Memory* memory, int i, long int num);