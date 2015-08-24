#include <stdio.h>
#include <sane/sane.h>

class LinuxScanner {
  
  public:
   void scan();
   void prepare();
   char* statusForHumans(SANE_Status status);

  protected:
    char* imagePath;
};
#

void LinuxScanner::prepare() {
  // SANE_Status status = sane_get_devices(device_list, true);
  printf("aksd");
}

char* LinuxScanner::statusForHumans(SANE_Status sane_status) {
  char* status = "";
  switch(sane_status) {
    case SANE_STATUS_GOOD : 
      status = "Operation completed succesfully.";
      break;
    case SANE_STATUS_UNSUPPORTED: 
      status = "Operation is not supported.";
      break;
    case SANE_STATUS_CANCELLED: 
      status = "Operation was cancelled.";
      break;
     case SANE_STATUS_DEVICE_BUSY: 
      status = "Device is busy---retry later.";
      break;
    case SANE_STATUS_INVAL: 
      status = "Data or argument is invalid.";
      break;
    case SANE_STATUS_EOF: 
      status = "No more data available (end-of-file).";
      break;
    case SANE_STATUS_JAMMED: 
      status = "Document feeder jammed.";
      break;
    case SANE_STATUS_NO_DOCS: 
      status = "Document feeder out of documents.";
      break;
    case SANE_STATUS_COVER_OPEN: 
      status = "Scanner cover is open.";
      break;
    case SANE_STATUS_IO_ERROR: 
      status = "Error during device I/O.";
      break;
    case SANE_STATUS_NO_MEM: 
      status = "Out of memory.";
      break;
    case SANE_STATUS_ACCESS_DENIED: 
      status = "Access to resource has been denied.";
      break;
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
