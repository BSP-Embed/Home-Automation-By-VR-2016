//include .h file 
#include"vr.h"

//Global Variables
unsigned char Position = 0x40;

//functions
unsigned char VoiceRecognitionInitialize(void)
{
	do {
		putchar ('b');
	}while (getchar() != 'o');
	
	return 1;
	
}
void SetLevel(void)
{
	putchar('v');
	putchar('B');
	
	while (getchar() != 'o');
	
}

static void SelectIndex(void)
{
	unsigned char Index;

	lcdr2();
	lcdws("SW2 TO INDEX NO.");
	dlyms(1000);
	
	for(;;)
	{
		if(Switch2Pressed())
		{
			if(Position++ == 0x4A)
				Position = 0x41;
			Index = Position - 0x41; 
			lcdr2();
			lcdws(" INDEX No.=");
			lcdwint(0xCB, Index);
			lcdws("     ");
			dlyms(200);
		}

		if(Switch1Pressed())
			break;
	}
}
int8u VrTrain(char GroupID, int8u index)
{
		lcdr2();
		lcdws("  Speak Now...  ");
		lcdr2();

		switch(TrainCommand(GroupID, index))
		{
			case 0x74:
			lcdws("    Time Out    ");
			dlyms(1000);
			return (0);
			break;

			case 0x65:
			lcdws("      ERROR     ");
			dlyms(1000);
			return (0);
			break;
			
			case 0x6F:
			case 0x73:
			lcdws("                ");
			dlyms(500);
			return (1);
			break;

			case 0x72:
			default:
			lcdws("                ");
			dlyms(500);
			return (0);
			break;
		}
		
}
static unsigned char SpeakNow(void)
{
	lcdr2();
	lcdws("  Speak Now...  ");
	lcdr2();

	switch(TrainCommand('B', Position))
	{
		case 0x74:
			lcdws("    Time Out    ");
			dlyms(1000);
			return (0);
			break;

		case 0x65:
			lcdws("      ERROR     ");
			dlyms(1000);
			return (0);
			break;
			
	case 0x6F:
	case 0x73:
			lcdws("                ");
			dlyms(500);
			return (1);
			break;	

		case 0x72:
		default:
			lcdws("                ");
			dlyms(500);
			break;
	}
}
void setTimeOut(void)
{
	do {
	putchar ('o');
	dlyms(10);
	putchar ('D');					/* 5 seconds */
	}while (getchar() != 'o');
	
}

void AddSDComm(void)
{
	puts("gBA");
	while (getchar() != 'o');
	
//	puts("gDBDBSP");
//	while (getchar() != 'o');
}

static unsigned char TrainCommand(unsigned char GroupIndex, unsigned char Position)
{

	putchar(CMD_TRAIN_SD);		//ascii value 't' to train command
	putchar(GroupIndex);		//Group Number range ascii A to Q
	putchar(Position); 
	
	return (getchar());
}


unsigned char SDRecognize(unsigned char GroupIndex)
{
	unsigned char SerialData;	

	putchar(CMD_RECOG_SD);		//ascii value 'd' to recognize command
	putchar(GroupIndex);		//Group Number ascii characters A to Q
	
	if((SerialData = getchar()) == STS_RESULT) 
	{
		dlyms(200);
		putchar(' ');
		return (getchar());
	}
	else
		return (SerialData);
}

/****************************** ERASE TRAINING **************************/

unsigned char VoiceEraseTraining(void)
{
	lcdclr();
	lcdws(" ERASE TRAINING ");
	dlyms(1000);
	
	
	SelectIndex();

	if(EraseTraining('B', Position))
	{
		lcdr2();
		lcdws("     SUCCESS    ");
		dlyms(1000);
		return (1);
	}
	else
	{
		lcdr2();
		lcdws("      FAIL      ");
		dlyms(1000);
		return (0);
	}	
}

unsigned char EraseTraining(unsigned char GroupIndex, unsigned char Position)
{
	putchar(CMD_ERASE_SD);		//ascii value to erase training of command
	putchar(GroupIndex);		//Group Number range ascii A to Q
	putchar(Position);

	if(getchar() == STS_SUCCESS)
		return (1);
	else
		return (0);	
}