
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
  ifstream myfile (PATH_P927);
  if (myfile.is_open())
  {
     getline (myfile,line) ;
    {
      ////cout << line << '\n';
    }
    myfile.close();
  }

  else cout << "Unable to open file P927"; 
////////////////////////////
ifstream myfile2 (PATH_P928);
  if (myfile2.is_open())
  {
     getline (myfile2,line2) ;
    {
      ////cout << line << '\n';
    }
    myfile2.close();
  }

  else cout << "Unable to open file P928"; 
//////////////////////
ifstream myfile3 (PATH_P929);
  if (myfile3.is_open())
  {
     getline (myfile3,line3) ;
    {
      ////cout << line << '\n';
    }
    myfile3.close();
  }

  else cout << "Unable to open file p929"; 
/////////////////////////////////
ifstream myfile4 (PATH_P930);
  if (myfile4.is_open())
  {
     getline (myfile4,line4) ;
    {
      ////cout << line << '\n';
    }
    myfile4.close();
  }

  else cout << "Unable to open file p930"; 
std::ofstream fout;
        fout.open(PATH_RESULT);
                ///string string5="RTC_COUNTS="+line+","+line2+","+line3+","+line4;
		string string5="RTC_COUNTS="+line4+","+line+","+line2+","+line3;
		fout<<string5<<endl;
        fout.close();
cout<<string5<<endl;

return 0;
}
