.name "Stinator"
.comment "STOOOOOORE!"
_start:
    ld %11328510, r4 ; ACDBFE
    st r4, -5 ; store the ld value at his own position
    ld %0, r1
    zjmp %:_start