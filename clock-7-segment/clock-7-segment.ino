int HH = 01;
int MM = 00;
int a, b, c, d;
unsigned long previousMillis = 0;
long interval = 1000;
byte on = 0;
int i = 5;

int segA = D0;
int segB = D1;
int segC = D2;
int segD = D3;
int segE = D4;
int segF = D5;
int segG = D6;

int digit1 = D7;
int digit2 = D8; 
int digit3 = 3; // RX
int digit4 = 1; // TX
int dot = 9; // SD2

void setup() {
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
  pinMode(dot, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval)
  { MM = MM+1;
  if (MM>59){MM = 0; HH = HH+1;}
  if (HH>12){HH = 1;}
  on =!on;
  digitalWrite(dot, !on);
  previousMillis = currentMillis;
  }

    a = int(HH/10);
    b = int(HH%10);
    c = int(MM/10);
    d = int(MM%10);
    displayNumber(a);
    digitalWrite(digit1, HIGH);
    digitalWrite(digit2, LOW);
    digitalWrite(digit3, LOW);
    digitalWrite(digit4, LOW);
    delay(i);
    displayNumber(b);
    digitalWrite(digit1, LOW);
    digitalWrite(digit2, HIGH);
    digitalWrite(digit3, LOW);
    digitalWrite(digit4, LOW);
    delay(i);
    displayNumber(c);
    digitalWrite(digit1, LOW);
    digitalWrite(digit2, LOW);
    digitalWrite(digit3, HIGH);
    digitalWrite(digit4, LOW);
    delay(i);
    displayNumber(d);
    digitalWrite(digit1, LOW);
    digitalWrite(digit2, LOW);
    digitalWrite(digit3, LOW);
    digitalWrite(digit4, HIGH);
    delay(i);
  }

void displayNumber(int numbertoDisplay){
  switch(numbertoDisplay){
    case 0:
      digitalWrite(segA, LOW );
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);     //Generating 8
      digitalWrite(segF, LOW);
      digitalWrite(segG, HIGH);
      break;

    case 1:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, HIGH);       //Generating 1
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;

    case 2:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, HIGH);      //Generating 2
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, LOW);
      break;

    case 3:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);      //Generating 3
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segF, LOW);
      break;

    case 4:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);     //Generating 4
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;

    case 5:
      digitalWrite(segA, LOW);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      digitalWrite(segE, HIGH);     //Generating 5
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;

    case 6:
      digitalWrite(segA, LOW);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);    //Generating 6
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;

    case 7:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);   //Generating 7
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      break;

    case 8:
      digitalWrite(segA, LOW );
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);     //Generating 8
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;

    case 9:
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      digitalWrite(segE, HIGH);    //Generating 9
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      break;

  }
}
