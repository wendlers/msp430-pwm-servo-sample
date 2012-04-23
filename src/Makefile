all:	firmware

firmware:	main.c
	msp430-gcc -Os -mmcu=msp430g2553 -g -Wall -Wextra main.c -o firmware

flash:	firmware
	mspdebug rf2500 "prog firmware"

clean:
	if [ -e firmware ]; then rm firmware; fi
