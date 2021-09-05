
#include "src/FileCommand.h"

FileCommand fcmd;

void setup() {

fcmd.addCommand("HELLO", sayHello);        // Echos the string argument back
fcmd.setDefaultHandler(unrecognized);      // Handler for command that isn't matched


}

void loop() {
  char a = 'a';
  fcmd.parse(a);

}


void sayHello() {
  char *arg;
  arg = fcmd.next();    // Get the next argument from the SerialCommand object buffer
  if (arg != NULL) {    // As long as it existed, take it
    Serial.print("Hello ");
    Serial.println(arg);
  }
  else {
    Serial.println("Hello, whoever you are");
  }
}

// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
  Serial.println("What?");
}
