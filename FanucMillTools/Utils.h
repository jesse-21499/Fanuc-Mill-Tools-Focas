
#if !__cplusplus_cli 
#error Only for C++/CLI Applications (e.g. Visual Studio Windows Forms Projects)
#endif

#include <string>
namespace Utils 
{bool GetBit(short n, int i)
  {
   return ((n >> i) & 1);
  }
  short ExtractBits(short n, unsigned int i, unsigned int j)
  {   
      unsigned short shifted = n >> i;
      unsigned short mask = (1 << j) - 1;
      return shifted & mask;
  }
} // end of namespace Utils