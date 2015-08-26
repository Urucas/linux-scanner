#include <stdio.h>
#include <sane/sane.h>

#define SANE_MAX_USERNAME_LEN   128
#define SANE_MAX_PASSWORD_LEN   128

typedef void (*SANE_Authorization_Callback)(SANE_String_Const resource,  SANE_Char username[SANE_MAX_USERNAME_LEN], SANE_Char password[SANE_MAX_PASSWORD_LEN]);

class LinuxScanner {
  
  public:
    int scan();
    int prepare();
    static void authCallback(SANE_String_Const c, SANE_Char user[SANE_MAX_USERNAME_LEN], SANE_Char passi[SANE_MAX_PASSWORD_LEN]);
    const SANE_Device **device_list;

  protected:
    char* imagePath;
    void log(char* msg);
    SANE_Device selected_device;
};

void LinuxScanner::authCallback(SANE_String_Const resource, SANE_Char* username, SANE_Char* password) {
  
}

void LinuxScanner::log(char* msg) {
  printf("[%s]\n", msg);
}

int LinuxScanner::prepare() {
  this->log("Initializing sane");
  SANE_Int version[1] = {SANE_CURRENT_MAJOR};
  SANE_Status status = sane_init(version, &LinuxScanner::authCallback);
  
  // SANE_String_Const strstatus = sane_strstatus(status);
  if(status != SANE_STATUS_GOOD) {
    this->log("Error initializing SANE");
    return 1;
  }

  this->log("Getting available devices");
  status = sane_get_devices(&device_list, SANE_TRUE);
  if(status != SANE_STATUS_GOOD) {
    this->log("[Error getting devices list]\n");
    return 1;
  }
  // Testing device
  // Device ready EPSON NX TX SX100/ME300/PX-401A
  
  int i = 0;
  for (; device_list[i]; ++i) {
    printf ("device `%s' is a %s %s %s\n",                                 device_list[i]->name, device_list[i]->vendor,                              device_list[i]->model, device_list[i]->type);
  }
  if(i==0) {
    this->log("No devices available");
    return 1;
  }
  return 0;
}

int LinuxScanner::scan() {
  return 0;
}

int main() {
  LinuxScanner scanner;
  int fail = scanner.prepare();  
  if(fail) return 1;
  
  return 0;
}
