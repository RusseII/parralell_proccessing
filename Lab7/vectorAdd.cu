/* ACADEMIC INTEGRITY PLEDGE                                              */
/*                                                                        */
/* - I have not used source code obtained from another student nor        */
/*   any other unauthorized source, either modified or unmodified.        */
/*                                                                        */
/* - All source code and documentation used in my program is either       */
/*   my original work or was derived by me from the source code           */
/*   published in the textbook for this course or presented in            */
/*   class.                                                               */
/*                                                                        */
/* - I have not discussed coding details about this project with          */
/*   anyone other than my instructor. I understand that I may discuss     */
/*   the concepts of this program with other students and that another    */
/*   student may help me debug my program so long as neither of us        */
/*   writes anything during the discussion or modifies any computer       */
/*   file during the discussion.                                          */
/*                                                                        */
/* - I have violated neither the spirit nor letter of these restrictions. */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Signed:_____________________________________ Date:_____________        */
/*                                                                        */
/*                                                                        */
/* 3460:4/577 CUDA Vector Add lab, Version 1.01, Fall 2016.               */

#include <stdio.h>
#include <stdlib.h>
#include <cutil.h>

__global__ void vecAdd(float *in1, float *in2, float *out, int len) {
  //@@ Insert code to implement vector addition here
	int i=threadIdx.x+(blockIdx.x*blockDim); //finds thread ID
	out[i]=(in1[1]+in2[i];
}

int main(int argc, char **argv) {
  int inputLength1, inputLength2, outputLength;
  float *hostInput1;
  float *hostInput2;
  float *hostOutput;
  float *deviceInput1;
  float *deviceInput2;
  float *deviceOutput;
  float *expectedOutput;

  FILE *infile1, *infile2, *outfile;
  unsigned int generic, gpu, copy, compute, blog = 1;

  // Import host input data
  CUT_SAFE_CALL(cutCreateTimer(&generic));
  cutStartTimer(generic);
  if ((infile1 = fopen("input0.raw", "r")) == NULL)
  { printf("Cannot open input0.raw.\n"); exit(EXIT_FAILURE); }
  if ((infile2 = fopen("input1.raw", "r")) == NULL)
  { printf("Cannot open input1.raw.\n"); exit(EXIT_FAILURE); }
  fscanf(infile1, "%i", &inputLength1);
  hostInput1 = (float*) malloc(sizeof(float) * inputLength1);
  for (int i = 0; i < inputLength1; i++)
    fscanf(infile1, "%f", &hostInput1[i]);
  fscanf(infile2, "%i", &inputLength2);
  hostInput2 = (float*) malloc(sizeof(float) * inputLength2);
  for (int i = 0; i < inputLength2; i++)
    fscanf(infile2, "%f", &hostInput2[i]);
  fclose(infile1);
  fclose(infile2);
  hostOutput = (float *)malloc(sizeof(float) * inputLength1);
  cutStopTimer(generic);
  printf("Importing data and creating memory on host: %f ms\n", cutGetTimerValue(generic));

  if (blog) printf("*** The input length is %i\n", inputLength1);

  CUT_SAFE_CALL(cutCreateTimer(&gpu));
  cutStartTimer(gpu);
  //@@ Allocate GPU memory here
int alloSize=sizeof(float)*inputLength1;
cudaMalloc((void * *) & deviceInput1,alloSize);
cudaMalloc((void * *) & deviceInput2,alloSize);
cudaMalloc((void * *) & deviceOutput,alloSize);
  
  cutStopTimer(gpu);
  printf("Allocating GPU memory: %f ms\n", cutGetTimerValue(gpu));

  cutDeleteTimer(gpu);
  CUT_SAFE_CALL(cutCreateTimer(&gpu));
  cutStartTimer(gpu);

  //@@ Copy memory to the GPU here
cudaMemcpy(deviceInput1,hostInput1,alloSize,cudaMemcpyHostToDevice)
cudaMemcpy(deviceInput2,hostInput1,alloSize,cudaMemcpyHostToDevice)
cudaMemcpy(deviceOutput,hostInput1,alloSize,cudaMemcpyHostToDevice)
  cutStopTimer(gpu);
  printf("Copying input memory to the GPU: %f ms\n", cutGetTimerValue(gpu));

  //@@ Initialize the grid and block dimensions here
dim3 gridDim(ceil(inputLength1/4),1,1);
dim3 blockDim(ceil(inputLength1/4),1,1);



  if (blog) printf("*** Block dimension is %i\n", blockDim.x);
  if (blog) printf("*** Grid dimension is %i\n", gridDim.x);

  CUT_SAFE_CALL(cutCreateTimer(&compute));
  cutStartTimer(compute);
  
  //@@ Launch the GPU Kernel here
  vecAdd <<< gridDim, blockDim >>> (deviceInput1,deviceInput2, deviceOutput,inputLength1);

  cudaDeviceSynchronize();
  
  cutStopTimer(compute);
  printf("Performing CUDA computation: %f ms\n", cutGetTimerValue(compute));

  CUT_SAFE_CALL(cutCreateTimer(&copy));
  cutStartTimer(copy);

  //@@ Copy the GPU memory back to the CPU here
cudaMemcpy(hostOutput, deviceOutput, alloSize, cudaMemcpyDeviceToHost);

  
  cutStopTimer(copy);
  printf("Copying output memory to the CPU: %f ms\n", cutGetTimerValue(copy));

  cutDeleteTimer(gpu);
  CUT_SAFE_CALL(cutCreateTimer(&gpu));
  cutStartTimer(gpu);
  
  //@@ Free the GPU memory here
  cudaFree(deviceInput1);
  cudaFree(deviceInput2);
  cudaFree(deviceOutput);
  
  cutStopTimer(gpu);
  printf("Freeing GPU Memory: %f ms\n", cutGetTimerValue(gpu));

  if ((outfile = fopen("output.raw", "r")) == NULL)
  { printf("Cannot open output.raw.\n"); exit(EXIT_FAILURE); }
  fscanf(outfile, "%i", &outputLength);
  expectedOutput = (float*) malloc(sizeof(float) * outputLength);
  for (int i = 0; i < outputLength; i++)
    fscanf(outfile, "%f", &expectedOutput[i]);
  fclose(outfile);
  int test = 1;
  for (int i = 0; i < outputLength; i++)
    test = test && (abs(expectedOutput[i] - hostOutput[i]) < 0.005);
  if (test) printf("Results correct.\n");
  else printf("Results incorrect.\n");

  cutDeleteTimer(generic);
  cutDeleteTimer(gpu);
  cutDeleteTimer(copy);
  cutDeleteTimer(compute);

  free(hostInput1);
  free(hostInput2);
  free(hostOutput);
  free(expectedOutput);
  
  return 0;
}
