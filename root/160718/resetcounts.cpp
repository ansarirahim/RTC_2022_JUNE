
#include <fstream>  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using namespace std;
#define PATH_P927 "/root/160718/countsP927"
#define PATH_P928 "/root/160718/countsP928"
#define PATH_P929 "/root/160718/countsP929"
#define PATH_P930 "/root/160718/countsP930"
#define PATH_RESULT "/root/280917/050817/RtcErrorlog"
#include <iostream>
#include <fstream>
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(){
string line,line2,line3,line4;

std::ofstream fout1;
        fout1.open(PATH_P927);
                fout1<<"0"<<endl;
        fout1.close();

std::ofstream fout2;
        fout2.open(PATH_P928);
                fout2<<"0"<<endl;
        fout2.close();

/////////////////////////////
std::ofstream fout3;
        fout3.open(PATH_P929);
                fout3<<"0"<<endl;
        fout3.close();

/////////////////////////////
std::ofstream fout4;
        fout4.open(PATH_P930);
                fout4<<"0"<<endl;
        fout4.close();

/////////////////////////
std::ofstream fout;
        fout.open(PATH_RESULT);
                fout<<"RTC_COUNTS="<<line<<","<<line2<<","<<line3<<","<<line4<<endl;
        fout.close();


return 0;
}
