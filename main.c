#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <z80ex/z80ex.h>

typedef struct {
    Z80EX_BYTE mem[0xffff];
} MACHINE;

void load(const char *filename, void *destination, const int max_len) {
    int flen;
    int read_up_to;
    FILE *fhandle;

    fhandle = fopen(filename, "rb");
    fseek(fhandle, 0, SEEK_END);
    flen = ftell(fhandle);
    rewind(fhandle);

    // TODO:
    //read_up_to = fmin(0xffff, fmax(flen, max_len));
    read_up_to = 0xffff;

    fread(destination, sizeof(Z80EX_BYTE), read_up_to, fhandle);

    fclose(fhandle);
}

Z80EX_BYTE read_memory(Z80EX_CONTEXT *cpu, Z80EX_WORD addr, int m1_state, void *machine) {
    Z80EX_BYTE value;
    value = ((MACHINE *)machine)->mem[addr];
    printf("r %.4X %.2X\n", addr, value);
    return value;
}

void write_memory(Z80EX_CONTEXT *cpu, Z80EX_WORD addr, Z80EX_BYTE value, void *machine) {
    printf("w %.4X %.2X\n", addr, value);
    ((MACHINE *)machine)->mem[addr] = value;
}

Z80EX_BYTE read_port(Z80EX_CONTEXT *cpu, Z80EX_WORD port, void *machine) {
    printf("i \n");
    return 0x00;
}

void write_port(Z80EX_CONTEXT *cpu, Z80EX_WORD port, Z80EX_BYTE value, void *machine) {
    printf("0 \n");
    // nop!
}

Z80EX_BYTE interrupt_vector_read(Z80EX_CONTEXT *cpu, void *machine) {
    printf("interrupt_vector_read:\n");
    return 0x00;
}

int main() {
    Z80EX_CONTEXT *cpu;
    MACHINE machine;

    load("a.bin", machine.mem, 0xffff);

    cpu = z80ex_create(
            read_memory, &machine,
            write_memory, &machine,
            read_port, &machine,
            write_port, &machine,
            interrupt_vector_read, &machine
    );

    for(int i = 0; i < 64; i++) {
        z80ex_step(cpu);
    }

    return 0;
}