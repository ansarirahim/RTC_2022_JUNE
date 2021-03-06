/* PRUSS program to  Measure Frequency Error in PPM
*  in Linux userspace by sending an interrupt.
*  written by A. R. Ansari for Secure Meters Ltd @ Udaipur/India.
*/
#include <stdio.h>
#include <stdlib.h>
#include <prussdrv.h>
#include <pruss_intc_mapping.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
using namespace std;
#define PRU_NUM 0
#define ONEHZ 89947314
#define  TWO56 390641
#define FIVE12 156648+8		//843352
#define CALIB512 843552
#define  THREE2768 3052 
#define  FOUR194304 20
// freq 512 9767 counts for first
// freq 512 156550 counts for full ==> 512MHZ=> ideally 100000 ==>56440 for eqp005-708
// freq 512 156448
//FREQ 1HZ ==> 899472
#define FREQ512CALIB 156540
#define FREQ1HZCALIB 909997+3	//89947314
#define FREQ1HZ1 8994
#define FREQ1HZ2 8992
#define FREQ256 390641
#define FREQ32768 3052
#define FREQ32768CALIB (1000000-FREQ32768+6)
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<stdint.h>
#include<linux/spi/spidev.h>
double ** theArray;//
int **testsamples=NULL;
int **M_save=NULL;
double** Make2DDoubleArray(int arraySizeX, int arraySizeY) {
double** theArray;
theArray = (double**) malloc(arraySizeX*sizeof(double*));
for (int i = 0; i < arraySizeX; i++)
   theArray[i] = (double*) malloc(arraySizeY*sizeof(double));
   return theArray;
} 

static void *pru0DataMemory;
static unsigned int *pru0DataMemory_int;
struct Freq {
	unsigned int count;
	unsigned  int calib;
	unsigned  long ppmerror;
	unsigned int min;
	unsigned int max;
	float avg;
	

	
};
#define TOTAL_CHANNELS 4
Freq FreqChannel[TOTAL_CHANNELS];
unsigned int  TargetFreq=512;//512;
unsigned int   NoOfSamplesTaken=0;
unsigned int 	SamplingFreq=10;
unsigned int  ChannelIndex=0;
unsigned int SampleIndex=0;
#define FREQ1HZ1 8994
#define FREQ1HZ2 8992
#define FREQ4194304 30
///#define FREQ1HZCALIB 8894729
//FreqChannel[0].min=FREQ512CALIB;
unsigned x1=1;
#define FREQ256CALIB (FREQ256-100000)	//290000
unsigned int sampleno=0;
unsigned int sampleold=0;
#define F512 65090
#define F512C 934908
double **arr=NULL;
#define MOD1 13030	//65100
int Freqinput[4];
int  SelectedFreqRange[4];
int mods[100][4];

int Samples[10][4];
/*
void *threadFunction(void *value){
   do {
      int notimes = prussdrv_pru_wait_event (PRU_EVTOUT_1);
      unsigned int raw_distance = *(pru0DataMemory_int+2);
      float distin = ((float)raw_distance / (100 * 148));
      float distcm = ((float)raw_distance / (100 * 58));
      printf("Distance is %f inches (%f cm)             \r", distin, distcm);
      prussdrv_pru_clear_event (PRU_EVTOUT_1, PRU0_ARM_INTERRUPT);
   } while (1);
}
*/
unsigned int M_savet[1000][4];
void *threadFunction(void *value){
   do {
/// int  mod1=65104;
	unsigned int channel=0;
//sampleno
      int notimes = prussdrv_pru_wait_event (PRU_EVTOUT_1);
sampleno=*(pru0DataMemory_int+6);

M_savet[sampleno][0]=*(pru0DataMemory_int+2);
///sampleno=*(pru0DataMemory_int+6);

///
//printf("\nFreq 4.19304 MHz i
///sampleno=*(pru0DataMemory_int+6);

//if(sampleno>sampleold)
{

//if(sampleno>1)
{
//printf("\r***%d. ",sampleno);
//printf(" =>%u",M_savet[sampleno][0]);
}
//printf("\n*%u. Raw0=%u Raw1=%u Raw2=%u Raw3=%u",sampleno, M_save[sampleno][0],M_save[sampleno][1],M_save[sampleno][2],M_save[sampleno][3]);//reqChannel[0].count,FreqChannel[1].count,FreqChannel[2].count,FreqChannel[3].count);
}


sampleold=sampleno;


      prussdrv_pru_clear_event (PRU_EVTOUT_1, PRU0_ARM_INTERRUPT);

   } while (1);
}
int cin_int(void)
{
    std::string input = "";
    int myNumber = 0;

    while (true) {
    getline(std::cin, input);
    std::stringstream myStream(input);
    if (myStream >> myNumber)
        break;
    }
    return myNumber;    
 }
//int  **SampleArray;
#define NOOFCHANNELS 4
#include <stdio.h>
#include <stdlib.h>
 
int array2d(int channels,int rows)
{
    int r = rows, c = channels;
    int *arr = (int *)malloc(r * c * sizeof(int));
/* 
    int i, j, count = 0;
    for (i = 0; i <  r; i++)
      for (j = 0; j < c; j++)
         *(arr + i*c + j) = ++count;
 
    for (i = 0; i <  r; i++)
      for (j = 0; j < c; j++)
         printf("%d ", *(arr + i*c + j));
 */
   /* Code for further processing and free the 
      dynamically allocated memory */
   
   return 0;
}
//int ** arr= NULL;//(void *);
#define CHANNEL1CALIB  0	//(3+4*2)	//7	//-1
#define CHANNEL2CALIB 	(-1)//(1+4*2)	// //-2
#define CHANEL3CALIB 	(-2)	//(2+4*2)	//6
#define CHANNEL4CALIB 0	//(9+4*2)	///6
#define MOD32768 (1018)
#define MOD512 13000	///65100
#define MOD1HZ  33334700
#define MOD256   32550
#define MOD4194304 20
//int **testsamples=NULL;
int te(int c, int r)
{
 //int r=3, c=4;
    //int **arr;
    int count = 0,i,j;
  
    testsamples  = (int **)malloc(sizeof(int *) * r);
    testsamples[0]= (int *)malloc(sizeof(int) * c * r);
}
int selectrange;
int  main (void)
{
unsigned int temp,temp1=0;
int Calib[4];
Freqinput[0]=0;
Freqinput[1]=0;
Freqinput[2]=0;
Freqinput[3]=0;

//while(1) 
Calib[0]=CHANNEL1CALIB;
Calib[1]=CHANNEL2CALIB;
Calib[2]=CHANEL3CALIB;
Calib[3]=CHANNEL4CALIB;
{

///Init_595();
//printf("Minimum value for int: %u", numeric_limits<int>::min());

printf("Please enter No. of Samples ");
temp=cin_int();
//array2d(NOOFCHANNELS,temp);
//int **array = malloc(nrows * sizeof *array + (nrows * (ncolumns * sizeof **array));
//int  **SampleArray = malloc(temp * sizeof *SampleArray + (temp * (4 * sizeof **SampleArray)));
//int **array = malloc (NOOFCHANNELS * sizeof(int *) + (NOOFCHANNELS * (temp * sizeof(int))));
//size_t rows=temp;
//int (*arr)[NOOFCHANNELS];
//...              // get number of rows
//arr = malloc(sizeof *arr * rows);
/*
if (arr)
{
  size_t i, j;
  for (i = 0; i < temp; i++)
    for (j = 0; j < NOOFCHANNELS; j++)
      arr[i][j] = temp;
}*/
//SampleArray = (unsigned int*) malloc(temp * sizeof(int));  //memory allocated using malloc
  //  if(SampleArray == NULL)                     
    {
    //    printf("Error! memory not allocated.");
      //  exit(0);
    }
printf("\n..............");
//SetChannelULN(temp);
printf("\nPls enter sample delay");
temp1=cin_int()+1;
//int selectrange=0;
//int selectrange;
//printf("\nselect range");
//selectrange=cin_int();
printf("\nSelected Range=%d",selectrange);
M_save = (int **)malloc(temp1 * sizeof(int *));

for (int i = 0; i <temp1; i++)
    M_save[i] = (int *)malloc(4 * sizeof(int));
////te(4,temp);//temp,4);
/*arr = (int **)malloc(temp * sizeof(int *));
    for (int i=0; i<temp; i++)
         arr[i] = (int *)malloc(NOOFCHANNELS * sizeof(int));
*/
//theArray=Make2DDoubleArray(temp, 4);
printf("\n..............");

//if(temp>0)
//if(temp<5)
{
///temp=temp-1;
//Select(temp);


   if(getuid()!=0){
      printf("You must run this program as root. Exiting.\n");
      exit(EXIT_FAILURE);
   }
   pthread_t thread;
   tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;

   // Allocate and initialize memory
   prussdrv_init ();
   prussdrv_open (PRU_EVTOUT_0);
   prussdrv_open (PRU_EVTOUT_1);

   // Map PRU's INTC
   prussdrv_pruintc_init(&pruss_intc_initdata);

   // Copy data to PRU memory - different way
   prussdrv_map_prumem(PRUSS0_PRU0_DATARAM, &pru0DataMemory);
   pru0DataMemory_int = (unsigned int *) pru0DataMemory;
   // Use the first 4 bytes for the number of samples
   *pru0DataMemory_int =temp;//1;// 500;
   // Use the second 4 bytes for the sample delay in ms
   *(pru0DataMemory_int+1) = temp1;//100;   // 2 milli seconds between samples

   // Load and execute binary on PRU
   prussdrv_exec_program (PRU_NUM, "./Fppm.bin");
   if(pthread_create(&thread, NULL, &threadFunction, NULL)){
       printf("Failed to create thread!");
   }
   int n = prussdrv_pru_wait_event (PRU_EVTOUT_0);
   printf("PRU program completed, event number %d.\n", n);
   printf("The data that is in memory is:\n");
   printf("- the number of samples used is %d.\n", (*pru0DataMemory_int)-1);
   printf("- the time delay used is %d.\n", *(pru0DataMemory_int+1));
   ///unsigned int raw_distance = *(pru0DataMemory_int+2);
//FreqChannel[ChannelIndex].count= *(pru0DataMemory_int+2);
//FreqChannel[ChannelIndex].count-=FREQ512CALIB;
  // printf("- Channel=%u the  sample is %u.\n", ChannelIndex, FreqChannel[ChannelIndex].count);
printf("\n%%%%%%%%%%");
float  Avgt=0;
int st=2;
float  countspercycle=0;
float freq=0;
for (int i=st;i<temp;i++)
{
countspercycle=((float )M_savet[i][0])/512.0;
freq=10000000.0/countspercycle;
Avgt+=M_savet[i][0];

printf("\n%d %u PerCycleCounts=%f Freq=%f",i,M_savet[i][0],countspercycle,freq);
}
printf("\n\n??Avgt=%f",Avgt);
Avgt=Avgt/((float)(temp-st));
printf("\n\n$$Avgt=%f",Avgt);
   }

///\printf("\nMod Value");//
int Savg=0;
int modvalue=MOD1;
int SampleAvg[4];
int modvaluerange=0;
//int selectrange;


///int M_saveAvg[4]; arr[i] = (int *)malloc(NOOFCHANNELS * sizeof(int));
int  *M_saveAvg;
M_saveAvg = (int *)malloc(NOOFCHANNELS * sizeof(int));
for (int i=0;i<4;i++)
M_saveAvg[i]=0;


int FinalCounts[4];
int FinalMasterCounts[4];
float FinalFreq[4];

for (int i=0;i<4;i++)
{
if(Freqinput[i]>=0)
{
FinalCounts[i]=10000000+Calib[i]-M_saveAvg[i];
printf(" \n*CCA %d RTC Counts=%d ",i,FinalCounts[i]);////10000000+Calib[i]-M_saveAvg[i]);//CCA %d RTC Counts=%d"
}
else
printf("\n*CCA %d  RTC Counts=Invalid Freq input",i);
}
}
   /* Disable PRU and close memory mappings */
   prussdrv_pru_disable(PRU_NUM);
   prussdrv_exit ();
   return EXIT_SUCCESS;
}

