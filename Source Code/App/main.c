#include "main.h"

extern int8u lcdptr;
					
const char *VoiceComm[] = {"Door Open", "Door Close", "Light ON", "Light OFF", "Fan ON", "Fan OFF", "Charger ON","Charger OFF"};
	
int main(void)
{
	init();
	
	while (TRUE) {
		
	if (Flag.ChkVoi) {
		VoiceRecog();
		Flag.ChkVoi =	FALSE;
	}
	
	if(Flag.Sw) {
		Flag.Sw = FALSE;
		VoiceTrain();
	}

	sleep();
		
	}
	return 0;
}
static void VoiceRecog(void)
{
	int8u x;
	
	x = SDRecognize('B')-'A';
	
	if (x <= 7) {
		lcdclr();
		lcdws("Voice Recognized");
		lcdr2();
		lcdws(VoiceComm[x]);
		beep(1,100);
		switch(x) {
			case 0: Flag.Door = TRUE; Forward(); dlyms(5000); Stop(); break;
			case 1: Flag.Door = FALSE; Backward(); dlyms(5000); Stop(); break; 
			case 2: if (Flag.Door) LightOn(); break;
			case 3: LightOff(); break;
			case 4: if (Flag.Door) FanOn(); break;
			case 5: FanOff(); break;
			case 6: if (Flag.Door) ChargerOn(); break;
			case 7: ChargerOff(); break;
		}
		dlyms(DISP_DLY);
		disptitl();
	}
}

static void VoiceTrain(void)
{
	int8u i;
	
	VoiceErase();
	
	lcdclr();
	lcdws("Voice Training");
	beep(1,100);
	
	for (i = 0; i <= 7; i++) {
		lcdclrr(1);
		lcdws(VoiceComm[i]);
		dlyms(1000);
		while (!VrTrain('B', 'A' + i));
		lcdclrr(1);
		lcdws("Success");
	}
	
	beep(2,200);
	disptitl();
}

static void VoiceErase(void)
{
	int8u i;
	
	lcdclr();
	lcdws("Erasing");

	for (i = 0; i <= 7; i++) {
		lcdclrr(1);
		lcdws(VoiceComm[i]);
		beep(2,75);
		while (!EraseTraining('B', 'A' + i));
		lcdclrr(1);
		lcdws("Success");
	}
	
}


static void init(void)
{
	buzinit();
	beep(2,100);
	gpioinit();
	ledinit();
	lcdinit();
	uartinit();
	tmr1init();
	motorinit();
	EXT0init();
		
//	if (VoiceRecognitionInitialize()) {
		//	lcdptr = 0xc5;
		//	setTimeOut();
		//	AddSDComm();
		//	SetLevel();
		//	lcdws("Success");
//	}
	
	disptitl();	
	sei();
		
}

static void gpioinit(void)
{
	RELAY_DDR |= 0x07;
	RELAY_PORT &= ~(0x07);
}

static void disptitl(void)
{ 
	lcdclr();
	lcdws("Home Auto by VR");
}
static void tmr1init(void)
{
	TCNT1H   = 0xD3;
	TCNT1L   = 0x00;
	TIMSK   |= _BV(TOIE1);			//ENABLE OVERFLOW INTERRUPT
	TCCR1A   = 0x00;					
	TCCR1B  |= _BV(CS10) | _BV(CS11); /* PRESCALAR BY 16 */
}

/* overflows at every 100msec */
ISR(TIMER1_OVF_vect) 
{ 
	static int8u i,j,k;

	TCNT1H = 0xD3;
	TCNT1L = 0x00;
	
	if (++i >= 50) i = 0;
	
	switch(i) {
		case 0: case 2: ledon();  break;
		case 1: case 3: ledoff(); break;
	} 
	
	if (++j >= 2) {
		j = 0;
		Flag.ChkVoi = TRUE;
	}
	
}
static void EXT0init(void)
{
	INTDDR 	&= ~_BV(INT0_PIN);
	INTPORT |= _BV(INT0_PIN);

	GICR |= _BV(INT0);			//ENABLE EXTERNAL INTERRUPT
	MCUCR |= _BV(ISC01);		//FALLING EDGE INTERRUPT

}
ISR(INT0_vect)
{
	Flag.Sw = TRUE;
	GICR |= _BV(INT0);
}
