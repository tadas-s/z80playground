#include <stdio.h>
#include <z80ex/z80ex.h>

typedef struct {
    Z80EX_BYTE mem[0xffff];
} MACHINE;

Z80EX_BYTE read_memory(Z80EX_CONTEXT *cpu, Z80EX_WORD addr, int m1_state, void *machine) {
    printf("read_memory: 0x%.4X\n", addr);
    return 0x00;
}

void write_memory(Z80EX_CONTEXT *cpu, Z80EX_WORD addr, Z80EX_BYTE value, void *machine) {
    printf("write_memory:\n");
    // nop!
}

Z80EX_BYTE read_port(Z80EX_CONTEXT *cpu, Z80EX_WORD port, void *machine) {
    printf("read_port:\n");
    return 0x00;
}

void write_port(Z80EX_CONTEXT *cpu, Z80EX_WORD port, Z80EX_BYTE value, void *machine) {
    printf("write_port:\n");
    // nop!
}

Z80EX_BYTE interrupt_vector_read(Z80EX_CONTEXT *cpu, void *machine) {
    printf("interrupt_vector_read:\n");
    return 0x00;
}

int main() {
    Z80EX_CONTEXT *cpu;
    MACHINE machine;

    cpu = z80ex_create(
            read_memory, &machine,
            write_memory, &machine,
            read_port, &machine,
            write_port, &machine,
            interrupt_vector_read, &machine
    );

    for(int i = 0; i < 0xf; i++) {
        z80ex_step(cpu);
    }

    return 0;
}