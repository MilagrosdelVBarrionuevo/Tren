#include "chip.h"
#include "enviar_dato.h"

void Enviar_Cadena_UART1(const char *str) {
    while (*str) {
        while ((Chip_UART_ReadLineStatus(LPC_UART1) & UART_LSR_THRE) == 0);
        Chip_UART_SendByte(LPC_UART1, *str++);
    }
}
