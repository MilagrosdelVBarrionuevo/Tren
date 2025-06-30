#include "chip.h"
#include "control_led.h"

#define A1_PORT 0
#define A1_PIN 22 //mcuexpresso pin (J6-24) (Humificador)
#define B1_PORT 0
#define B1_PIN 3 //mcuexpresso pin J6-22 (Led Tren)

void Inicializar_A1(void) {
    Chip_IOCON_PinMuxSet(LPC_IOCON, A1_PORT, A1_PIN, IOCON_FUNC0 | IOCON_MODE_INACT); // Chip_IOCON_PinMuxSet -> configuracion del modo del pin
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, A1_PORT, A1_PIN); //Chip_GPIO_SetPinDIROutput configura el pin en esa direecion como salida
    Chip_GPIO_SetPinState(LPC_GPIO, A1_PORT, A1_PIN, false);  // Inicia el led apagado
}
void Inicializar_B1(void) {
    Chip_IOCON_PinMuxSet(LPC_IOCON, B1_PORT, B1_PIN, IOCON_FUNC0 | IOCON_MODE_INACT);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, B1_PORT, B1_PIN);
    Chip_GPIO_SetPinState(LPC_GPIO, B1_PORT, B1_PIN, false);
}

void Encender_A1(void) {
    Chip_GPIO_SetPinState(LPC_GPIO, A1_PORT, A1_PIN, true); //Enciende el LED
}

void Apagar_A1(void) {
    Chip_GPIO_SetPinState(LPC_GPIO, A1_PORT, A1_PIN, false);
}

void Encender_B1(void) {
    Chip_GPIO_SetPinState(LPC_GPIO, B1_PORT, B1_PIN, true);
}

void Apagar_B1(void) {
    Chip_GPIO_SetPinState(LPC_GPIO, B1_PORT, B1_PIN, false);
}
