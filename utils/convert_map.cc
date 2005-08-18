#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 2) cout<<"usage: "<<argv[0]<<" filename "<<endl;

  ifstream ifs;
  ifs.open(argv[1]);

  double x, y, z, bx, by, bz;

  while(ifs.good())
    {
      ifs>>x>>y>>bx>>by;
      cout<<x<<" "<<y<<" "<<0<<" "<<bx<<" "<<by<<" "<<0<<endl;
      cout<<-x<<" "<<y<<" "<<0<<" "<<bx<<" "<<by<<" "<<0<<endl;
      cout<<x<<" "<<-y<<" "<<0<<" "<<bx<<" "<<by<<" "<<0<<endl;
      cout<<-x<<" "<<-y<<" "<<0<<" "<<bx<<" "<<by<<" "<<0<<endl;
    }
}
