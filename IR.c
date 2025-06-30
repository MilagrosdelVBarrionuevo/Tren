#include "board.h"
#include "chip.h"
#include "IR.h"

#define IR_PORT 1
#define IR_PIN 31

void InicializarIR(){

 // Configurar pin del receptor IR como entrada
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, IR_PORT, IR_PIN);
    Chip_IOCON_PinMuxSet(LPC_IOCON, IR_PORT, IR_PIN,
                         (IOCON_MODE_PULLUP | IOCON_FUNC0)); //Configura el pin como entrada y habilita una resitencia PULL-UP interna
    //No necesaria para el caso del sensor IR pero se dejo como recordatorio en caso de otro tipo de sensor que si lo requiera
}

bool DetectaSeñalIR(){ //Lectura del estado del pin
	bool estado = (Chip_GPIO_GetPinState(LPC_GPIO, IR_PORT, IR_PIN) == 0); //estado = 1 si detecta una señal IR
	//La mayoria de sensores IR estan en HIGH cuando no detecta señal
	//Si detecta una señal valida la salida del receptor IR se pone en bajo LOW
	return estado;
}
