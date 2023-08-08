int x = 0;
int a = D0;
int b = D1;
int c = D2;
int d = D3;
int e = D4;
int f = D5;
int g = D6;

byte SW0 = 1;  // TX
byte SW1 = 3;  // RX
void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  Serial.begin(9600);
  Serial.println("Counting begins..");
  pinMode(SW0, INPUT);
  pinMode(SW1, INPUT);

  digitalWrite(SW0, HIGH);
  digitalWrite(SW1, HIGH);
}

void loop() {
  int plus = digitalRead(SW0);
  int minus = digitalRead(SW1);
  if (plus == LOW) {
  x = x+1;
  delay(200);
  }
  if (minus == LOW) {
  x = x-1;
  delay(200);
  }
  displayNumber(x);
  delay(100);
}

void displayNumber(int numbertoDisplay){
  switch(numbertoDisplay){
    case 0:
      digitalWrite(a, LOW );
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);     //Generating 8
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;

    case 1:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);       //Generating 1
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;

    case 2:
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);      //Generating 2
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
      break;

    case 3:
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);      //Generating 3
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
      break;

    case 4:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);     //Generating 4
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;

    case 5:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, HIGH);     //Generating 5
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;

    case 6:
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);    //Generating 6
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;

    case 7:
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);   //Generating 7
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;

    case 8:
      digitalWrite(a, LOW );
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);     //Generating 8
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;

    case 9:
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, HIGH);    //Generating 9
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
      break;

  }
}
