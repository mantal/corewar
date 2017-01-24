.name "HelloWord"
.comment "Hello World!"
_start:

    ld %65, r1 # base value ('A')

    ld %7, r2
    add r1, r2, r3
    aff r3 # H

    ld %4, r2
    add r1, r2, r3
    aff r3 # E

    ld %11, r2
    add r1, r2, r3
    aff r3 # L
    aff r3 # L

    ld %14, r2
    add r1, r2, r3
    aff r3 # O

    ld %32, r4
    aff r4 # space

    ld %22, r2
    add r1, r2, r3
    aff r3 # W

    ld %14, r2
    add r1, r2, r3
    aff r3 # O

    ld %17, r2
    add r1, r2, r3
    aff r3 # R

    ld %11, r2
    add r1, r2, r3
    aff r3 # L

    ld %3, r2
    add r1, r2, r3
    aff r3 # D

    ld %10, r4 # line return
    aff r4 # return