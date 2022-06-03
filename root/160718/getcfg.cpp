

#include <fstream>  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
#define PATH_CFG_P927  "/root/160718/cfgp927"
#define PATH_CFG_P928  "/root/160718/cfgp928"
#define PATH_CFG_P929  "/root/160718/cfgp929"
#define PATH_CFG_P930  "/root/160718/cfgp930"
/////////////////////
#include <iostream>
#include <fstream>
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(){
string line1,line2,line3,line4;
  ifstream myfile1 (PATH_CFG_P927);
  if (myfile1.is_open())
  {
     getline (myfile1,line1) ;
    {
      ////cout << line << '\n';
    }
    myfile1.close();
  }
  ifstream myfile2 (PATH_CFG_P927);
  if (myfile2.is_open())
  {
     getline (myfile2,line2) ;
    {
      ////cout << line << '\n';
    }
    myfile2.close();
  }
  ifstream myfile3 (PATH_CFG_P929);
  if (myfile3.is_open())
  {
     getline (myfile3,line3) ;
    {
      ////cout << line << '\n';
    }
    myfile3.close();
  }

  ifstream myfile4 (PATH_CFG_P930);
  if (myfile4.is_open())
  {
     getline (myfile4,line4) ;
    {
      ////cout << line << '\n';
    }
    myfile4.close();
  }

////////////////////////////
cout<<line1<<" "<<line2<<" "<<line3<<" " <<line4<<endl;

return 0;///atoi(line.c_str());
}
