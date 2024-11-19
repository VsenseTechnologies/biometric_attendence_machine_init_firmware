#include<SPIFFS.h>

bool writeFile(const char *path,const char *message) {
  //opening the file
  File file=SPIFFS.open(path,FILE_WRITE);

  //checking if the file opened or not
  if(!file) {
    Serial.println("failed to open file");
    return false;
  }

  //writing the message to file
  if(!file.print(message)){
    //closing the file
    file.close();
    return false;
  }

  //closing the file
  file.close();
  return false;
}

String readFile(const char *path) {

  File file = SPIFFS.open(path);
  //opening the file
  if(!file) {
    Serial.println("failed to open file");
    return "";
  }

  String data="";

  //checking for the file content
  while(file.available()) {
    data+=char(file.read());
  }

  //closing the file
  file.close();

  return data;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  if(!SPIFFS.begin(true)) {
    Serial.println("SPIFFS file system mount failed");

    //indicating the SPIFFS file system mount failure 
    while(1) {
      Serial.println("failed to mount the file system");
      delay(1000);
    }
  }

  Serial.println("file system mounted successfully");

  writeFile("/wifi_config.json","{\"uid\":\"123\",\"ssid\":\"undefined\",\"pwd\":\"password\"}");


}

void loop() {
  // put your main code here, to run repeatedly:
  String data=readFile("/wifi_config.json");

  Serial.println(data);

  delay(3000);
}
