#ifndef _APP_H
#define _APP_H

/* Main settings */

/*comment below line for release*/

#define TESTING

#define EEPROM_DISPLAY				0

/******** MAIN CONFIGURATION ENDS ****************/

/* LCD CONFIGURATION */
#define LCD_DDR           	   		DDRB 
#define LCD_DATA_PORT          		PORTB
#define LCD_ENABLE_PIN        		PB3 
#define LCD_REGISTER_SELECT_PIN     PB2
#define DISPLAY_INIT				1
#define LCD_NSCRL					1
#define FLOAT_T0_STRING				1
#define DECIMAL_PRECISION			100

/******** LCD CONFIGURATION ENDS ****************/

/* BUZZER: CONFIGURATION */
#define	BUZ_DDR						DDRC
#define	BUZ_PORT					PORTC
#define	BUZ_PIN						PC1
#define OFF_TIME					100
/******** BUZZER CONFIGURATION ENDS ****************/

/* LED: CONFIGURATION */

#define	LED_DDR			DDRC
#define	LED_PORT		PORTC
#define	LED_PIN			PC0

#define OFF_TIME		100
/******** LED CONFIGURATION ENDS ****************/

/* GSM: CONFIGURATION */

#ifdef TESTING
	#define RPhNum	"9980237552"
#else
	#define RPhNum	"8884376238"
#endif

#define MSG_START			""
#define MSG_END				". Automated SMS By: SG"

/******** GSM CONFIGURATION ENDS ****************/

/******** MOTOR CONFIGURATION   ****************/
#define MOT_PORT			PORTC
#define MOT_DDR				DDRC
#define MOT1_AN				PC2
#define MOT1_CA				PC3
#define MOT2_AN				PC4
#define MOT2_CA				PC5
/******** MOTOR CONFIGURATION ENDS  ****************/

/******** PWM CONFIGURATION  *******************/
#define PWM_DDR				DDRD
#define PWM_PIN				PD7
/********  PWM CONFIGURATION ENDS **************/

/******** ADC CONFIGURATION		 *******************/
#define REF_VOL_256	
/******** ADC CONFIGURATION  ENDS *******************/

/********* SWITCH CONFIGURATION   ***************/

#define SWITCH_DDR	DDRA
#define SWITCH_PORT	PORTA
#define SWITCH_PIN	PINA
#define SWITCH1_BIT	PA4
#define SWITCH2_BIT	PA5
#define SWITCH3_BIT	PA6
#define SWITCH4_BIT	PA7


#define Switch1Pressed()	bit_is_clear(SWITCH_PIN, SWITCH1_BIT)
#define Switch2Pressed()	bit_is_clear(SWITCH_PIN, SWITCH2_BIT)
#define Switch3Pressed()	bit_is_clear(SWITCH_PIN, SWITCH3_BIT)
#define Switch4Pressed()	bit_is_clear(SWITCH_PIN, SWITCH4_BIT)

/********* SWITCH CONFIGURATION ENDS  ***************/
#endif
