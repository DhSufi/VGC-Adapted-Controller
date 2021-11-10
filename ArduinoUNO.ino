bool connection = false;

int pinA = 2;
int pinB = 3;
int pinX = 4;
int pinY = 5;
int pinPLUS = 6;
int pinUp = 7;
int pinDown = 8;
int pinRight = 9;
int pinLeft = 10;

uint32_t myDelay = 200;

void setup() {
  for (int i = 2; i<=11; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }  
  
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  Serial.begin(9600);
  Serial.setTimeout(1);
}


void loop() {

  while (!Serial.available());  // Bucle infinito mientras la condicion sea true, Cuando la condicion sea false, se rompe el bucle y continua la ejecucion

  String data = Serial.readString(); // Leemos la conexion serial como string

  if(connection == false && data == "9"){
    Serial.print("ArduinoController");
    connection = true;
    
    for (int i = 0; i<6; i++){
      digitalWrite(13, HIGH);
      delay(50);
      digitalWrite(13, LOW);
      delay(50);
    }
    
    digitalWrite(13, HIGH);        
  }
  
  else if (connection == true) {
    
    if(data == "A"){
      digitalWrite(pinA, LOW);
      delay(myDelay);
      digitalWrite(pinA, HIGH);
      Serial.println("Button A pushed");
    }

    if(data == "B"){
      digitalWrite(pinB, LOW);
      delay(myDelay);
      digitalWrite(pinB, HIGH);
      Serial.println("Button B pushed");
    }

    if(data == "X"){
      digitalWrite(pinX, LOW);
      delay(myDelay);
      digitalWrite(pinX, HIGH);
      Serial.println("Button X pushed");
    }

    if(data == "Y"){
      digitalWrite(pinY, LOW);
      delay(myDelay);
      digitalWrite(pinY, HIGH);
      Serial.println("Button Y pushed");
    }

    if(data == "P"){
      digitalWrite(pinPLUS, LOW);
      delay(myDelay);
      digitalWrite(pinPLUS, HIGH);
      Serial.println("Button PLUS pushed");
    }

    if(data == "U"){
      digitalWrite(pinUp, LOW);
      delay(myDelay);
      digitalWrite(pinUp, HIGH);
      Serial.println("Button UP pushed");
    }

    if(data == "D"){
      digitalWrite(pinDown, LOW);
      delay(myDelay);
      digitalWrite(pinDown, HIGH);
      Serial.println("Button DOWN pushed");
    }

    if(data == "R"){
      digitalWrite(pinRight, LOW);
      delay(myDelay);
      digitalWrite(pinRight, HIGH);
      Serial.println("Button RIGHT pushed");
    }

    if(data == "L"){
      digitalWrite(pinLeft, LOW);
      delay(myDelay);
      digitalWrite(pinLeft, HIGH);
      Serial.println("Button LEFT pushed");
    }
    
    
  }
}
