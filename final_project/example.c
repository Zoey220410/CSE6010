#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 65536  // 2^16 for 16-bit addresses

typedef struct {
    char address[17];  // 16 bits + '\0'
    char contents[17]; // 16 bits + '\0'
} MemoryEntry;

typedef struct {
    int reg[8];        // General-purpose registers
    int cc;            // Condition codes: N, Z, P
    int pc;            // Program Counter
} LC3State;

void initializeState(LC3State *state) {
    for (int i = 0; i < 8; i++) {
        state->reg[i] = 0;
    }
    state->cc = 0;
    state->pc = 0;
}

int convertToDecimal(const char *binary) {
    return strtol(binary, NULL, 2);
}

void executeLD(LC3State *state, const MemoryEntry *mem) {
    int offset = convertToDecimal(mem->contents);
    int pcValue = convertToDecimal(state->reg[7]);  // Assuming PC is stored in R7

    int address = pcValue + offset;
    int value = convertToDecimal(mem->address);

    printf("%X %d\n", address, value);
}

// Similar functions for other instructions (LDR, ADD, BRp, STR, FIN)

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    int numMemoryLocations;
    fscanf(file, "%d", &numMemoryLocations);

    MemoryEntry *memory = malloc(numMemoryLocations * sizeof(MemoryEntry));
    if (memory == NULL) {
        perror("Memory allocation error");
        fclose(file);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < numMemoryLocations; i++) {
        fscanf(file, "%16s %16s", memory[i].address, memory[i].contents);
    }

    fclose(file);

    LC3State state;
    initializeState(&state);

    for (int i = 0; i < numMemoryLocations; i++) {
        // Execute instructions based on opcode
        if (strncmp(memory[i].contents, "0001", 4) == 0) {
            executeLD(&state, &memory[i]);
        }
        // Similar checks for other instructions

        // Check if FIN instruction is encountered
        if (strncmp(memory[i].contents, "1101", 4) == 0) {
            break;
        }
    }

    free(memory);

    return EXIT_SUCCESS;
}
