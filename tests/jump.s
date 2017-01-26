.name "Jumper"
.comment "JUMP, 2 3 4!"
_start:
    ld %48, r4 # base value ('A')
    ld %5, r2 # carry is 0, so it will jmp
    ld %5, r3
    sub r2, r3, r5
    zjmp %:stage_2
stage_1:
    ld %1, r2
    add r2, r4, r5
    aff r5
stage_2:
    ld %2, r2
    add r2, r4, r5
    aff r5
stage_3:
    ld %3, r2
    add r2, r4, r5
    aff r5
stage_4:
    ld %4, r2
    add r2, r4, r5
    aff r5
