#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
#define PATH_CFG_P927  "/root/160718/cfgp927"
#define PATH_CFG_P928  "/root/160718/cfgp928"
#define PATH_CFG_P929  "/root/160718/cfgp929"
#define PATH_CFG_P930  "/root/160718/cfgp930"
int main(int argc, char** argv)
{
    //cout << "You have entered " << argc
      ///   << " arguments:" << "\n";
 
 //   for (int i = 0; i < argc; ++i)
   //     cout << argv[i] << "\n";
if(argc>3)
{
 std::ofstream fout;
        fout.open(PATH_CFG_P927);
                fout<<argv[1]<<endl;///string5<<endl;
        fout.close();
        fout.open(PATH_CFG_P928);
                fout<<argv[2]<<endl;///string5<<endl;
        fout.close();
fout.open(PATH_CFG_P929);
                fout<<argv[3]<<endl;///string5<<endl;
        fout.close();
        fout.open(PATH_CFG_P930);
                fout<<argv[4]<<endl;///string5<<endl;
        fout.close();
}

    return 0;
}
