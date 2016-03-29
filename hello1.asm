; Hello world?!

org 0x100

main:
ld a, 0x1
ld b, 0x2
add a, b
call foo

foo:
ld a, 0
ld b, 0
ret

hello:
defb "Hello world!", 0

