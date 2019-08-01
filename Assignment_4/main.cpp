#define __CL_ENABLE_EXCEPTIONS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <CL/cl.hpp>
#define MAX_SOURCE_SIZE (0x100000)


typedef struct _cords
{
    int x;
    int y;
    float length = 0.0;
} cords;


void check_err(int status,char* line_num)
{
	if (status != CL_SUCCESS)
	{
		printf("OpenCL error #%s. Error code: %d\n",line_num, status);
        std::exception e;
        throw e;
	}
}

int main(int argc, char const *argv[])
{
    try{
    if(argc != 3){
        std::cout << "Not enough args";
        return 1;
    }
    char const* infile = argv[1];
    char const* outfile = argv[2];

    std::cout << infile << '\n' << outfile << '\n';



    FILE *f;
    char * kernel_test;
    size_t kernel_size;

    f = fopen("./kernel.cl","r");
    if(!f){
        printf("Couldn't find Kernel \n");
        std::exception e;
        throw e;
    }

    
    kernel_test = (char*)malloc(MAX_SOURCE_SIZE);
    kernel_size = fread(kernel_test, 1, MAX_SOURCE_SIZE, f);

    fclose(f);
    f=NULL;

    f = fopen(infile,"r");
    if(!f){
        printf("Couldn't find Kernel \n");
        std::exception e;
        throw e;
    }

    int N;
    int M;

    fscanf(f,"%i",&N);
    fscanf(f,"%i",&M);

     const int LIST_SIZE = M*N*2;

    cords coordinate_holder[N*M];
    cords sorted_cords[N*M];

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; j++)
        {
            fscanf(f,"%i",&(coordinate_holder[i*M+j].x));
            fscanf(f,"%i",&(coordinate_holder[i*M+j].y));
            sorted_cords[i*M+j].x = coordinate_holder[i*M+j].x;
            sorted_cords[i*M+j].y = coordinate_holder[i*M+j].y;
        }
    }



    fclose(f);
    f=NULL;

    cl_platform_id platform = NULL;

    cl_device_id devid = NULL;

    cl_uint num_devices;

    cl_uint num_platforms;

    cl_event events;

    cl_int ret = clGetPlatformIDs(1,&platform,&num_platforms);

    ret = clGetDeviceIDs(platform,CL_DEVICE_TYPE_GPU,1,&devid,&num_devices);

    check_err(ret,"1");

    cl_context context = clCreateContext(NULL,1,&devid,NULL,NULL,&ret);

    cl_command_queue cq = clCreateCommandQueue(context,devid,0,&ret);

    cl_mem in_mem = clCreateBuffer(context,CL_MEM_READ_WRITE,LIST_SIZE*sizeof(cords),NULL,&ret);
    check_err(ret,"in");

    ret = clEnqueueWriteBuffer(cq,in_mem,CL_TRUE,0,LIST_SIZE*sizeof(cords),coordinate_holder,0,NULL,NULL);
    check_err(ret,"2");


    cl_program prog = clCreateProgramWithSource(context,1,(const char **)&kernel_test,(const size_t *)&kernel_size,&ret);
    check_err(ret,"prog");

    ret = clBuildProgram(prog,1,&devid,NULL,NULL,NULL);
    check_err(ret,"4");

    cl_kernel ck = clCreateKernel(prog, "cart", &ret);
    check_err(ret,"5");

    ret = clSetKernelArg(ck, 0, sizeof(cl_mem), (void *)&in_mem);
    check_err(ret,"6");


    ret = clSetKernelArg(ck, 1, sizeof(int), &N);
    //check_err(ret,"62");

    ret = clSetKernelArg(ck, 2, sizeof(int), &M);
    //check_err(ret,"72");

    size_t g_item_size = LIST_SIZE;

    size_t l_item_size = LIST_SIZE/2;

    ret = clEnqueueNDRangeKernel(cq,ck,1,NULL,&g_item_size,&l_item_size,0,NULL,&events);
    check_err(ret,"8");

    ret = clWaitForEvents(1,&events);
    check_err(ret,"9");

    ret = clReleaseEvent(events);
    check_err(ret,"10");
    

    ret = clEnqueueReadBuffer(cq,in_mem,CL_TRUE,0,LIST_SIZE*sizeof(cords),sorted_cords,0,NULL,NULL);
    check_err(ret,"11");


    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; j++)
        {
            //printf("%i ",sorted_cords[i*M+j].x);
            //printf("%i ",sorted_cords[i*M+j].y);
            //printf("%f ", sorted_cords[i*M+j].length);
        }
        //printf("\n");
    }

    f = fopen(outfile,"w");

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; j++)
        {
            fprintf(f,"%i ", sorted_cords[i*M+j].x);
            fprintf(f,"%i ", sorted_cords[i*M+j].y);
            //fprintf(f,"%f ", sorted_cords[i*M+j].length);
        }
        fprintf(f,"\n");
    }

    fclose(f);

    f=NULL;

    
    ret = clFlush(cq);
    ret = clFinish(cq);
    ret = clReleaseKernel(ck);
    ret = clReleaseProgram(prog);
    ret = clReleaseMemObject(in_mem);
    ret = clReleaseCommandQueue(cq);
    ret = clReleaseContext(context);  

    printf("The sorted coordinate data has been stored in output.dat");

    return 0;

    }catch(cl::Error err){
        printf("An unexpected OpenCL error occured \n");
        return 1;

    }catch(std::exception e){
        printf("An unexpected error occured \n");
        return 1;
    }

    return 0 ;
}
