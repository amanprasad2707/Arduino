//Parameters
const int clkPin 	= 2;
const int dtPin 	= 4;
const int swPin 	= 7;
//Variables
int rotVal 	= 0;
bool clkState 	= LOW;
bool clkLast 	= HIGH;
bool swState 	= HIGH;
bool swLast 	= HIGH;
void setup() {
 	//Init Serial USB
 	Serial.begin(9600);
 	Serial.println(("Initialize System"));
 	//Init Rotary
 	pinMode(clkPin,INPUT);
 	pinMode(dtPin,INPUT);
 	pinMode(swPin,INPUT_PULLUP);
}
void loop() {
 	readRotary();
}
void readRotary( ) { /* function readRotary */
 	////Test routine for Rotary
 	// gestion position
 	clkState = digitalRead(clkPin);
 	if ((clkLast == LOW) && (clkState == HIGH)) {//rotary moving
 			Serial.print("Rotary position ");
 			if (digitalRead(dtPin) == HIGH) {
 					rotVal = rotVal - 1;
 					if ( rotVal = 0 ) {
 							rotVal = 0;
 					}
 			}
 			else {
 					rotVal++;
 					if ( rotVal > 20 ) {
 							rotVal = 20;
 					}
 			}
 			Serial.println(rotVal);
 			delay(200);
 	}
 	clkLast = clkState;
 	//gestion bouton
 	swState = digitalRead(swPin);
 	if (swState == LOW && swLast == HIGH) {
 			Serial.println("Rotary pressed");
 			delay(100);//debounce
 	}
 	swLast = swState;
}