#include "chip.h"
#include "uart_config.h"
#include "control_led.h"
#include "board.h"
#include "pwm.h"
#include "recibir_dato.h"
#include "enviar_dato.h"
#include "IR.h"
#include "delay.h"
volatile uint32_t contador = 0;


//////////////// FUNCION PRINCIPAL ////////////////
int main(void) {
Board_Init(); //Iniciar placa y perifericos;

	uint8_t dato; //Variable donde se almacena el dato recibido desde la app
	int marcha=0; //Sentido de giro motor
    int estado = 0; //Apagar-Encender tren
	bool estadoAnterior = true; //Verificar si se detecta una señal IR
	bool barrera=0; //Variable booleana que almacena el valor leido por el sensor IR
    Inicializar_A1(); //Inicializa el pin P0.22 del lpc - Humificador
    Inicializar_B1(); //Inicializa el pin P0.3 del lpc - LED Tren
    Inicializar_UART1(); //Configurar e Iniciar la comunicacion uart
    habilitar_pwm();
    Duty_Cycle(0); //Inicio apagado salidaA puente H apagada
    Duty_Cycle_2(0); //Inicio apagado salidaB puente H apagada
    InicializarIR(); //Iniciar y configurar pines del led IR
    SystemCoreClockUpdate(); //Actualiza la frecuencia a la que esta trabajando el CPU

    //Bucle infinito
    while (1) {

    	dato = Recibir_Dato_UART1();//RECIBIR DATO BT
        barrera = DetectaSeñalIR(); //RECIBIR DATO SENSOR IR

////////// APAGAR TREN //////////
    if (dato == '0') { //
        //apagar motor
        Duty_Cycle(0);
        Duty_Cycle_2(0);
        //apagar humificador y led tren
        Apagar_A1();//off humificador
        Apagar_B1();//off led
        estado=0; //estado del tren


           }
////////// TREN ENCENDIDO //////////
     else if (dato == '1') {
    	estado = 1; //tren Activo
        Encender_B1();//encender led

           }
    ////////// HUMIFICADOR //////////
     if (dato == 'H' && estado == 1) {
                  Encender_A1();
                  delay_ms(100);
                  Apagar_A1();


                   }
    ////////// NORMAL //////////
          if (dato == 'F') {
              marcha = 1;
               }
    ////////// REVERSA //////////
          else if(dato == 'R'){
        	marcha = 0;
               }

        ///////// Marcha Nomal /////////

        ///////// CONTROL VELOCIDAD /////////
        if(estado == 1 && marcha == 1 ){
        	if (estadoAnterior && !barrera) {//Control deteccion de señal IR
        	    Enviar_Cadena_UART1("B");//Enviar dato a la app para sumar una vuelta
        	    delay_ms(100); //Evitar señales multiples
        	   }
        	estadoAnterior = barrera;

            if (dato == 'A') {
                Duty_Cycle(19); //10% app
          		Duty_Cycle_2(0);
          		}
        	if (dato == 'B') {
                Duty_Cycle(35); //20% app
              	Duty_Cycle_2(0);
              	}
        	if (dato == 'C') {
                Duty_Cycle(50); //50% app
              	Duty_Cycle_2(0);
               }
        	if (dato == 'D') {
                Duty_Cycle(100); //100% app
                Duty_Cycle_2(0);
               }
     }


         ///////// REVERSA /////////

         ///////// CONTROL VELOCIDAD /////////
         if(estado == 1 && marcha == 0 ){
            if (estadoAnterior && !barrera) {
                Enviar_Cadena_UART1("NB");//Enviar dato a la app para restar una vuelta
                delay_ms(100);
               }
            estadoAnterior = barrera;

            if (dato == 'A') {
                Duty_Cycle(0);
                Duty_Cycle_2(19);
               }
            if (dato == 'B') {
                Duty_Cycle(0);
                Duty_Cycle_2(25);
               }
            if (dato == 'C') {
            	Duty_Cycle(0);
                Duty_Cycle_2(50);
               }
            if (dato == 'D') {
                Duty_Cycle(0);
                Duty_Cycle_2(100);
               }
            }

      }
    return 0;
}
