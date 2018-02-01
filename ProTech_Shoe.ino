void setup() {  
  int count=0;
  Serial.begin(115200);
  while (!Serial);

  // put your setup code here, to run once:

}

void loop() {
  int count;
  while (Serial.available() > 0);
    int inCommand = Serial.read();
    Serial.println(inCommand);
      delay(500);
  // put your main code here, to run repeatedly:

}
