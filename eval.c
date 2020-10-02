#include <stdio.h>
#include <math.h>    /* for pow(x, y) */
#include "type.h"
#include <stdlib.h>
#define n_dim 2
#define bits_per_dim 17
#define bit_weight 131072
#define bits_per_unit 1000

double decode(IPTR pj, int index, int size);
double binToDec(int *chrom, int l);

double eval(POPULATION *p, IPTR pj) 
     /* Called from gen.c and init.c */
{

  double val;
  //double square = 0.0;

  val = decode(pj, 0, p->lchrom); 
  //square = val * val;

  return val;
}

double decode(IPTR pj, int index, int size)
{

  return ((double) binToDec(&(pj->chrom[0]), size));
}

double rand_gen() {
   // return a uniformly distributed random value
   return ( (double)(rand()) + 1. )/( (double)(RAND_MAX) + 1. );
}
double normalRandom() {
   // return a normally distributed random value
   double v1=rand_gen();
   double v2=rand_gen();
   return cos(2*3.14*v2)*sqrt(-2.*log(v1));
}
double binToDec(int *chrom, int l)
{
  float x1;
  float x2;
  int a1[n_dim] = {-32,-16,0,16,32,-32,-16,0,16,32,-32,-16,0,16,32,-32,-16,0,16,32,-32,-16,0,16,32};
  int a2[n_dim] = {-32,-32,-32,-32,-32,-16,16,-16,16,-16,0,0,0,0,0,16,16,16,16,16,32,32,32,32,32};
  int i;
  int j = 0;
  int k = 0;
  double prod;
  double sum = 0;

  prod = 0.0;

  for(i = 0; i < l; i++)
  {
    j = i % bits_per_dim;
    if (i == 16	)
    {
      x1 = prod-65.536;
      prod = 0;
    }

    if (i == 33 )

    {
      x2 = prod-65.536;
      prod = 0;
    }


    prod += (chrom[i] == 0 ? 0.0 : pow((double)2.0, (double) j))/bits_per_unit;
  }
  printf("x1: %2.2f", x1);
  printf( "x2: %2.2f\n", x2);
  prod = 0;
//  printf("sum-sqs: %2.2f ", sum);
  for (i = 1; i < 26; i++)
  {
  prod = 1/( i + pow((x1-a1[i]),6) + pow((x2-a2[i]),6) );
  sum += prod;
  }
  return sum;
}


void decToBin(int ad, int *barray, int size)
{
  int i, t;

  t = ad;
  for(i = 0; i < size; i++){
    barray[i] = t%2;
    t = t/2;

  }
}
