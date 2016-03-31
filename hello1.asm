; Hello world?!

org 0x0

main:
    nop
    ld a, 10
    ld b, 20
    add a, b
    ld (result), a
    nop
    nop
    nop
    jp main

result:
    defb 0x0

hello:
    defb "Hello world!", 0
