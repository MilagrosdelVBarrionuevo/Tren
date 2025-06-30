#include "chip.h"
#include "pwm.h"

#define CORE_CLK       96000000
#define PWM_FREQUENCY  50
#define PWM_PERIOD     ((CORE_CLK / 4) / PWM_FREQUENCY) //PWM funciona a CCLK/4 por defecto

#define PINSEL4   (*((volatile uint32_t *) 0x4002C010))
#define PWM1PCR   (*((volatile uint32_t *) 0x4001804C))
#define PWM1MR0   (*((volatile uint32_t *) 0x40018018))
#define PWM1MR1   (*((volatile uint32_t *) 0x4001801C)) // PWM1.1 - P2.0 ->J6-42
#define PWM1MR2   (*((volatile uint32_t *) 0x40018020)) // PWM1.2 - P2.1 ->J6-43
#define PWM1TCR   (*((volatile uint32_t *) 0x40018004))
#define PWM1MCR   (*((volatile uint32_t *) 0x40018014))
#define PWM1LER   (*((volatile uint32_t *) 0x40018050)) ////Accede a los registros del pwm1
// PWM1MR1 y MR2 -> definen duty salida
// PWM1TCR -> iniciar-parar-resetear pwm Timer Control Register
//PWM1MCR -> Accion al llegar a un valor limite Match Control Register
//PWM1LER -> Aplicar cambios del MCR Latch Enable Register
//PWM Setup
void habilitar_pwm() {
    //Configurar P2.0 (PWM1.1)
    PINSEL4 &= ~(0x3 << 0); // Limpia bits 0-1 (P2.0)
    PINSEL4 |=  (0x1 << 0); // P2.0 como PWM1.1

    //Configurar P2.1 (PWM1.2)
    PINSEL4 &= ~(0x3 << 2); // Limpia bits 2-3 (P2.1)
    PINSEL4 |=  (0x1 << 2); // P2.1 como PWM1.2

    // Habilita los canales PWM1.1 y PWM1.2
    PWM1PCR |= (1 << 9); // PWM1.1 habilitacion
    PWM1PCR |= (1 << 10); // PWM1.2 habilitacion
    PWM1MCR |= (1 << 1); // Reset on MR0

    // Inicializar Timer y periodo
    PWM1TCR = (1 << 1); // Reset Timer
    PWM1MR0 = PWM_PERIOD; // Periodo base (480000 ->50Hz)

    // Duty al 0% por defecto
    PWM1MR1 = PWM_PERIOD * 0 / 100; //0% duty en PWM1.1
    PWM1MR2 = PWM_PERIOD * 0 / 100; //0% duty en PWM1.2

    PWM1LER |= (1 << 0) | (1 << 1) | (1 << 2); // Latch MR0, MR1, MR2 guardar cambios


    PWM1TCR = (1 << 0) | (1 << 3); // Enable Timer y PWM mode
}

// Duty Cycle para PWM1.1 (P2.0)
void Duty_Cycle(int porcentaje) {
    if (porcentaje < 0) {//Control numero positivo
    	porcentaje = 0;
    }
    if (porcentaje > 100){ //Control maximo
    	porcentaje = 100;
    }//control dyty 0-100%
    PWM1MR1 = PWM_PERIOD * porcentaje / 100;
    PWM1LER |= (1 << 1);  // Latch MR1 aplicar cambio
}

// Duty Cycle para PWM1.2 (P2.1)
void Duty_Cycle_2(int porcentaje) {
    if (porcentaje < 0) porcentaje = 0;
    if (porcentaje > 100) porcentaje = 100;

    PWM1MR2 = PWM_PERIOD * porcentaje / 100;
    PWM1LER |= (1 << 2);  // Latch MR2
}
