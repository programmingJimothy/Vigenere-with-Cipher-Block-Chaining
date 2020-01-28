//------------------------------------------------------------------
// University of Central Florida
// CIS3360 - Fall 2017
// Program Author: James Hague
//------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char **argv){
  char* fileName=argv[1];
  char* vKeyword=argv[2];
  char* iVector=argv[3];
  char cleanText[5001];
  char encryptedText[5001];
  FILE *fp=fopen(fileName, "r");
  if(fp==0){
    printf("Error opening file\n");
    return 0;
  }
  else{
    //printf("file opened\n");
  }
  printf("CBC Vigenere by James Hague\n");
  printf("Plaintext file name: %s\n", fileName);
  printf("Vigenere keyword: %s\n", vKeyword);
  printf("Initialization vector: %s\n", iVector);

  //these 3 variables are needed to read the file character by character, store the character, and put that character into an array
  int i=0;
  char c;
  char read;

  while(fscanf(fp, "%c", &read)!=EOF){
    if(isalpha(read)){
      cleanText[i]=read;
    }
    else{
      i--;
    }
    i++;
  }
  //lines 39-45 gets the length of the clean text, the block size, and the amount of padding that is needed
  int lengthOfText;
  int blockSize;
  int padding;
  blockSize=strlen(vKeyword);
  lengthOfText=strlen(cleanText);
  padding=lengthOfText%blockSize;
  padding=blockSize-padding;

  //makes clean text lowercase
  for(i=0; i<lengthOfText; i++)
    cleanText[i]=tolower(cleanText[i]);

  //adds padding to the clean text
  i=0;
  while(i<padding){
    cleanText[lengthOfText+i]='x';
    i++;
  }
  //clean text is now ready to be encrypted

  //Encryption
  int blockCount;
  int eCount;
  int vCount;
  int vKeyIndex;

  //creates the first 6 letters of the cipher text
  blockCount=strlen(cleanText)/blockSize;
  i=0;
  for(i=0; i<blockSize; i++){
    encryptedText[i]=((((cleanText[i]-97)+(iVector[i]-97)+(vKeyword[i]-97))%26)+97);
  }

  //creates the rest of the cipher text
  i=blockSize;
  for(eCount=0; eCount<blockCount-1; eCount++){
    for(vKeyIndex=0; vKeyIndex<blockSize; vKeyIndex++){
      encryptedText[i]=((((cleanText[i]-97)+(encryptedText[i-blockSize]-97)+(vKeyword[vKeyIndex]-97))%26)+97);
      i++;
    }
  }

  //prints plain text, cipher text, and statistics
  printf("\nClean Plaintext:\n");

  for(i=0; i<lengthOfText; i++){
    if(i%80==0){
      printf("\n");
    }
    printf("%c", cleanText[i]);
  }
  printf("\n\nCiphertext:\n");
  for(i=0; i<lengthOfText+2; i++){
    if(i%80==0){
      printf("\n");
    }
    printf("%c", encryptedText[i]);
  }
  printf("\n\nNumber of characters in clean plaintext file: %d\n", lengthOfText);
  printf("Block size = %d\n", blockSize);
  printf("Number of pad characters added: %d\n", padding);
  fclose(fp);
}
