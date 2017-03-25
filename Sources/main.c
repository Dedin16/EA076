/* ###################################################################
**     Filename    : main.c
**     Project     : Sem_Dedin_Caicara
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-03-16, 09:14, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "LED_C_R.h"
#include "BitIoLdd1.h"
#include "LED_C_G.h"
#include "BitIoLdd2.h"
#include "LED_C_Y.h"
#include "BitIoLdd3.h"
#include "LED_P_R.h"
#include "BitIoLdd4.h"
#include "LED_P_G.h"
#include "BitIoLdd5.h"
#include "PUSH_BOTTON.h"
#include "ExtIntLdd1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "AD1.h"
#include "AdcLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"


volatile char tempo=0;
volatile char estado=0;

int main(void){
  int i=0, pomba=0;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /*Estado inicial*/
  LED_C_G_PutVal(0); // Carro_Green 
  LED_C_Y_PutVal(1); // Carro_Yellow 
  LED_C_R_PutVal(1); // Carro_Red 
  LED_P_G_PutVal(1); // Pedestre_Green 
  LED_P_R_PutVal(0); // Pedestre_Red
  TI1_Enable();		//comeca contagem
  static uint16_t value=0;
  
  (void)AD1_Measure(TRUE);
  (void)AD1_GetValue16(&value);
  	  
  for(;;){
	  	  
	  if(estado==0){
		  
		  if(tempo>=10){
			  (void)AD1_Measure(TRUE);
			  (void)AD1_GetValue16(&value);
			  tempo=0;	
			  
			  if(value<=20000){
				  pomba++;
			  }
			  
			  if(value>=30000){
				  pomba=0;
			  }
		  }
		  
		  if(pomba>1){
			  estado=2;
			  PUSH_BOTTON_Disable();
			  pomba=0;
		  }
	  }
	  
	  if(estado==1){
		  
		  /*Tempo para os carros*/
		  tempo=0;
		  while(tempo<=20){} //espera 10 segundos
		  
		  /*Amarelo para carro*/
		  tempo=0;
		  LED_C_G_PutVal(1);
		  LED_C_Y_PutVal(0);
		  while(tempo<=10){} //espera 5 segundos
		  
		  /*Vermelho para carro*/
		  tempo=0;
		  LED_C_Y_PutVal(1);
		  LED_C_R_PutVal(0);
		  LED_P_R_PutVal(1);
		  LED_P_G_PutVal(0);
		  while(tempo<=40){} //espera 20 segundos
		  		  
		  /*Vermelho piscante para pedestre*/
		  LED_P_G_PutVal(1);
		  for(i=0;i<4;i++){		//4 segundos
			  tempo=0;
			  LED_P_R_NegVal(); //Acende
			  while(tempo<1){};
			  LED_P_R_NegVal(); //Apaga
			  while(tempo<2){}
			  
		  }
		  estado=0;
		  LED_P_R_PutVal(0);
		  LED_C_R_PutVal(1);
		  LED_C_G_PutVal(0);
		  tempo=0;
	  }
	  
	  if(estado==2){
		  
		  LED_C_G_PutVal(1);	//Carro verde apaga
		  
		  for(i=0;i<5;i++){		//10 segundos
			  tempo=0;
			  LED_C_Y_NegVal(); //Acende
			  while(tempo<2){};
			  LED_C_Y_NegVal(); //Apaga
			  while(tempo<4){}
			  
		  }
		  
		  (void)AD1_Measure(TRUE);
		  (void)AD1_GetValue16(&value);
			  
		  if(value>=30000){
			  estado=0;
			  PUSH_BOTTON_Enable();
			  LED_C_Y_PutVal(1);
			  LED_C_G_PutVal(0);
		  }		  
	  }
	  
  }
  
    
  
  
  
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
    
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/



