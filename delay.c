#include "chip.h"
#include "delay.h"
void delay_ms(uint32_t ms) {
    // clock de 100 MHz
    for (uint32_t i = 0; i < ms * 50000; i++) {
        __NOP();//Procesador sin hacer nada
    }
}
