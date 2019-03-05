#include <stdio.h>
#include <stdlib.h>
#include <err_code.h>
#include <CL/cl.h>
#include <sys/types.h>

typedef unsigned long ull;

using namespace std;

int main()
{
  
  ull N = 1000;

  ull *h_list;
  ull *h_primes;
  ull limit= floor(sqrt(N));
  cl_mem d_list;
  cl_mem d_primes;
  

  return 0;
}