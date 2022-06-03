
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
string line,line2,line3,line4;
  ifstream myfile (PATH_CFG_P927);
  if (myfile.is_open())
  {
     getline (myfile,line) ;
    {
      ////cout << line << '\n';
    }
    myfile.close();
  }

  else cout << "Unable to open file cfgP927"; 
////////////////////////////
cout<<line<<endl;

return atoi(line.c_str());
}
