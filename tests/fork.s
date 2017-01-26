.name "Forkinator"
.comment "Forkinator"

_start:	sti r1,%:live,%1
		and r1,%0,r1
live:	live %1
        fork %:live
		zjmp %:live
