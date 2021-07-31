# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:lab3.elf

#additional rules for files
lab3.elf: ${COMMON_OBJECTS} lab3.o wdt_handler.o switches.o p1_interrupt_handler.o buzzer.o stateMachines.o led.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 
switches.o: switches.h
stateMachines.o: stateMachines.s led.h stateMachines.h
led.o: led.c led.h
buzzer.o: buzzer.h


load: lab3.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
