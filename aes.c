#include<stdio.h>
//#include <time.h>	
int flag = 0, start=0;
char plaintext[16];
int counter = 0, count=0;
int rounds = 1;
unsigned char mtrkey[16];
FILE *fp;
unsigned char statearray[4][4];
unsigned char roundkey[4][4];
unsigned char sbox[16][16] = {{0x63,0x7C,0x77,0x7B,0xF2,0x6B,0x6F,0xC5,0x30,0x01,0x67,0x2B,0xFE,0xD7,0xAB,0x76},
		    {0xCA,0x82,0xC9,0x7D,0xFA,0x59,0x47,0xF0,0xAD,0xD4,0xA2,0xAF,0x9C,0xA4,0x72,0xC0},
		    {0xB7,0xFD,0x93,0x26,0x36,0x3F,0xF7,0xCC,0x34,0xA5,0xE5,0xF1,0x71,0xD8,0x31,0x15},
		    {0x04,0xC7,0x23,0xC3,0x18,0x96,0x05,0x9A,0x07,0x12,0x80,0xE2,0xEB,0x27,0xB2,0x75},
		    {0x09,0x83,0x2C,0x1A,0x1B,0x6E,0x5A,0xA0,0x52,0x3B,0xD6,0xB3,0x29,0xE3,0x2F,0x84},
		    {0x53,0xD1,0x00,0xED,0x20,0xFC,0xB1,0x5B,0x6A,0xCB,0xBE,0x39,0x4A,0x4C,0x58,0xCF},
		    {0xD0,0xEF,0xAA,0xFB,0x43,0x4D,0x33,0x85,0x45,0xF9,0x02,0x7F,0x50,0x3C,0x9F,0xA8},
		    {0x51,0xA3,0x40,0x8F,0x92,0x9D,0x38,0xF5,0xBC,0xB6,0xDA,0x21,0x10,0xFF,0xF3,0xD2},
		    {0xCD,0x0C,0x13,0xEC,0x5F,0x97,0x44,0x17,0xC4,0xA7,0x7E,0x3D,0x64,0x5D,0x19,0x73},
		    {0x60,0x81,0x4F,0xDC,0x22,0x2A,0x90,0x88,0x46,0xEE,0xB8,0x14,0xDE,0x5E,0x0B,0xDB},
		    {0xE0,0x32,0x3A,0x0A,0x49,0x06,0x24,0x5C,0xC2,0xD3,0xAC,0x62,0x91,0x95,0xE4,0x79},
		    {0xE7,0xC8,0x37,0x6D,0x8D,0xD5,0x4E,0xA9,0x6C,0x56,0xF4,0xEA,0x65,0x7A,0xAE,0x08},
		    {0xBA,0x78,0x25,0x2E,0x1C,0xA6,0xB4,0xC6,0xE8,0xDD,0x74,0x1F,0x4B,0xBD,0x8B,0x8A},
		    {0x70,0x3E,0xB5,0x66,0x48,0x03,0xF6,0x0E,0x61,0x35,0x57,0xB9,0x86,0xC1,0x1D,0x9E},
		    {0xE1,0xF8,0x98,0x11,0x69,0xD9,0x8E,0x94,0x9B,0x1E,0x87,0xE9,0xCE,0x55,0x28,0xDF},
		    {0x8C,0xA1,0x89,0x0D,0xBF,0xE6,0x42,0x68,0x41,0x99,0x2D,0x0F,0xB0,0x54,0xBB,0x16}};
void input()
{
	int ii;
	//printf("In input()\n");
	if(start==0)
	{
		fp = fopen("Plain_Text_Input.txt", "r");
		start=9;
		ii=0;
	}
	else
		ii=1;
	if(flag==1)
		fclose(fp);
	else
	{
		for(;ii<16;ii++)
		{
			plaintext[ii] = fgetc(fp);
			if(plaintext[ii]==EOF)
			{
				flag=1;
				break;
			}
		}
		//Printing Plain Text
		for(int i=0;i<16;i++)
			printf("%c",plaintext[i]);
		printf("\n");
		//Initialising statearray with plaintext
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++,count++)
			{
				
				statearray[j][i] = plaintext[count];
			}	
		}
		plaintext[0] = fgetc(fp);
		if(plaintext[0]==EOF)
		{
			flag=1;
		}
		/*printf("Printing Plain Text in hexadecimal form :\n");
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				printf("%X ",statearray[i][j]);
			}
			printf("\n");
		}*/
		/*
		//Printing statearray in character form :
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				printf("%c ",statearray[i][j]);
			}
			printf("\n");
		}
		*/
	}
}
void masterkey()
{
	int count = 0;
	if(counter == 0)
	{printf("Enter the masterkey : ");
	gets(mtrkey);counter++;}
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++,count++)
		{
			roundkey[j][i] = mtrkey[count];
		}	
	}
	//for(int i=0;i<16;i++)
	//	printf("%c",mtrkey[i]);
	//printf("\n");
/*	printf("Printing masterkey in hexadecimal form :\n");
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			printf("%X ",roundkey[i][j]);
		}
		printf("\n");
	}*/
}
void addroundkey()
{
	/*
	printf("Statearray before add Round function :\n");
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			printf("%X ",statearray[i][j]);
		}
		printf("\n");
	}
	*/
	//Performing add round function
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			statearray[i][j]^= roundkey[i][j];
		}
	}
	/*
	printf("Statearray after add Round function :\n");
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			printf("%X ",statearray[i][j]);
		}
		printf("\n");
	}
	*/
}
void subbyte()
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			statearray[i][j]= sbox[statearray[i][j]>>4][statearray[i][j]&0x0F];
		}
	}
	/*
	printf("Printing statearray after s-box substitution :\n");
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			printf("%X ",statearray[i][j]);
		}
		printf("\n");
	}
	*/
}
void shiftrow()
{
	for(int i=1;i<4;i++)
	{
		for(int k=0;k<i;k++)
		{
			int temp = statearray[i][0];
			for(int j=0;j<3;j++)
			{
				statearray[i][j] = statearray[i][j+1];
			}
			statearray[i][3] = temp;
		}
	}
	/*
	printf("Printing statearray after row shift : \n");
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			printf("%X ",statearray[i][j]);
		}
		printf("\n");
	}
	*/
}
void mixcolm()
{
	unsigned char statearray1[4][4];
	for(int i=0;i<4;i++)
	{
		statearray1[0][i] = (((statearray[0][i]>0x80?(statearray[0][i]<<1)^0x1B:statearray[0][i]<<1))^((statearray[1][i]>0x80?(statearray[1][i]<<1)^0x1B:statearray[1][i]<<1)^statearray[1][i])^(statearray[2][i])^(statearray[3][i]))&0x0FF;
		statearray1[1][i] = ((statearray[0][i])^((statearray[1][i]>0x80?(statearray[1][i]<<1)^0x1B:statearray[1][i]<<1))^((statearray[2][i]>0x80?(statearray[2][i]<<1)^0x1B:statearray[2][i]<<1)^statearray[2][i])^(statearray[3][i]))&0x0FF;
		statearray1[2][i] = ((statearray[0][i])^(statearray[1][i])^((statearray[2][i]>0x80?(statearray[2][i]<<1)^0x1B:statearray[2][i]<<1))^((statearray[3][i]>0x80?(statearray[3][i]<<1)^0x1B:statearray[3][i]<<1)^statearray[3][i]))&0x0FF;
		statearray1[3][i] = (((statearray[0][i]>0x80?(statearray[0][i]<<1)^0x1B:statearray[0][i]<<1)^statearray[0][i])^(statearray[1][i])^(statearray[2][i])^((statearray[3][i]>0x80?(statearray[3][i]<<1)^0x1B:statearray[3][i]<<1)))&0x0FF;
	}
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			statearray[i][j] = statearray1[i][j];
		}
	}	
	/*
	printf("Printing statearray after mix column : \n");
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			printf("%X ",statearray[i][j]);
		}
		printf("\n");

	}
	*/
}
void g()
{
	//Shifting the 4th column words upwards
	int temp = roundkey[0][3];
	for(int i=0;i<3;i++)
	{
		roundkey[i][3] = roundkey[i+1][3];
		
	}
	roundkey[3][3] = temp;
	/*
	printf("\nArray after Left Shift :\n");
	for(int i =0;i<4;i++)
	{
		printf("%X ",roundkey[i][3]);
	}
	*/
	//Performing S-box substitution 
	for(int i=0;i<4;i++)
	{
		roundkey[i][3] = sbox[roundkey[i][3]>>4][roundkey[i][3]&0x0F];
	}
	/*
	printf("\nArray after S-byte substitution :\n");
	for(int i =0;i<4;i++)
	{
		printf("%X ",roundkey[i][3]);
	}
	*/
	int RC[10] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1B,0x36};
	//Performing Xor with RC
	roundkey[0][3]^=RC[rounds-1];
	/*
	printf("\n%X ",RC[rounds-1]);
	printf("\nArray after Xor with RC :\n");
	for(int i =0;i<4;i++)
	{
		printf("%X ",roundkey[i][3]);
	}
	printf("\n");
	printf("Roundkey after g function : \n"); 
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			printf("%X ",roundkey[i][j]);
		}
		printf("\n");
	}
	*/
}
void keyexpansion()
{
	unsigned char w4[4] = {roundkey[0][3],roundkey[1][3],roundkey[2][3],roundkey[3][3]};	
	g();
	//Finding new 1st column of roundkey
	for(int i=0;i<4;i++)
	{
		roundkey[i][0]^= roundkey[i][3];
	}
	/*
	printf("Roundkey after altering 1st column : \n");	
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			printf("%X ",roundkey[i][j]);
		}
		printf("\n");
	}
	*/
	//Finding new 2nd,3rd column of roundkey
	for(int j=1;j<3;j++)
	{
		for(int i=0;i<4;i++)
		{
			roundkey[i][j]= roundkey[i][j-1]^roundkey[i][j];
		}
		/*
		printf("Change :\n");	
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				printf("%X ",roundkey[i][j]);
			}
			printf("\n");
		}
		*/
	}
	//Finding new 4th column of roundkey 
	for(int i=0;i<4;i++)
	{
		roundkey[i][3]= roundkey[i][2]^w4[i];
	}
	/*	
	printf("Roundkey after altering all column : \n");	
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			printf("%X ",roundkey[i][j]);
		}
		printf("\n");
	}
	*/
}
void output()
{
	//printf("The encrepted plaintext is :\n");
	for(int i=0;i<4;i++)
	{	
		for(int j=0;j<4;j++)
		{
			printf("%02X",statearray[j][i]);
		}
		printf(" ");	
	}
	printf("\n");
}
void rnds()
{
	for(;rounds<=10;rounds++)
	{
		if(rounds!=10)
		{
			subbyte();
			shiftrow();
			mixcolm();
			keyexpansion();
			addroundkey();
		}
		else
		{
			subbyte();
			shiftrow();
			keyexpansion();
			addroundkey();
		}
	}	
	output();
}
void main()
{
	//clock_t t;
	//t = clock();
	masterkey();
	printf("The encrepted plaintext is :\n");
	for(;flag!=1;)
	{input();
	masterkey();
	addroundkey();
	rnds();
	rounds=1;}
	//t = clock() - t;
	//double time_taken = (double)t;
	//printf("%f\n", time_taken);
}
