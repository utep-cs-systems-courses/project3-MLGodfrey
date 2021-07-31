#include "lcddraw.h"
#include "switches.h"
#include "lcdutils.h"
#include "stateMachines.h"
#include "buzzer.h"

	.arch msp430g2553
	.p2align 1,0

	.text
	.global state_advance
	.global state
	.extern my_color
	.extern COLOR_RED
	.extern COLOR_YELLOW
	.extern COLOR_BLACK
	.extern COLOR_BROWN

state:
	.word 0
jt:
	.word case_1
	.word case_2
	.word case_3
	.word case_4

state_advance:
	mov &state, r12
	add r12, r12
	mov jt(r12), r0

case_1://didn't bother with buzzer, doesn't work in .c file anyways
	mov &COLOR_RED, &my_color
	jmp end
case_2:
	mov &COLOR_YELLOW, &my_color
	jmp end
case_3:
	mov &COLOR_BLACK, &my_color
	jmp end
case_4:
	mov &COLOR_BROWN, &my_color //again, actually changes color to pink
	jmp end
end:
	pop r0
