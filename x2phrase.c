/***************************************************************\
*   x2phrase: Convert existing BTC Keys to bip39 word phrases   *
*                                                               *
*   Authored by: Anthero                                        *
*                                                               *
\***************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//function definitions
void show_help(void); //displays help text
void generate_bip39_array(void); //fills the array from bip39.txt file
const char *decimal_to_base62(int dec); //converts dec to b62, returns string
const int  base62_to_decimal(char *b62); //converts b62 to dec, returns dec as int
void x2_encode(int argc, char *argv[]);
void x2_decode(int argc, char *argv[]);

//global variables
char dtob[8]; //return variable for dec_to_base
char bip39[2048][16]; //filled by function
char base62_alphabet[] = { 
	'0','1','2','3','4','5','6','7','8','9',
	'a','b','c','d','e','f','g','h','i','j',
	'k','l','m','n','o','p','q','r','s','t',
	'u','v','w','x','y','z','A','B','C','D',
	'E','F','G','H','I','J','K','L','M','N',
	'O','P','Q','R','S','T','U','V','W','X',
	'Y','Z' };

// Main function
int main(int argc, char *argv[]) {
	
	if (argc <= 2) {

		show_help();

	} else if (strcmp(argv[1], "-e") == 0) {
		
		generate_bip39_array(); 
		
		//pass arguments to encoder
		x2_encode(argc, argv);

	} else if (strcmp(argv[1], "-d") == 0) {

		generate_bip39_array();

		//pass arguments to decoder
		x2_decode(argc, argv);
	
//	} else if (strcmp(argv[1], "-t") == 0) { 

		// uncomment line above for debugging, trace code goes here

	} else { 

		show_help();

	}

	return 0;
}

//supporting functions
void x2_encode(int argc, char *argv[]) {

		char stemp[4];
		char *key = argv[2];
		int  cpos = 0;
		int  itemp;

		while (cpos < strlen(key)) {
			
			// grab 2 char from key, make a string and encode
			for (int i = 0; i < 2; i++) {
				stemp[i] = key[cpos];
				cpos++;
			} stemp[3] = '\0';
			itemp = base62_to_decimal(stemp);

			if (itemp <= 2048) { //test if lower than x2
				
				printf("%s ", bip39[itemp-1]); //print word, consider zero-index
			
			} else { //char pair value is too large, just grab the first char
				
				stemp[1] = '\0'; //truncate string to first char
				itemp = base62_to_decimal(stemp); //overwrite itemp
				printf("%s ", bip39[itemp-1]); //print word, consider zero-index
				cpos--; //decrement char position for next run

			}
		}
		printf("\n");
}

void x2_decode(int argc, char *argv[]) {

		for (int i = 2; i < argc; i++)
			for (int j = 0; j < 2048; j++)
				if (strcmp(argv[i], bip39[j]) == 0)
					printf("%s", decimal_to_base62(j+1));
		
		printf("\n");

}

const int base62_to_decimal(char *b62) {
	int  itemp[4];
	int  output = 0;
	int  base = 62;
	int  power = 1;
	
	for (int i = 1; i < strlen(b62); i++)
		power *= base;

	for (int i = 0; i < strlen(b62); i++)
		for (int j = 0; j < base; j++)
			if (b62[i] == base62_alphabet[j])
				itemp[i] = j;
	
	for (int i = 0; i < strlen(b62); i++) {
		itemp[i] = itemp[i] * power;
		power /= base;
		output += itemp[i];
	}

	return output;
}

const char *decimal_to_base62(int dec) {
	int  num    = dec;
	int  base   = 62;
	int  place  = 1;
	int  pcount = 0;
	int  scount = 0;
	//char dtob[] = declared in global
	//base62_alphabet[] = declared in global
	
	for (int i = 0; i < 8; i++)
		dtob[i] = 0;

	while (place <= num / base)
		place *= base;

	while (place >= 1) {
		while (num >= place) {
			pcount++;
			num -= place;
		}
		dtob[scount] = base62_alphabet[pcount];
		place /= base;
		pcount = 0;
		scount++;
	}
	dtob[scount+1] = '\0';
	
	return dtob;
}

void show_help(void) { //displayed each time an incorrect arg set is used.
	printf("Arguments required.\n");
	printf("Encoding: x2phrase -e <PubKey>\n");
	printf("Decoding: x2phrase -d <KeyPhrase>\n");
}

void generate_bip39_array(void) { //fills the array, run once
	FILE *fp;
	//char bip39[2048][16]; //moved to global
	
	fp = fopen("./BIP39", "r");
	for (int i = 0; i < 2048; i++)
		fscanf(fp, "%s", bip39[i]);
	fclose(fp);
}
