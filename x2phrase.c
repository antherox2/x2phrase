/***************************************************************\
*   x2phrase: Convert existing BTC Keys to bip39 word phrases   *
*                                                               *
*   Authored by: Anthero                                        *
*                                                               *
\***************************************************************/

// Development Tasks:
// [x] Write function to import bip39 dict to string array
// [x] Write function to convert dec to base62
// [ ] Write function to convert base62 to dec
// [x] Write a help text function
// [ ] Establish main function
// [x] Declare global arrays

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//function declarations
void show_help(void); //displays help text
void generate_bip39_array(void); //fills the array from bip39.txt file
const char *decimal_to_base62(int dec); //converts dec to b62, returns string
int  base62_to_decimal(char *b62[]); //converts b62 to dec, returns dec as int

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

		//encode

	} else if (strcmp(argv[1], "-d") == 0) {

		//decode
	
	} else if (strcmp(argv[1], "-t") == 0) {

		//trace, debugging goes here
		generate_bip39_array();
		printf("%s\n", bip39[1]);

	} else { 

		show_help();

	}

	return 0;
}

//supporting functions
int base62_to_decimal(char *b62[]) {
	int num;
	
	return num;
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
		place = place * base;

	while (place >= 1) {
		while (num >= place) {
			pcount++;
			num = num - place;
		}
		dtob[scount] = base62_alphabet[pcount];
		place = place / base;
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
	fp = fopen("./BIP39.txt", "r");
	for (int i = 1; i <= 2048; i++)
		fscanf(fp, "%s", bip39[i]);
	fclose(fp);
}