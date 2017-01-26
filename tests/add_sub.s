.name "Addinator"
.comment "Addition unit test"
_start:
    ld %48, r2 # '0'
    add r2, r1, r3 # '0' + id
    aff r3 ; program id
    sub r1, r1, r1 # should be always 0
    add r2, r1, r3
    aff r3 # should be '0'
