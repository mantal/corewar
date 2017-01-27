.name "Test 6"
.comment ""
_start:
test\:
zjmp %:_start:
	add r12, r5, r3
	zjmp %:test\
	zjmp %:not_found
