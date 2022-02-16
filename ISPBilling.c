#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define CHAR_MAX 500 //generous size for all strings 

void costCalculator(char first[CHAR_MAX], char second[CHAR_MAX], char third[CHAR_MAX], char fourth[CHAR_MAX]);

double roundMoney();

int main(void) {
  
  FILE *infilep = fopen("usage.txt", "r");
  FILE *outfilep = fopen("charges.txt", "w");

  char usageString[CHAR_MAX]; //string that stores each line of the text file
  char *token;
  char first[CHAR_MAX]; //first column of the charges text file
  char second[CHAR_MAX]; // second column...etc
  char third[CHAR_MAX];
  char fourth[CHAR_MAX];

  int k = 0;
  int m = 0;

  for(int i=1; fgets(usageString,CHAR_MAX,infilep); i++){
    if(i==1){
      token = strtok(usageString," "); //using strtok to create substrings from whitespace to whitespace
      while( token != NULL ) {
        if(k==0){
          strcpy(first, token);
          k++;
        } else {
          strcpy(second,token);
        }
        token = strtok(NULL, " ");
      }
      fprintf(outfilep,"Charges for %s/%s",first,second);
      fprintf(outfilep,"\n");
      fprintf(outfilep,"Customer\tHours used\tCharge per hour\tAverage cost");
      fprintf(outfilep,"\n");
    } else {
      token = strtok(usageString," ");
      while( token != NULL ) {
        if(m==0){
          strcpy(first,token);
          m++;
        } else if(m==1){
          strcpy(second,token);
          m--;
        }
        token = strtok(NULL, " \n");
      }
      costCalculator(first,second,third,fourth);
      fprintf(outfilep,"%s     %s         %.5s            %.4s\n",first,second,third,fourth); //prints all the columns to the file as neatly as possible with a simple fprintf function
    }
  }
  fclose(infilep);
  return 0;
}
// ----------------------------------------------------------------------------
// NAME: round_money
// INPUT Param.: rounded, a double that is the input to be rounded
// OUTPUT Param.: A double, the rounded result of the input parameter
// PURPOSE: The function takes a double which represents some amount of money, and rounds the input to the second decimal place so that it can be treated as a monetary amount. 

double round_money(double rounded){
  double result;
  result = (int)(rounded * 100 + .5);
  return (double)result / 100; //rounds to two decimal places
}
// ----------------------------------------------------------------------------
// NAME: costCalculator
// INPUT Param.: 4 strings each representing a respective entry in the four columns of the charges.txt file.
// OUTPUT Param.: No outputs, as the 4 strings are modified in the main thorugh this function.
// PURPOSE: The function makes calculations so that the Charge per hour and average cost columns can be completed.

void costCalculator(char first[CHAR_MAX], char second[CHAR_MAX], char third[CHAR_MAX], char fourth[CHAR_MAX]){
  double secondDoub;
  char *ptr;
  char secondResult[CHAR_MAX];
  char fourthResult[CHAR_MAX];
  secondDoub = strtod(second,&ptr); //converts hours used into a double
  if(secondDoub>10){ //if extra payment over 7.99 per hour
    if(floor(secondDoub)==secondDoub){
      snprintf(secondResult,CHAR_MAX,"%f",round_money((secondDoub-10)*1.99)); //converts the double charge per hour into a string
      strcpy(third,secondResult); //stores temporary string into third
    } else{
      snprintf(secondResult,CHAR_MAX,"%f",round_money(((floor(secondDoub)-10)*1.99)+9.98));
      strcpy(third,secondResult);
    }
  } else {
    strcpy(third,"7.99");
  }
  if(secondDoub>10){
    snprintf(fourthResult, CHAR_MAX, "%f",round_money((((floor(secondDoub)-10)*1.99)+9.98)/secondDoub)); //converts average cost into a string
    strcpy(fourth,fourthResult); //stores temporary string into fourth
  } else {
    snprintf(fourthResult,CHAR_MAX,"%f",round_money(7.99/secondDoub));
    strcpy(fourth,fourthResult);
  }
}

