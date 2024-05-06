int in1=7,in2=6,in3=2,in4=4;
int enable1=5,enable2=3;
int tiempo;
int TRIGGER = 9, ECHO = 8;
int sen1=10;
int sen2=11;
int sen3=12;
bool inDanger = false;
bool sensors[3];

void setup(){
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  analogWrite(enable1, 180);
  analogWrite(enable2, 255);
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT); /*activación del pin 9 como salida: para el pulso ultrasónico*/
  pinMode(ECHO, INPUT); /*activación del pin 8 como entrada: tiempo del rebote del ultrasonido*/ 
  delay(4900);
}

void loop(){
    fight();
    recover();
}

void read_sensors(){
  sensors[0]=digitalRead(sen1);
  sensors[1]=digitalRead(sen2);
  sensors[2]=digitalRead(sen3);

//  Serial.println(sensors[0]);
//  Serial.println(sensors[1]);
//  Serial.println(sensors[2]);
}

bool detect_danger(){
  read_sensors();
  for(int i=0; i<3; i++){
    if (sensors[i]){
      //Serial.println("Blanco");
      return true;
      }
    }
    //Serial.println("Negro");
    return false;
  }

void fight(){    
    while(true){
        if (!discover()){
            break;
        }
        if (!strike()){
            break;
        }
    }
}

void recover(){
    while(true){
       read_sensors();
        if (sensors[0]) {
            if (recover_from_front()) {
                break; // Sale del bucle while
            } else {
                continue; // Continúa con la siguiente iteración del bucle while
            }
        }
        if (sensors[1]) {
            if (recover_from_right()) {
                break; // Sale del bucle while
            } else {
                continue; // Continúa con la siguiente iteración del bucle while
            }
        }
        if (sensors[2]) {
            if (recover_from_left()) {
                break; // Sale del bucle while
            } else {
                continue; // Continúa con la siguiente iteración del bucle while
            }
        }
        break; // Sale del bucle while si ninguna condición se cumple
    }
}

bool recover_from_right(){
    //TODO
    adelante();
    delay(500);
    izquierda();
    delay(1000);
    adelante();
    delay(500);
    return !detect_danger();
}

bool recover_from_left(){
    //TODO
    adelante();
    delay(500);
    derecha();
    delay(1000);
    adelante();
    delay(500);
    return !detect_danger();
}

bool recover_from_front(){
   //TODO
    atras();
    delay(1000);
    izquierda();
    delay(1000);
    adelante();
    delay(500); 
    derecha();
    delay(1000);
    adelante();
    delay(500);
    return !detect_danger();
}


bool is_enemy_in_sight(){
    delay(10);
    return measure_distance() < 170;
}

int measure_distance(){
    //TODO
    int distance;
    digitalWrite(TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER, LOW);
    // Calcula la distancia midiendo el tiempo del estado alto del pin ECHO
    tiempo = pulseIn(ECHO, HIGH);
    // La velocidad del sonido es de 340m/s o 29 microsegundos por centimetro
    distance = tiempo / 58;
    //manda la distancia al monitor serie
   
//    Serial.print(distance);
//    Serial.println("cm");
//    delay(100);
    return distance;
}

bool discover(){
    while(!is_enemy_in_sight()){
        derecha();
        delay(1); 
        Serial.println("buscando");
        if(detect_danger()){
          return false;
        }
    }
    return true;
}

bool strike(){
    while(is_enemy_in_sight()){
        adelante();
        delay(500);
        if(detect_danger()){
          return false;
        }
    }
    return true;
}
void detener() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void izquierda() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void derecha() {
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in3, LOW);
}
void adelante() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in3, LOW);
}
void atras() {
  digitalWrite(in2, HIGH);  
  digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
  
