#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL02Z4.h"
#include "fsl_debug_console.h"


#include "sdk_hal_uart0.h"

/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
/*
 * @brief   Application entry point.
 */
int main(void) {
  	/* Init board hardware. */

	SIM->SCGC5|=1<<10;// activa la señal del reloj
	  	int t=0;
	  	int s=10000000;//velocidad de colores

//           para el pin 6, led rojo
	  	PORTB->PCR[6]|=1<<8;//activa puertob pin como gpio
	  	  	GPIOB->PDDR|=1<<6;//configura pin 10 como salida
	  		GPIOB->PCOR|=0<<6;//cambia el valor en el pin
	  		GPIOB->PTOR|=1<<6;
//           para el pin 10 led azul
	  		PORTB->PCR[10]|=1<<8;//activa puertob pin como gpio
	  		  	GPIOB->PDDR|=1<<10;//configura pin 10 como salida
	  			GPIOB->PCOR|=0<<10;//cambia el valor en el pin
	  			GPIOB->PTOR|=1<<10;
//         para el pin 7 led verde
	  			PORTB->PCR[7]|=1<<8;//activa puertob pin como gpio
	  			  	GPIOB->PDDR|=1<<7;//configura pin 10 como salida
	  				GPIOB->PCOR|=0<<7;//cambia el valor en el pin
	  				GPIOB->PTOR|=1<<7;


    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    (void)uart0Inicializar(115200);
unsigned int contador_ledblue=0;
unsigned int contador_ledred=0;
unsigned int contador_ledgreen=0;
    while(1) {
    	status_t status;
    	uint8_t nuevo_byte;

    	if(uart0NuevosDatosEnBuffer()>0){
    		status=uart0LeerByteDesdeBufferCircular(&nuevo_byte);
    		if(status==kStatus_Success){
    			printf("dato:%c\r\n",nuevo_byte);
    			if(nuevo_byte == 'R' && contador_ledred==0){
    			    				GPIOB->PTOR =1<<6;
    			    				contador_ledred=contador_ledred+1;
    			    			}
    			if(nuevo_byte == 'r' && contador_ledred!=0){
    			    			     GPIOB->PTOR =1<<6;
    			    			     contador_ledred=0;
    			} // led rojo
    			if(nuevo_byte == 'G' && contador_ledgreen==0){
    			    GPIOB->PTOR =1<<7;
    			    contador_ledgreen=contador_ledgreen+1;
    			    			    }
    			    if(nuevo_byte == 'g' && contador_ledgreen!=0){
    			     GPIOB->PTOR =1<<7;
    			     contador_ledgreen=0;
    			    } //led verde
    			    if(nuevo_byte == 'B' && contador_ledblue==0){
    			    	GPIOB->PTOR =1<<10;
    			    	contador_ledblue=contador_ledblue+1;
    			    			    			}
    			    	if(nuevo_byte == 'b' && contador_ledblue!=0){
    			          GPIOB->PTOR =1<<10;
    			          contador_ledblue=0;
    			    		}// led azul

    		}else{
    			printf("error\r\n");
    		}
    	}
    }
    return 0 ;
}
