#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <float.h>

#define MAXSCORE 101


long double max(long double x, long double y) {
	if (x > y) {return x;}
	else {return y;}
}


int main(int argc, char **argv)
 {
 	long double	***p = (long double ***) calloc(MAXSCORE, sizeof(long double **));
 	for (int i = 0; i < MAXSCORE; ++i)
 	{
 		p[i] = (long double **) calloc(MAXSCORE, sizeof(long double *));
 		for (int j = 0; j < MAXSCORE; ++j)
 		{
 		p[i][j] = (long double *) calloc(MAXSCORE, sizeof(long double));
 		}
 	}

 	//basic cases plug in manually
 	for (int i = 0; i < MAXSCORE; ++i)
 	{
 		for (int j = 0; j < MAXSCORE; ++j)
 		{
 			for (int k = 0; k < MAXSCORE; ++k)
 			{
 				if (j >= MAXSCORE - 1) {
 					p[i][j][k] = 0; // j>= 100 Pi,j,k = 0 
 					continue;
 				}
 				if ((i + k) >= MAXSCORE - 1) { // i+k>= 100 Pi,j,k = 1
 					p[i][j][k] = 1;
 				}
 			}
 		}
 	}

 	int k2, k3, k4, k5, k6, ik;
 	for (int i = MAXSCORE - 1; i > 0; --i)
 	{
 		for (int j = MAXSCORE - 1; j > 0; --j)
 		{
 			for (int k = MAXSCORE - 1; k > 0; --k)
 			{
 				if ((k6 = (k + 6)) > (MAXSCORE-1)) {k6 = MAXSCORE-1;}
 				if ((k5 = (k + 5)) > (MAXSCORE-1)) {k5 = MAXSCORE-1;}
 				if ((k4 = (k + 4)) > (MAXSCORE-1)) {k4 = MAXSCORE-1;}
 				if ((k3 = (k + 3)) > (MAXSCORE-1)) {k3 = MAXSCORE-1;}
 				if ((k2 = (k + 2)) > (MAXSCORE-1)) {k2 = MAXSCORE-1;}
 				if ((ik = (i + k)) > (MAXSCORE-1)) {ik = MAXSCORE-1;}
 	
 				long double pijkroll = (1/6) * ((1-p[j][i][0]) + p[i][j][k2] + p[i][j][k3] + p[i][j][k4] + p[i][j][k5] + p[i][j][k6]);
 				long double pijkhold = 1 - p[j][ik][0];
 				p[i][j][k] = pijkroll;
 				max(pijkroll, pijkhold);
 				printf("i: %d j: %d k: %d p: %LF\n", i, j, k, p[i][j][k]);
 			}
 		}
 	}


 	
 	



 	// p[99][0][0] = 2;
 	// p[100][0][0] = 3;

 	printf("TEST: %LF\n", p[0][0][20]);

 	// P(i,j,k,roll) = (1/6) * ((1-Pj,i,0) + P(i,j))
 	// P(i,j,k,hold) = 1 - Pj,i+k,0

 	return 1;
 }