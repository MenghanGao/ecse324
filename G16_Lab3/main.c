#include <stdio.h>
#include "./drivers/inc/LEDs.h"
#include "./drivers/inc/slider_switches.h"
#include "./drivers/inc/pushbuttons.h"
#include "./drivers/inc/HEX_displays.h"

int main() {
    while (1) {
		int readInteger = read_slider_switches_ASM(); 
		int toHEXDisplays = read_PB_data_ASM() & 0x0000000F; // 0b1111 
		char readChar = (char)(readInteger & 0x0000000F); 
		int isClear = readInteger & 0x00000200; // 0b1000000000
		if (isClear) {
			HEX_clear_ASM(HEX0 | HEX1 | HEX2 | HEX3 | HEX4 | HEX5); // 0b111111
		} else {
			HEX_flood_ASM(HEX4 | HEX5); 
			HEX_write_ASM(toHEXDisplays, readChar); 
		}
		write_LEDs_ASM(readInteger);
	} 
    return 0; 
}
