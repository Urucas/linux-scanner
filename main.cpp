#include <stdio.h>
#include <sane/sane.h>

#define SANE_MAX_USERNAME_LEN   128
#define SANE_MAX_PASSWORD_LEN   128

typedef void (*SANE_Authorization_Callback)(SANE_String_Const resource,           SANE_Char username[SANE_MAX_USERNAME_LEN], SANE_Char password[SANE_MAX_PASSWORD_LEN]);

class LinuxScanner {
  
  public:
    void scan();
    void prepare();
    SANE_Auth_Callback authorize;
    static void authCallback(SANE_String_Const c, SANE_Char user[SANE_MAX_USERNAME_LEN], SANE_Char passi[SANE_MAX_PASSWORD_LEN]);
  
  protected:
    char* imagePath;
};

void LinuxScanner::authCallback(SANE_String_Const resource, SANE_Char* username, SANE_Char* password) {

}

void LinuxScanner::prepare() {
  printf("[Getting scanners list]");
  SANE_Int version[1] = {SANE_CURRENT_MAJOR};
  SANE_Status status = sane_init(version, authorize);
  
  SANE_String_Const strstatus = sane_strstatus(status);
  printf("%s\n", strstatus);

  if(status != SANE_STATUS_GOOD) {
    printf("Error initializing SANE");
    return;
  }
}

void LinuxScanner::scan() {
}

int main() {
  LinuxScanner scanner;
  scanner.prepare();  
  return 0;
}
