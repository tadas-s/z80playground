; Hello world?!

org 0x0

main:
    nop
    nop
    nop
    nop
    jp main

hello:
    defb "Hello world!", 0
