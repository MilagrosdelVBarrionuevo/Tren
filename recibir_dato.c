#include "chip.h"
#include "recibir_dato.h"


uint8_t Recibir_Dato_UART1(void) {
    if (Chip_UART_ReadLineStatus(LPC_UART1) & UART_LSR_RDR) {
        return Chip_UART_ReadByte(LPC_UART1);
    }
    return 0xFF;  // Valor especial si no hay dato
}
