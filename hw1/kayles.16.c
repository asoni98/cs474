#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

int *moveOutputFunc(int numXs, int grundyNext, int *grundyNum);
int myXOR(int x, int y);
int MEX(int *values, int length);
int* grundy(int n);
int *convertInput(char *input, int *outputLength);
char *msb(int *inputNums, int *inputLen);
int intTobinary(int dec);
int intLength(int dec);
int *moveOutputFunc(int numXs, int grundyNext, int *grundyNum);
char *moveToChar(int *move);

int myXOR(int x, int y)
{
  return x^y;
}

int MEX(int *values, int length) {
  // qsort(values, length, sizeof(int), cmpfunc);
  int present[length];
  memset(present, -1, sizeof(present));
  
  for (int i = 0; i < length; ++i)
  {
    if (values[i] > length) {
      printf("ERROR HERE");
      return -1;
    }
    else {
      present[values[i]] = 1;
    }
  }

  for (int i = 0; i < length; ++i)
  {
    if (present[i] == -1) {
      return i;
    }
  }

  printf("ERRROR");
  return -1;
}

int* grundy(int n) {
  int *grundyNum = malloc(sizeof(int) * n);
  grundyNum[0] = 0;
  grundyNum[1] = 1;
  grundyNum[2] = 0;

  for (int i = 3; i < n+1; ++i)
  {
    int ceiling = (int) i/2 + 1;
    int tempArray[ceiling];
    tempArray[0] = grundyNum[i-2];
    
    for (int j = 1; j < ceiling; ++j)
    {
      tempArray[j] = myXOR(grundyNum[j], grundyNum[i-2-j]);
    }

    //TESTING PURPOSES ONLY
    // printf("\n Grundy %d:\n", i);
    // for (int i = 0; i < ceiling; ++i)
    // {
    //   printf("%d, ", tempArray[i]);
    // }
    // printf("\n");

    grundyNum[i] = MEX(tempArray, ceiling);
  }
  return grundyNum;

  // MEX(
  // G(n-2),
  // myXOR(G(1), G(n-3)),
  // myXOR(G(2), G(n-4)))
}

int *convertInput(char *input, int *outputLength) { //converts input (.xxxxx..) to numbers
  int length = strlen(input);
  printf("LENGTH: %d\n", length);
  int *output = calloc(length, sizeof(int));
  
  //*dotsOutput = malloc(length * sizeof(int));

  int next = 0;
  bool onPin;
  if (input[0] == '.') {
    onPin = false;
    next = -1; 
  }
  else {
    onPin = true;
  }

  // ...xxxxx....
  // xxxx...xxxxx.xxxx
  
  for (int i = 0; i < length; ++i)
  {
    if (input[i] == '.' && onPin) {
      //next++;
      onPin = false;
      //continue;
    }
    else if (input[i] == '.' && onPin == false) {
      //next++;
      onPin = false;
      //continue;
    }
    else if (input[i] == 'x' && onPin) {
      //next++;
      output[next] = output[next] + 1;
      onPin = true;
    }
     else if (input[i] == 'x' && onPin == false) {
      next++;
      output[next] = output[next] + 1;
      onPin = true;
    }
  }
  //*output = realloc(output, (next+1) * sizeof(int));
  *outputLength = next+1; //breaks if not at least 1. fix this. 
  printf("OUTPUT LENGTH: %d\n", *outputLength);
  return output;
}


int intTobinary(int dec)
{
    if (dec == 0)
    {
        return 0;
    }
    else
    {
        return (dec % 2 + 10 * intTobinary(dec / 2));
    }
}

int intLength(int dec) {
  if (dec != 0) {
    return floor(log10(abs(dec))) + 1;
  }
  else {
    return 1;
  }
}

char *msb(int *inputNums, int *inputLen) {//pass in outputLength here
  int maxint = 0;
  for (int i = 0; i < *inputLen; ++i)
  {
    if (inputNums[i] > maxint) {maxint = inputNums[i];}
  }

  int *grundyNum = grundy(maxint+1); 
  int grundyCurr = 0;
  for (int i = 0; i < *inputLen; ++i)
  {
    grundyCurr = myXOR(grundyNum[inputNums[i]],grundyCurr);
  }
  if (grundyCurr==0) {
    return "LOSS";
  }

  int binaryLength = intLength(intTobinary(grundyCurr));
  int savedSpot = 0;
  for (int i = 0; i < *inputLen; ++i)
  {
    int binaryNum = intTobinary(grundyNum[inputNums[i]]);
    int numLength = intLength(binaryNum);
    char result[numLength*2];
    sprintf(result, "%d", binaryNum);
    printf("BinaryNum: %d, NumLength: %d, Result: %s\n", binaryNum, numLength, result);
    if (((numLength - binaryLength) >= 0) && (result[numLength - binaryLength] == '1')) {
      savedSpot = i;
      break;
    }
  }

  int grundyNext = myXOR(grundyNum[inputNums[savedSpot]], grundyCurr);
  printf("Grundy Current: %d Binary Length: %d\n Saved Spot: %d\n Grundy Next: %d \n", grundyCurr, binaryLength, savedSpot, grundyNext);

  // printf("Grundy Current: %d Binary Length: %d\n Lower Bound: %d, Upper Bound: %d, Saved Spot: %d\n Grundy Next: %d \n", grundyCurr, binaryLength, lowerbound, upperbound, savedSpot, grundyNext);
  //CORRECT UP TO HERE I BELIEVE
  
 int *move = moveOutputFunc(inputNums[savedSpot], grundyNext, grundyNum);
 printf("Move1: %d Move2: %d", move[0], move[1]);
 char *charMove = moveToChar(move);
 printf("\nCHAR MOVE: %s\n", charMove);

  free(move);
  return charMove; //this needs to be reworked


  //need to change currentPosition grundy number to grundyNext

  //list all moves from that position. check the grundyNum of that move. if it matchs then it's the move. 


  
}

int *moveOutputFunc(int numXs, int grundyNext, int *grundyNum) {//output the correct move
  // char *output = malloc((numXs+1)*sizeof(char));
  int *output = malloc(2*sizeof(int));
  //length of 1 and length 2 code for manually
  //what to do with loses. I shouldn't get loses here. 
  if (numXs == 1) {
    //printf("WIN");
    output[0] = -1;
    output[1] = -1;
    return output; 
  }

  if (numXs == 2) { //shouldn't come here in the first place
    printf("LOSE Shouldn't be here");
    output[0] = 0;
    output[1] = 0;
    return output;
  }

  int ceiling = (int) numXs/2 + 1;
  int moves[ceiling];

  moves[0] = grundyNum[numXs-2];
  if (moves[0] == grundyNext) {
    output[0] = 0;
    output[1] = numXs-2;
    return output;
  }
    
  for (int j = 1; j < ceiling; ++j)
    {
      moves[j] = myXOR(grundyNum[j], grundyNum[numXs-2-j]);
      if (moves[j] == grundyNext) {
          output[0] = j;
          output[1] = numXs-2-j;
      return output;
      }
    }

  printf("NO POSSIBLE MOVE");
  return output;
}

char *moveToChar(int *move) {
  //{0,8} means two .. in front
  //{1,8} means one x in front and then .. then xxxxxxxx
  if (move[0] == -1 && move[1] == -1)
  {
    char *moveOutput = malloc((2) * sizeof(char));
    moveOutput = ".";
    return moveOutput;
  }

  int length = move[0] + move[1];
  char *moveOutput = malloc((length+3) * sizeof(char));
  for (int i = 0; i < move[0]; ++i)
  {
    moveOutput[i] = 'x';
  }
  moveOutput[move[0]] = '.';
  moveOutput[move[0]+1] = '.';


  for (int i = move[0]+2; i < move[1]+move[0]+2; ++i)
  {
    moveOutput[i] = 'x';
  }
  moveOutput[length+3] = '\0';

  return moveOutput;
}

int main(int argc, char **argv) {
  int n;

  if (argc < 3) { //print nothing if there is only one number inputted (this helps prevent a few segment errors)
    return 0;
  }

  if (strcmp(argv[1],"grundy") == 0) {
    if (argc == 3) {
      n = atoi(argv[2]);
      int *grundyNum = grundy(n);

      printf("[");
      for (int i = 0; i < n; ++i) {
        printf("%d, ", grundyNum[i]);
      }
      printf("%d]\n", grundyNum[n]);

      free(grundyNum);
    }
    return 1;
  }

  // int outputLength = 0;
  // int *outputNums = convertInput(argv[1], &outputLength);
  // // printf("OUTPUT NUMS: \n");
  // // for (int i = 0; i < outputLength; ++i)
  // // {
  // //   printf("%d ", outputNums[i]);
  // // }
  // // printf("\n");

  // char *move = msb(outputNums, &outputLength);
  // printf("MOVE: %s\n", move);


  //free(move);
  return 0;
}


 



