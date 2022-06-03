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

#define SPI_PATH "/dev/spidev1.0"

int transfer(int fd, unsigned char send[], unsigned char receive[], int length){
   struct spi_ioc_transfer transfer;           //the transfer structure
   transfer.tx_buf = (unsigned long) send;     //the buffer for sending data
   transfer.rx_buf = (unsigned long) receive;  //the buffer for receiving data
   transfer.len = length;                      //the length of buffer
   transfer.speed_hz = 1000000;                //the speed in Hz
   transfer.bits_per_word = 8;                 //bits per word
   transfer.delay_usecs = 0;                   //delay in us

   // send the SPI message (all of the above fields, inc. buffers)
   int status = ioctl(fd, SPI_IOC_MESSAGE(1), &transfer);
   if (status < 0) {
      perror("SPI: SPI_IOC_MESSAGE Failed");
      return -1;
   }
   return status;
}
int Select(unsigned int jk){
int fd, i=0;                   //file handle and loop counter
   unsigned char value, null=0x00;         //sending only a single char
   uint8_t bits = 8, mode = 3;             //8-bits per word, SPI mode 3
   uint32_t speed = 1000;               //Speed is 1 MHz

printf("\njk=%u",jk);
i=1<<jk;
   // The following calls set up the SPI bus properties
   if ((fd = open(SPI_PATH, O_RDWR))<0){
      perror("SPI Error: Can't open device.");
      return -1;
   }
   if (ioctl(fd, SPI_IOC_WR_MODE, &mode)==-1){
      perror("SPI: Can't set SPI mode.");
      return -1;
   }
   if (ioctl(fd, SPI_IOC_RD_MODE, &mode)==-1){
      perror("SPI: Can't get SPI mode.");
      return -1;
   }
   if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits)==-1){
      perror("SPI: Can't set bits per word.");
      return -1;
   }
   if (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits)==-1){
      perror("SPI: Can't get bits per word.");
      return -1;
   }
   if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed)==-1){
      perror("SPI: Can't set max speed HZ");
      return -1;
   }
   if (ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed)==-1){
      perror("SPI: Can't get max speed HZ.");
      return -1;
   }

   // Check that the properties have been set
   printf("SPI Mode is: %d\n", mode);
   printf("SPI Bits is: %d\n", bits);
   printf("SPI Speed is: %d\n", speed);
printf("\n********i=%u\n",255-i);
i=255-i;

   //printf("Counting through all of the LEDs:\n");

   // Loop from 0 to 255 and light the LED bar as a binary counter

//for (i=0; i<255; i++)
   {
//	if(i==jk)
{      
// This function can send and receive data, just sending here
      if (transfer(fd, (unsigned char*) &i, &null, 1)==-1){
         perror("Failed to update the display");
         return -1;
      }
      printf("%4d\r", i);   //print the number on the same line
      fflush(stdout);       //need to flush the output, no \n
      usleep(500000);       //sleep for 100ms each loop
	}
   }
   close(fd); 
}

const char *Clear_GPIO48="echo 0 > /sys/class/gpio/gpio48/value";
const char *Clear_GPIO50="echo 0 > /sys/class/gpio/gpio50/value";
const char *Clear_GPIO51="echo 0 > /sys/class/gpio/gpio51/value";
const char *Clear_GPIO60="echo 0 > /sys/class/gpio/gpio60/value";

const char *Set_GPIO48="echo 1 > /sys/class/gpio/gpio48/value";
const char *Set_GPIO50="echo 1 > /sys/class/gpio/gpio50/value";
const char *Set_GPIO51="echo 1 > /sys/class/gpio/gpio51/value";
const char *Set_GPIO60="echo 1 > /sys/class/gpio/gpio60/value";


const char *Export_GPIO48="echo 48 > /sys/class/gpio/export";
const char *Export_GPIO50=" echo 50 > /sys/class/gpio/export";
const char *Export_GPIO51="echo 51 > /sys/class/gpio/export";
const char *Export_GPIO60="echo 60 > /sys/class/gpio/export";
const char *DIRECTION_SET_GPIO48="echo high > /sys/class/gpio/gpio48/direction";
const char *DIRECTION_SET_GPIO50="echo high > /sys/class/gpio/gpio50/direction";
const char *DIRECTION_SET_GPIO51=	"echo high > /sys/class/gpio/gpio51/direction";
const char *DIRECTION_SET_GPIO60=	"echo high > /sys/class/gpio/gpio60/direction";
const char *DIRECTION_SET_GPIO115=	"echo high > /sys/class/gpio/gpio115/direction";
const char *DIRECTION_SET_GPIO49="echo high > /sys/class/gpio/gpio49/direction";//qhc
/////////////////////

const char *DIRECTION_CLEAR_GPIO48="echo low > /sys/class/gpio/gpio48/direction";
const char *DIRECTION_CLEAR_GPIO50="echo low > /sys/class/gpio/gpio50/direction";
const char *DIRECTION_CLEAR_GPIO51=	"echo low > /sys/class/gpio/gpio51/direction";
const char *DIRECTION_CLEAR_GPIO60=	"echo low > /sys/class/gpio/gpio60/direction";
const char *DIRECTION_CLEAR_GPIO115=	"echo low > /sys/class/gpio/gpio115/direction";
const char *DIRECTION_CLEAR_GPIO49="echo low > /sys/class/gpio/gpio49/direction";//qhc
void Init_595(){
	system(Export_GPIO48);
			system(Export_GPIO50);
			system(Export_GPIO51);
			system(Export_GPIO60);

	system(DIRECTION_SET_GPIO48);
		system(DIRECTION_SET_GPIO50);
		system(DIRECTION_SET_GPIO51);
		system(DIRECTION_SET_GPIO60);

		system(Clear_GPIO48);//clk
		system(Clear_GPIO50);//data
		system(Clear_GPIO51);//rclk
		///system(Clear_GPIO60);
		//usleep(1000);

		system(Clear_GPIO60);//l595
		usleep(10000);
}
void SetChannelULN(unsigned int x)
{
switch(x)
        {
                case 1:
         system(Set_GPIO48);//clk
                system(Set_GPIO50);//data
                system(Set_GPIO51);//rclk
                system(Set_GPIO60);
 system(Clear_GPIO48);
printf("\nP9_15 is Clear");
        break;
        case 2 :
 system(Set_GPIO48);//clk
 system(Set_GPIO60);
                system(Set_GPIO50);//data
                system(Set_GPIO51);//rclk
 system(Clear_GPIO50);
printf("\nP9_14 is Clear");


        break;
        case 3 :
 system(Set_GPIO48);//clk
                system(Set_GPIO50);//data
                system(Set_GPIO60);//rclk
 system(Clear_GPIO51);
printf("\nP9_16 is Clear");


        break;
        case 4 :
 system(Set_GPIO51);
 system(Set_GPIO48);//clk
 system(Set_GPIO50);//data
                system(Clear_GPIO60);//rclk
printf("\nP9_12 is Clear");


        break;
}
}


void SetChannel(unsigned int x)
{
switch(x)
	{
		case 1:
	 system(Clear_GPIO48);//clk
                system(Clear_GPIO50);//data
                system(Clear_GPIO51);//rclk
 		system(Clear_GPIO60);
 system(Set_GPIO48);
printf("\nP9_15 is set");
	break;
	case 2 :
 system(Clear_GPIO48);//clk
 system(Clear_GPIO60);
                system(Clear_GPIO50);//data
                system(Clear_GPIO51);//rclk
 system(Set_GPIO50);
printf("\nP9_14 is set");


	break;
	case 3 :
 system(Clear_GPIO48);//clk
                system(Clear_GPIO50);//data
                system(Clear_GPIO60);//rclk
 system(Set_GPIO51);
printf("\nP9_16 is set");


	break;
	case 4 :
 system(Clear_GPIO51);
 system(Clear_GPIO48);//clk
                system(Clear_GPIO50);//data
                system(Set_GPIO60);//rclk
printf("\nP9_12 is set");


	break;
}
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
void *threadFunction(void *value){
   do {

      int notimes = prussdrv_pru_wait_event (PRU_EVTOUT_1);
      FreqChannel[ChannelIndex].count = *(pru0DataMemory_int+2);
if(FreqChannel[ChannelIndex].count<FOUR194304+200)
TargetFreq=4194304;
else
if(FreqChannel[ChannelIndex].count<THREE2768+200)
TargetFreq=32768;
else if(FreqChannel[ChannelIndex].count<FIVE12+200)
TargetFreq=512;
else  if(FreqChannel[ChannelIndex].count<TWO56+200)
TargetFreq=256;
else if(FreqChannel[ChannelIndex].count<ONEHZ+200)
TargetFreq=1;





printf("\rFreq Range is =%u Hz",TargetFreq);
switch(TargetFreq)
{
case 32768 :
	FreqChannel[ChannelIndex].count+=FREQ32768CALIB;
	break;
case 4194304 :
FreqChannel[ChannelIndex].count-=10;
break;
case 256 :
	FreqChannel[ChannelIndex].count-=FREQ256CALIB;
	break;
case  512 :
 FreqChannel[ChannelIndex].count+=CALIB512;//1000000-FREQ512CALIB;
if(FreqChannel[ChannelIndex].min>=FreqChannel[ChannelIndex].count)
{ 
FreqChannel[ChannelIndex].min=FreqChannel[ChannelIndex].count;

}

break;
case 1:
//printf("\nFirst=%u",FreqChannel[ChannelIndex].count);////		 
FreqChannel[ChannelIndex].count=FreqChannel[ChannelIndex].count/1000+FREQ1HZCALIB;//);//-FREQ1HZCALIB;

	break;
}

{
//	FreqChannel[ChannelIndex].count-=FREQ512CALIB;
if(x1){
FreqChannel[0].min=FreqChannel[ChannelIndex].count;
x1=0;
}
}
if(FreqChannel[ChannelIndex].min>=FreqChannel[ChannelIndex].count)
{ 
FreqChannel[ChannelIndex].min=FreqChannel[ChannelIndex].count;

}
printf("Ch-%u=>Counts=%u  RAW=%u\r",ChannelIndex,FreqChannel[ChannelIndex].count,*(pru0DataMemory_int+2));//     std::cout<<ChannelIndex<<"="<<FreqChannel[ChannelIndex]<<"\r";

      
      //printf(is %f inches (%f cm)             \r", distin, distcm);
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
int  main (void)
{
unsigned int temp=0;
while(1) {

//Init_595();
printf("Please enter a valid number/chanel: ");
///temp=cin_int();
printf("\n..............");
///SetChannelULN(temp);
printf("\n************");
///if(temp>0)
///if(temp<5)
{
//temp=temp-1;
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
   *pru0DataMemory_int =100;// 500;
   // Use the second 4 bytes for the sample delay in ms
   *(pru0DataMemory_int+1) = 100;   // 2 milli seconds between samples

   // Load and execute binary on PRU
   prussdrv_exec_program (PRU_NUM, "./Fppm.bin");
   if(pthread_create(&thread, NULL, &threadFunction, NULL)){
       printf("Failed to create thread!");
   }
   int n = prussdrv_pru_wait_event (PRU_EVTOUT_0);
   printf("PRU program completed, event number %d.\n", n);
   printf("The data that is in memory is:\n");
   printf("- the number of samples used is %d.\n", *pru0DataMemory_int);
   printf("- the time delay used is %d.\n", *(pru0DataMemory_int+1));
   unsigned int raw_distance = *(pru0DataMemory_int+2);
//FreqChannel[ChannelIndex].count= *(pru0DataMemory_int+2);
//FreqChannel[ChannelIndex].count-=FREQ512CALIB;
   printf("- Channel=%u the  sample is %u.\n", ChannelIndex, FreqChannel[ChannelIndex].count);
}
   }

   /* Disable PRU and close memory mappings */
   prussdrv_pru_disable(PRU_NUM);
   prussdrv_exit ();
   return EXIT_SUCCESS;
}
