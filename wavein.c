/******************************************************************************
 ____                      _                                 _ _         _     
/ ___| ___  _   _ _ __  __| | __ _ _ __ ___  _   _ _ __   __| | |   __ _| |__  
\___ \/ _ \| | | | '_ \/ _` |/ _` | '__/ _ \| | | | '_ \ / _` | |  / _` | '_ \
 ___)  (_) | |_| | | |  (_| | (_| | | | (_) | |_| | | | | (_| | |_| (_| | |_) |
|____/\___/ \__,_|_| |_\__,_|\__, |_|  \___/ \__,_|_| |_|\__,_|____\__,_|_.__/ 
                             |___/                                             
*******************************************************************************
*Autor:    Benjamin Hedert                                        Juni 2022  *
*Version:  0.02                                                              *
*Module:   wavein (prototype)                                                *
******************************************************************************/
#define OPT(a) match(argv[para], a)
#define NO_OPT argv[para][0] != '-'
#define GETPARAM(a, b) strncpy(a, argv[para], b)
#define GETVAL(a, b) strncpy(a, argv[++para], b)
#define VERBOSE verbose && 
#include <stdio.h>

	
#include <string.h>

	void cli_show_help()
	{
		printf("Usage: wavein<Datei/en > -b<bittiefe> -c<channels>\n\nOptionen:\n");
		printf("   -b     --bit       Bittiefe für Import 8/16/24 (default 16)\n");
		printf("   -c     --channels  Audio Channel 1=mono/2=stereo (default 2)\n");
		printf("   -f     --float     Konvertiere Werte in Fließkommazahlen\n");
		printf("   -h     --help      Zeigt diese Hilfe\n");
		printf("   -v     --verbose   Ausführliche Erklärungen\n\n");
		printf("github.com/beni1993/sound-ground-lab   Juni 2022\n");
	}

int match(char *a, char *b)
{
	int i;

	for (i = 0; 1 == 1; i++)
	{
		if (a[i] != b[i])
		{
			return 0;
		}

		if (a[i] == '\0')
		{
			return 1;
		}
	}
}

void cli_set(char *
	var, char *val, int lenght)
{
	int i = 0;
	for (i = 0; i < lenght; i++)
	{
		var[i] = val[i];
		if (var[i] == '\0') break;
	}
	var[++i] = '\0';
}

int main(int argc, char **argv)
{
	//Variablen Standardkonfiguration
	char bit[3] = "16";
	char channels[2] = "2";
	char filename[80];
	char verbose = 0;
	char floatmodus = 0;

	int para = 0;
	for (para = 0; para < argc; para++)
	{
		if (NO_OPT) GETPARAM(filename, 80);
		if (OPT("-v") || OPT("--verbose")) verbose = 1;
		if (OPT("-h") || OPT("--help")) cli_show_help();
		if (OPT("-f") || OPT("--float"))floatmodus = 1;
		if (OPT("-b") || OPT("--bit")) GETVAL(bit, 3);
		if (OPT("-c") || OPT("--channels")) GETVAL(channels, 2);
	}

	/*****************************************************************************/
	int bytemodus = 2;	//2Byte = 16Bit
	int channelmodus = 2; //2Channels = stereo
	float maxval = 32768.0;
	FILE * fp;

	switch (bit[0])
	{
		case '8': //8Bit
			bytemodus = 1;
			maxval = 128.0;
			break;	
		case '1': //16Bit
			bytemodus = 2;
			maxval = 32768.0;
			break;	
		case '2': //24Bit
			bytemodus = 3;
			maxval = 8388608.0;
			break;	
	}
	VERBOSE printf("Bytebreite: %d\n", bytemodus);
	
	switch (channels[0])
	{
		case '1': //mono
			channelmodus = 1;
			break;
		case '2': //stereo
			channelmodus = 2;
			break;
	}
	VERBOSE printf("Channels: %d\n",channelmodus);

	fp = fopen(filename, "rb");

	if (fp == NULL)
	{
		VERBOSE printf("Datei nicht gefunden!\n");
		return 1;
	}

	short i = 0;
	char data = 0;
	int countdown = 4;
	int read = 0;
	int x = 0;
	int head;
	char history[5];
	char channel = 'l';

	while (1)
	{
		if (data && countdown == 0)
		{
			if (read != 1)
			{
				read = 1;
				printf("\n");
			}
			fread(&i, bytemodus, 1, fp);
		}
		else
		{
			head = fgetc(fp);
			if (data)
			{ 	(countdown != 0) ? countdown-- : 0;
			}
		}

		if (feof(fp))
		{
			break;
		}

		history[0] = history[1];
		history[1] = history[2];
		history[2] = history[3];
		history[3] = head;
		history[4] = '\n';

		if (data == 0 &&
			history[0] == 0x64 &&
			history[1] == 0x61 &&
			history[2] == 0x74 &&
			history[3] == 0x61)
		{
			data = 1;
		}

		//--- LESE SAMPLES ---
		if (read && channelmodus == 1 ) //MONO 
		{
			if(floatmodus)
				printf("MONOSAMPLE_FLOAT %e ", i/maxval);
			else
				printf("MONOSAMPLE %d ", i);
		}
		else if (read && channelmodus == 2) //STEREO 
		{
			if (channel == 'r')
			{
				channel = 'l';
				if(floatmodus)
					printf("%e \n", i/maxval);
				else
					printf("%d \n", i);
			}
			else
			{
				channel = 'r';
				if(floatmodus)
					printf("STEREOSAMPLE_FLOAT %e ", i/maxval);
				else
					printf("STEREOSAMPLE %d ", i);
			}
		}
		else
		{
			printf("HEAD %02X\n", head);
		}
	}

	return 0;

}
