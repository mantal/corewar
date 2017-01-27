.name "Tork"
.comment "Basic living reporting his number"
_start:
    sti r1, %:live, %1 # store the program id
    ldi %:live, %1, r1 # retrieve the program id
    ld %48, r2 # load '0'
    add r2, r1, r3 # '0' + program id
    aff r3 # program id
	and r1, %0, r1
live:
    live %1 # replaced by the program value
    zjmp %:live
