/* pi.cl */
#pragma OPENCL EXTENSION cl_khr_fp64 : enable

__kernel void erastotenes(__global double *marked , __global double *limit , double *n)
{   
    printf("kernel OK");
}