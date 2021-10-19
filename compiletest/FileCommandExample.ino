
#include "src/FileCommand.h"
#include "SPIFFS.h"


FileCommand fcmd;

void setup() {

  Serial.begin(115200);

  fcmd.addCommand("HELLO", sayHello);         //echos the string argument back
  fcmd.addCommand("pCom", pCommand);          //converts arguments to integer
  fcmd.setDefaultHandler(unrecognized);       //handler for command that isn't matched

//initialise file system
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

//open file and parse
  File file = SPIFFS.open("/cfg.txt");
  if(!file){
    Serial.println("Failed opening /cft.txt");
    return;
  }
  Serial.print("Start parsing");
  Serial.println();
  Serial.println();
  while(file.available()){
    fcmd.parse(file.read());
  }
  file.close();



}

void loop() {


}


void sayHello() {
  char *arg;
  arg = fcmd.next();                        //get the next argument from the SerialCommand object buffer
  if (arg != NULL) {                        //as long as it existed, take it
    Serial.print("Hello ");
    Serial.println(arg);
  }
  else {
    Serial.println("Hello, whoever you are");
  }
}

void pCommand() {
  int aNumber;
  char *arg;

  Serial.println("processing command");
  arg = fcmd.next();
  if (arg != NULL) {
    aNumber = atoi(arg);                    //converts a char string to an integer
    Serial.print("First argument was: ");
    Serial.println(aNumber);
  }
  else {
    Serial.println("No arguments");
  }

  arg = fcmd.next();
  if (arg != NULL) {
    aNumber = atol(arg);
    Serial.print("Second argument was: ");
    Serial.println(aNumber);
  }
  else {
    Serial.println("No second argument");
  }
}



// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
  Serial.print("unrecognized parameters: ");
  Serial.println(command);                    //print which command is meant
}
