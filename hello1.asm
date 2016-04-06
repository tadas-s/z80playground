; Hello world?!

org 0x0000

main:
    ld c, 0x00
    ld a, 0x58
    out (c), a
    ld a, 0x58
    out (c), a
    ld a, 0x59
    out (c), a
    ld a, 0x60
    out (c), a
    jp main

result:
    defb 0x0

hello:
    defb "Hello world!", 0
