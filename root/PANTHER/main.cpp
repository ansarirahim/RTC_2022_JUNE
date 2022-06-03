#include <stdio.h>
#include <string.h>
#include <iostream>   // std::cout
#include <string>
// std::string, std::stol
// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* strtol */
#include <string>
#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>     //close()
#include <fcntl.h>     //define O_WONLY and O_RDONLY
#define MAX_BUF 64     //This is plenty large
#include <iostream>

#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include<iostream>
#include<stdio.h>

#include<iostream>
using namespace std;

#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define POLL_TIMEOUT (3 * 1000) /* 3 seconds */
#define MAX_BUF 64
#define P9_24 15
#define QSH P9_24
enum PIN_DIRECTION{
	INPUT_PIN=0,
	OUTPUT_PIN=1
};
 void msleep(unsigned long msec) {
     timeval delay = {msec / 1000, msec % 1000 * 1000};
     int rc = ::select(0, NULL, NULL, NULL, &delay);
     if(-1 == rc) {
         // Handle signals by continuing to sleep or return immediately.
     }
 }
enum PIN_VALUE{
	LOW=0,
	HIGH=1
};
int gpio_set_dir(unsigned int gpio, PIN_DIRECTION out_flag)
{
	int fd;
	char buf[MAX_BUF];

	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%d/direction", gpio);

	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("gpio/direction");
		return fd;
	}

	if (out_flag == OUTPUT_PIN)
		write(fd, "out", 4);
	else
		write(fd, "in", 3);

	close(fd);
	return 0;
}
int gpio_export(unsigned int gpio)
{
	int fd, len;
	char buf[MAX_BUF];

	fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
	if (fd < 0) {
		perror("gpio/export");
		return fd;
	}
	 //if((LEDHandle = fopen(LEDTrigger, "r+")) != NULL){
			  	 	//	fwrite(set_reset, sizeof(char), 1, LEDHandle);
	len = snprintf(buf, sizeof(buf), "%d", gpio);
	write(fd, buf, len);
	close(fd);

	return 0;
}
int Print_H_L_gpio_value(unsigned int gpio)////, unsigned int *value)
{
	int fd;
	char buf[MAX_BUF];
	char ch;
///int v;
	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

	fd = open(buf, O_RDONLY);
	if (fd < 0) {
		perror("gpio/get-value");
		return fd;
	}

	read(fd, &ch, 1);

	if (ch != '0') {
		printf("L");//v=1;///*value = 1;
	} else {
		printf("H");///v=0;///*value = 0;
	}

	close(fd);
	///r///eturn v;
}

int readADCinbuilt(unsigned int pin)
{
     int fd;          //file pointer
     char buf[MAX_BUF];     //file buffer
     char val[4];     //holds up to 4 digits for ADC value

     //Create the file path by concatenating the ADC pin number to the end of the string
     //Stores the file path name string into "buf"
     snprintf(buf, sizeof(buf), "/sys/devices/ocp.3/helper.14/AIN%d", pin);     //Concatenate ADC file name

     fd = open(buf, O_RDONLY);     //open ADC as read only

     //Will trigger if the ADC is not enabled
     if (fd < 0) {
          perror("ADC - problem opening ADC");
     }//end if

     read(fd, &val, 4);     //read ADC ing val (up to 4 digits 0-1799)
     close(fd);     //close file and stop reading

     return atoi(val);     //returns an integer value (rather than ascii)
}//end read ADC()
int main(int argc ,char **argv)//////read status of all inputs of panther safety

{
	int minadc=atoi(argv[1]);
	int i=0;
	for(i=0;i<7;i++)
					{
						if(readADCinbuilt(i)<minadc)
						cout<<"L,";
					else cout<<"H,";

					}
					gpio_export(14 );
						gpio_set_dir(14, INPUT_PIN);
					Print_H_L_gpio_value(14);//p926
					cout<<",";
					gpio_export(30 );
												gpio_set_dir(30, INPUT_PIN);
					Print_H_L_gpio_value(30);//p911
					cout<<",";
					gpio_export(86 );
												gpio_set_dir(86, INPUT_PIN);
					Print_H_L_gpio_value(86);//p827
					cout<<",";
					gpio_export(88 );
												gpio_set_dir(88, INPUT_PIN);
					Print_H_L_gpio_value(88);//p828


					cout<<"\r\n";
		return 0;
}
