#include <stdio.h>
#include <sane/sane.h>

#define SANE_MAX_USERNAME_LEN   128
#define SANE_MAX_PASSWORD_LEN   128

class LinuxScanner {
  
  public:
    void scan();
    void prepare();
    char* statusForHumans(SANE_Status status);
    void authCallback(SANE_String_Const c, SANE_Char user[SANE_MAX_USERNAME_LEN], SANE_Char passi[SANE_MAX_PASSWORD_LEN]);
  
  protected:
    char* imagePath;
};

void LinuxScanner::authCallback(SANE_String_Const resource, SANE_Char* username, SANE_Char* password) {

}

void LinuxScanner::prepare() {
  printf("[Getting scanners list]");
  SANE_Int* version = new int[SANE_CURRENT_MAJOR];
  SANE_Status status = sane_init(version, &LinuxScanner::authCallback);
  
  if(status != SANE_STATUS_GOOD) {
    printf("Error initializing SANE");
    return;
  }
}

char* LinuxScanner::statusForHumans(SANE_Status sane_status) {
  char* status = "";
  switch(sane_status) {
    case SANE_STATUS_GOOD : 
      return "Operation completed succesfully.";
    case SANE_STATUS_UNSUPPORTED: 
      status = "Operation is not supported."; break;
    case SANE_STATUS_CANCELLED: 
      status = "Operation was cancelled."; break;
     case SANE_STATUS_DEVICE_BUSY: 
      status = "Device is busy---retry later."; break;
    case SANE_STATUS_INVAL: 
      status = "Data or argument is invalid."; break;
    case SANE_STATUS_EOF: 
      status = "No more data available (end-of-file)."; break;
    case SANE_STATUS_JAMMED: 
      status = "Document feeder jammed."; break;
    case SANE_STATUS_NO_DOCS: 
      status = "Document feeder out of documents."; break;
    case SANE_STATUS_COVER_OPEN: 
      status = "Scanner cover is open."; break;
    case SANE_STATUS_IO_ERROR: 
      status = "Error during device I/O."; break;
    case SANE_STATUS_NO_MEM: 
      status = "Out of memory."; break;
    case SANE_STATUS_ACCESS_DENIED: 
      status = "Access to resource has been denied."; break;
  }
  return status;
}

void LinuxScanner::scan() {
}

int main() {
  LinuxScanner scanner;
  scanner.prepare();  
  return 0;
}
