#include <stdio.h>
#include <sane/sane.h>
#include <string.h>
class LinuxScanner {
  
  public:
    string scan();

  protected:
    string imagePath;
};

int main(int argc, const char * argv[]) {
  LinuxScanner scanner;
  return 0;
}
