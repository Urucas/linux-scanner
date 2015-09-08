#include <stdio.h>
#include <sane/sane.h>
#include <png.h>
#include <string.h>
#include <alloca.h>
#define SANE_MAX_USERNAME_LEN   128
#define SANE_MAX_PASSWORD_LEN   128

typedef void (*SANE_Authorization_Callback)(SANE_String_Const resource,  SANE_Char username[SANE_MAX_USERNAME_LEN], SANE_Char password[SANE_MAX_PASSWORD_LEN]);

class LinuxScanner {
  
  public:
    int scan();
    int prepare();
    static void authCallback(SANE_String_Const c, SANE_Char user[SANE_MAX_USERNAME_LEN], SANE_Char passi[SANE_MAX_PASSWORD_LEN]);

  protected:
    char* imagePath;
    void log(char* msg);
    void log(char* msg, SANE_Status status);
    const SANE_Device* selected_device;
    bool isGoood(SANE_Status status);
    SANE_Status read(SANE_Handle device);
    FILE* createTmpFile();
	int getOptionInt(SANE_Handle device, SANE_Option_Descriptor option, int i); 
};

void LinuxScanner::authCallback(SANE_String_Const resource, SANE_Char* username, SANE_Char* password) {
}

void LinuxScanner::log(char* msg) {
  printf("[%s]\n", msg);
}

void LinuxScanner::log(char* msg, SANE_Status status) {
  printf("[%s]\n", msg);
  printf("[%s]\n", sane_strstatus(status));
}

int LinuxScanner::prepare() {
  this->log("Initializing sane");
  SANE_Int version[1] = {SANE_CURRENT_MAJOR};
  SANE_Status status = sane_init(version, &LinuxScanner::authCallback);
 
  if(!this->isGoood(status)) {
    this->log("Error initializing SANE", status);
    return 1;
  }
  
  const SANE_Device **device_list;
  this->log("Getting available devices");
  status = sane_get_devices(&device_list, SANE_TRUE);
  if(!this->isGoood(status)) {
    this->log("[Error getting devices list]\n", status);
    return 1;
  }
  int i = 0;
  for (; device_list[i]; ++i) {
    this->log("Availabled devices");
    this->log((char*)device_list[i]->model);
    // printf ("device `%s' is a %s %s %s\n", device_list[i]->name, device_list[i]->vendor, device_list[i]->model, device_list[i]->type);
  }
  if(i==0) {
    this->log("No devices available");
    return 1;
  }
  this->selected_device = device_list[0];
  return 0;
}

bool LinuxScanner::isGoood(SANE_Status status) {
  if(status != SANE_STATUS_GOOD) {
    return false;
  }
  return true;
}

FILE* LinuxScanner::createTmpFile() {
  return tmpfile();
}

SANE_Status LinuxScanner::read(SANE_Handle device) {
  
  SANE_Byte buffer[1024*1024];
  SANE_Int len = 0;
  SANE_Status status;
  SANE_Word total_bytes = 0;
  
  //FILE*tmp = this->createTmpFile();
  /*
  png_structp png_ptr = NULL;
  png_infop info_ptr = NULL;
  png_bytep row = NULL;
  
  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  info_ptr = png_create_info_struct(png_ptr);
  
  png_init_io(png_ptr, tmp);
  */
  while(1) {
    status = sane_read(device, buffer, sizeof(buffer), &len);
    total_bytes+= (SANE_Word) len;
    // printf("%d\n", total_bytes);
    if(!this->isGoood(status)) {
      this->log("eof", status);
      break;
    }
  }
  sane_close(device);
  if(status == SANE_STATUS_EOF) {
    printf("end of file\n");
    status = SANE_STATUS_GOOD;
  }

  return status;
}

int LinuxScanner::getOptionInt(SANE_Handle device, SANE_Option_Descriptor option, int i) {
  printf("%s\n", (char *)option->name);
  printf("%s\n", (char *)option->desc);
  int value = 0;
  void* val;
  val = alloca(option->size);
  sane_control_option(device, i, SANE_ACTTION_GET_VALUE, val, 0);
  if(option->type == SANE_TYPE_INT)
    value = *(SANE_Int *)val;
  else
    value = (int) (SANE_UNFIX (*(SANE_Fixed *) val) + 0.5);
  return value;
}

int LinuxScanner::scan() {

  this->log("Trying to open device");
  this->log((char *)this->selected_device->model);
  static SANE_Handle device;
  SANE_Status status = sane_open(this->selected_device->name, &device);
  if(!this->isGoood(status)) {
    this->log("Error trying to open device", status);
    return 1;
  }
  if(device) {
    const SANE_Option_Descriptor *option;
	
	SANE_Int num_options = 0;
	status = sane_control_option(device, 0, SANE_ACTION_GET_VALUE, &num_options, 0);
	 if(!this->isGoood(status)) {
      this->log("Error getting scanner options", status);
      return 1;
    }
 
	for(int i=0;i<num_options;i++) {
      option = sane_get_option_descriptor(device, i);
	  if(!SANE_OPTION_IS_SETTABLE(option->cap))
	    continue;
	
	  if(!strcmp(option->name,"br-y")) {
	    int val = this->getOptionInt(&device, &option, i);
		  printf("%d\n", resol);
	  }
	  /*
 	  if(!strcmp(option->name,"resolution")) {
		printf("%s\n", (char *)option->name);
	    printf("%s\n", (char *)option->desc);
		const SANE_Option_Descriptor* resopt;
		resopt = sane_get_option_descriptor(device, i);
		printf("%d\n", resopt->size);
	  }
	  */
	  /*
	  if(!strcmp(option->name,"resolution")) {
	  	printf("%s\n", (char *)option->name);
		int resol = 0;
		const SANE_Option_Descriptor* resopt;
		resopt = sane_get_option_descriptor(device, i);
		val = alloca(resopt->size);
		sane_control_option(device, i, SANE_ACTION_GET_VALUE, val, 0);
		resol = *(SANE_Int *)val;
		printf("%d\nn", resol);
	  }  
	
	  // setting full width
	  *
	  // setting full height
	  if(!strcmp(option->name,"tl-y")) {
	  	printf("%s\n", (char *)option->name);
		sane_control_option(device, i, SANE_ACTION_SET_VALUE, &height, 0);
		printf("%s", sane_strstatus(status));
	  }
	  */
	}
	return 0;
	status = sane_start(device);
    if(!this->isGoood(status)) {
      this->log("Error trying to start scanner", status);
      return 1;
    }
    
    status = sane_set_io_mode(device, SANE_TRUE);
    if(!this->isGoood(status)) {
      this->log("Error setting scanner IO mode", status);
      return 1;
    }

	/* 
    SANE_Parameters* params;	
    status = sane_get_parameters(device, params);
 
    printf("scanning image: %dx%d", params->pixels_per_line, params->lines); 
    printf("bytes x line: %d\n", params->bytes_per_line); 
    printf("pixels x line: %d\n", params->pixels_per_line); 
    printf("lines: %d\n", params->lines); 
    printf("depth: %d\n", params->depth); 
*/
    
    status = this->read(device);
    if(!this->isGoood(status)) {
      this->log("An error ocurr while reading scanner data", status);
      return 1;
    }
    
  }else{
    this->log("An error ocurr while trying to open the device!");
    return 1;
  }
  return 0;
}

int main() {
  LinuxScanner scanner;
  int fail = scanner.prepare();  
  if(fail) return 1;
  fail = scanner.scan();
  if(fail) return 1;
  return 0;
}
