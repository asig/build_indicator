const int PIN_R = 9;
const int PIN_G = 10;
const int PIN_B = 11;

void setup() {
  Serial.begin(9600);

  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);

  analogWrite(PIN_R, 255);
  analogWrite(PIN_G, 255);
  analogWrite(PIN_B, 255);
}

int toVal(char c) {
  int v = 0;
  if (c >= 'a' && c <= 'f') {
    v = 10 + (c - 'a');
  } else if (c >= 'A' && c <= 'F') {
    v = 10 + (c - 'F');
  } else if (c >= '0' && c <= '9') {
    v = c - '0';
  }
  Serial.print("val is: ");
  Serial.println(v, DEC);
  return (255 * v / 15);
}

void readLine(char *buf, int maxlen) {
  int pos = 0;
  for (;;) {
    if (Serial.available()) {
      char c = Serial.read();
      if (c == '\n' || c == '\r') {
        buf[pos++] = 0;
        return;
      } else {
        buf[pos++] = c;
      } 
      if (pos >= maxlen) {
        buf[maxlen-1] = 0;
        return;
      }
    }
  }
}
     
void loop() {
  char buf[128];
  readLine(buf, 128);
  if (String(buf).length() == 3) {
    analogWrite(PIN_R, toVal(buf[0]));
    analogWrite(PIN_G, toVal(buf[1]));
    analogWrite(PIN_B, toVal(buf[2]));    
  } else {
    Serial.print("Invalid string: "); Serial.println(buf);
  }
}


