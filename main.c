#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <z80ex/z80ex.h>

typedef struct {
    // Just a 64kb chunk, everything is writeable
    Z80EX_BYTE mem[0xffff];
} MACHINE;

void console_output(Z80EX_BYTE value) {
    printw("%c", value);
}

uint8_t console_input_available(MACHINE *machine) {
    return 0;
}

Z80EX_BYTE console_input_read(MACHINE *machine) {
    return 0x00;
}

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
    printw("r %.4X %.2X\n", addr, value);
    return value;
}

void write_memory(Z80EX_CONTEXT *cpu, Z80EX_WORD addr, Z80EX_BYTE value, void *machine) {
    printw("w %.4X %.2X\n", addr, value);
    ((MACHINE *)machine)->mem[addr] = value;
}

Z80EX_BYTE read_port(Z80EX_CONTEXT *cpu, Z80EX_WORD port, void *machine) {
    Z80EX_BYTE value;

    switch (port) {
        case 0xff00: value = console_input_available(machine); break;
        case 0xff01: value = console_input_read(machine); break;
        default: value = 0x00; break;
    }

    printw("i %.4X %.2X\n", port, value);

    return value;
}

void write_port(Z80EX_CONTEXT *cpu, Z80EX_WORD port, Z80EX_BYTE value, void *machine) {
    printw("o %.4X %.2X\n", port, value);

    switch (port) {
        case 0xff00: console_output(value); break;
        default: break;
    }
}

Z80EX_BYTE interrupt_vector_read(Z80EX_CONTEXT *cpu, void *machine) {
    printw("interrupt_vector_read:\n");
    return 0x00;
}

int main() {
    Z80EX_CONTEXT *cpu;
    MACHINE machine;

    initscr();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);

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
        refresh();
    }

    sleep(5);
    endwin();
    return 0;
}