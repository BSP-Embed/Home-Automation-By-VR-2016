#ifndef MAIN_H
#define MAIN_H

#include "includes.h"

#define INTDDR				DDRD
#define INTPORT				PORTD
#define INT0_PIN			PD2
#define INT1_PIN			PD3

#define RELAY_DDR			DDRA
#define RELAY_PORT			PORTA
#define LIGHT_PIN			PA0
#define FAN_PIN				PA1
#define CHARGER_PIN			PA2


//DEFINE CONSTANT
#define	INFO_EE_ADDR		0x01

#define DELTA				4			

enum {VOICE = 1, CTRL};

//DEFINE MACROS
#define StartTmr()			TCCR0  	|= _BV(CS01)
#define StopTmr()			TCCR0  	&= ~_BV(CS01)

#define LightOn()		RELAY_PORT |= _BV(LIGHT_PIN)
#define LightOff()		RELAY_PORT &= ~_BV(LIGHT_PIN)
#define FanOn()			RELAY_PORT |= _BV(FAN_PIN)
#define FanOff()		RELAY_PORT &= ~_BV(FAN_PIN)
#define ChargerOn()		RELAY_PORT |= _BV(CHARGER_PIN)
#define ChargerOff()	RELAY_PORT &= ~_BV(CHARGER_PIN)


struct  {
	volatile int8u ChkVoi:1;
	volatile int8u Door:1;
	volatile int8u Sw:1;
} Flag;

//FUNCTION PROTOTYPES
static void		 init		(void);
static void 	disptitl 	(void);
static void 	tmr1init	(void);
static void		EXT0init	(void);	
static void		gpioinit	(void);
static void		VoiceTrain	(void);
static void		VoiceErase	(void);
static void		VoiceRecog	(void);

#endif
