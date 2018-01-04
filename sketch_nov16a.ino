int OP;
int OP2;
int OutA = 6; //OutA from encoder is set to pin 6 which is D3 on arduino
int OutB = 5; //OutB from encoder is set to pin 5 which is D2 on arduino
int M1 = 11;  //M1 on encoder set to pin 14 on arduino
int M2 = 12;  //M2 on encoder set to pin 15 on arduino
int a;
int OutC = 8; //OutC from encoder is set to pin which is D5 on arduino
int OutD = 7; //OutD from encoder is set to pin which is D4 on arduino
int M3 = 9; //M1 on encoder 2 set to pin 12
int M4 = 10; //M2 on encoder 2 set to pin 13
int b;

void setup() {
  // put your setup code here, to run once:
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  Serial.begin(9600); //initialize baud rate to 9600
}

void loop() {
  {
    digitalWrite(M1, LOW);
    digitalWrite(M2, HIGH);
    OP = digitalRead(2);
    a+= OP;
    Serial.println(a);
    delay(1);
    while (a >= 500) {
     digitalWrite(M1,HIGH);
     digitalWrite(M2,LOW);
    }
  }
  {
    digitalWrite(M3, LOW);
    digitalWrite(M4, HIGH);
    OP2 = digitalRead(5);
    b+= OP2;
    Serial.println(b);
    delay(1);
    while (b >= 500) {
      digitalWrite(M3,HIGH);
      digitalWrite(M4,LOW);
    }
    }
  }
