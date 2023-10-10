#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define PI M_PI
#define BUFF_SIZE 1024

 double expon(double x, int n){
  if(n <= 0){
    return 1;
  }
  else{
    return x * expon(x,n-1);
  }
}

int fac(int n){
  if (n <= 1){
    return 1;
  }
  else{
    return n * fac(n - 1);
  }
}

  //stolen
  float inverse_sqrt( float number ) 
{ 
 const float threehalfs = 1.5F; 
 
 float x2 = number * 0.5F; 
 float y = number; 
  
 // evil floating point bit level hacking 
 long i = * ( long * ) &y; 
  
 // value is pre-assumed 
 i = 0x5f3759df - ( i >> 1 ); 
 y = * ( float * ) &i; 
  
 // 1st iteration 
 y = y * ( threehalfs - ( x2 * y * y ) ); 
  
 // 2nd iteration, this can be removed 
   y = y * ( threehalfs - ( x2 * y * y ) ); 
 
 return y; 
} 

float arcsine(float x, int n){
  if( x > 1){
    printf("error, x !> 1 for arcsine\n");
    exit(1);
      }
  float dx = (x/n);
  float s = 0;
  for(int i = 0; i < n; i++){
    // s += inverse_sqrt(1 - ((dx * i) * (dx * i))) * dx;
     s+= (1/sqrtf(1-((dx * i) * (dx * i)))) * dx;
  }
  return s;
}

float sine(float x){
  float eps = 5e-5;
  float dxn;
  float fxn;
  float a;
  float s;
  time_t t;
  srand((unsigned) time(&t));
  a = ((float)(rand())/RAND_MAX) - .5;
  if(x < PI/4 && x > -1 * PI/4){
  do{
     dxn = 1/sqrtf(1-(a*a));
     fxn = (arcsine(a,10000) -x);
     a -= (fxn * dxn);
  }while(((fxn < (-1 * eps)) || (fxn > eps)));
  return a;
  }
  else if( x < PI/2 && x > -1 * PI/2){
    s = sine(x/2);
  return 2 * s * sqrtf(1-(s*s));
  }
  else if(x < 3 * PI/4 && x > -3 * PI/4){
    s = sine(PI/2 - x); 
  return sqrtf(1 - (s * s));
  }
  else if(x < PI && x > -1 * PI){
    s = sine((PI/2 - x)/2);
     return (1 - 2 * s * s);
  }
  else if (x < 2 * PI && x > -2 * PI){
    return -1 * sine(x - PI);
  }
  else if ( x > 2 * PI || x < -2 * PI){
    return sine(x - 2 * PI);
  }
  else{
    printf("error: X value out of bounds\n");
    return 0;
      }
}

void cleanUp(char** str, char* vars){



}

float cosine(float x){
  float s = sine(x);
  return sqrtf(1 - (s * s));
}

int numL(int n){
  if(n == 0){
    return 1;
  }
  else{
  return (int)(floor(log10(n)) + 1);
  }
}

void insertNum(char** str,int a, int n){
  int l;
  l = numL(n);
  if(n == 0){
    *(*str + a) = '0';
  }
  else{
  while(n > 0){
    l--;
    *(*str + a + l) = (char)((48) + (n % 10));
    n/= 10;
  }
  }
}

char* binomial(char a, char b, int n){
  char* str = malloc(sizeof(char) * BUFF_SIZE);
  int k = 0;
  int coef;
  for(int i = 0; i < n + 1; i++){
    coef = fac(n)/(fac(i)*fac(n-i));
    insertNum(&str,k,coef);
    k += numL(coef);
    str[k] = a;
    k++;
    str[k] = '^';
    k++;
    insertNum(&str,k,n-i);
    k += numL(n-i);
    str[k] = b;
    k++;
    str[k] = '^';
    k++;
    insertNum(&str,k,i);
    k += numL(i);
    if(i != n){
    str[k] = ' ';
    str[k + 1] = '+';
    str[k + 2] = ' ';
    k += 3;
    }
  }
  return str;
}

int main(int argc, char* argv[]){
  /*  for(int i = 0; i < 13; i++){
    printf("sin(%d%s) = %.3f\n",(i),("PI/6"),sine(PI/6 * i));
    printf("cos(%d%s) = %.3f\n",(i),("PI/6"),cosine(PI/6 * i));
    }*/
  char* str = binomial('x','b',10);
  printf("%s\n",str);
  return 0;
}
