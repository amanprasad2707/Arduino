#define led1 D5
#define led2 D6
#define led3 D7
void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led1, HIGH);
  delay(500);
  digitalWrite(led1,LOW);
  delay(500);
  digitalWrite(led2, HIGH);
  delay(500);
  digitalWrite(led2,LOW);
  delay(500);
  digitalWrite(led3, HIGH);
  delay(500);
  digitalWrite(led3,LOW);
  delay(500);
}
