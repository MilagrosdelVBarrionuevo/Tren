#include "chip.h"
#include "uart_config.h"

void Inicializar_UART1(void) {
    // Configurar pines TXD1 (P0.15)->J6-13 y RXD1 (P0.16)->J6-14
    Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 15, IOCON_FUNC1); // TXD1->FUNC1 usa el pin modo uart
    Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 16, IOCON_FUNC1); // RXD1->FUNC1 usa el pin modo uart

    // Inicializar UART1
    Chip_UART_Init(LPC_UART1); //Inicia el hardware del uart
    Chip_UART_SetBaud(LPC_UART1, 9600); //Selecciona velocidad de la conexion
    Chip_UART_ConfigData(LPC_UART1, UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS);//8 datos, 1 stop, No paridad
    Chip_UART_SetupFIFOS(LPC_UART1, UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS); //Configurar Buffer y borrar datos residuales
    Chip_UART_TXEnable(LPC_UART1);//Inicia la transferencia del UART
}

