
#include "aoi.h"

int main() {

    cl_device_id		        deviceID;
    cl_context                  context = NULL;
    cl_command_queue            command_queue = NULL;
    cl_mem                      memobj = NULL;
    cl_program                  program = NULL;
    cl_kernel                   kernel = NULL;
    cl_int                      ret;

    char ouput[MEM_SIZE]; 

    InitializeOpenCL(&deviceID, &context, &command_queue, &program);

    // Create Memory Buffer
    memobj = clCreateBuffer(context, CL_MEM_READ_WRITE, MEM_SIZE * sizeof(char), NULL, &ret);
    CheckCLError (ret, "Could not create clCreateBuffer.", "Created clCreateBuffer.");
    
    // Create OpenCL Kernel
    kernel = clCreateKernel(program, "hello", &ret);
    CheckCLError (ret, "Could not create clCreateKernel.", "Created clCreateKernel.");
    
    // Set OpenCL Kernel Parameters
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);
    CheckCLError (ret, "Could not create clSetKernelArg.", "Created clSetKernelArg.");
    
    // Execute OpenCL Kernel
    ret = clEnqueueTask(command_queue, kernel, 0, NULL,NULL);
    CheckCLError (ret, "Could not create clEnqueueTask.", "Created clEnqueueTask.");

    // Copy results from the memory buffer
    ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0, MEM_SIZE * sizeof(char), ouput, 0, NULL, NULL);
 
    // Display Result
    puts(ouput);
 
    // Finalization 
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(memobj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);

   return 0;
}
