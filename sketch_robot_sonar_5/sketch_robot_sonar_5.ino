int IN1 = 7; // Двигатели
int IN2 = 6;
int IN3 = 5;
int IN4 = 4;

int EN1 = 9; // сигналы скорости
int EN2 = 3;

int Trig = 12; // сонар
int Echo = 13;

 

int MAXspeed = 150; // Максимальная скорость робота
int TURNspeed = 130;
int TURNangle = 250;// время поворота, хорошо бы пересчитать в градусы, когда будут датчики положения или скорости.
int BACKtime = 100;
int BACKspeed = 150;

int i;
int t;
int pos=50;

unsigned int impulseTime=0; // Для сонара
unsigned int distance_sm=0; 

void setup()
{
  Serial.begin(9600);
  
  //выводы двигателей
  pinMode (EN1, OUTPUT); // правое колесо
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  
  pinMode (EN2, OUTPUT); // левое колесо
  pinMode (IN4, OUTPUT);
  pinMode (IN3, OUTPUT);
  
  //выводы сонара
  pinMode(Trig, OUTPUT); 
  pinMode(Echo, INPUT); 
}



void loop()
{

pos = dist ();


if (pos>10)
  {
    robo_forth ();
    Serial.print ("Forth| distantion:");
    Serial.println (pos);  
    
  }
  else
  {
    robo_stop ();
    
    robo_back ();
    //robo_stop ();
    
    
    robo_turn ();
    robo_stop ();
    delay(500);
  }
  
}

//functions

//STOP
  int robo_stop () {
    // обнуление сигнала
    analogWrite (EN1, 0);
    analogWrite (EN2, 0);

    }

//FORTH
  int robo_forth () {
      // настройки для езды вперед
    digitalWrite (IN2, HIGH); 
    digitalWrite (IN1, LOW);
  
    digitalWrite (IN3, HIGH);
    digitalWrite (IN4, LOW); 
    
    analogWrite(EN1, MAXspeed);
    analogWrite(EN2, MAXspeed);
    delay(50);
   
  }

//TURN
  int robo_turn () {
    // настройки для кругом
    digitalWrite (IN2, HIGH); 
    digitalWrite (IN1, LOW);
   
    digitalWrite (IN4, HIGH);
    digitalWrite (IN3, LOW); 
    
    // пусть крутится пока <30см
    pos = dist ();
    
    while(pos < 30){
      
      analogWrite(EN1, TURNspeed);
      analogWrite(EN2, TURNspeed); 
      delay(TURNangle); // здесь регулировать время поворота.
      
      pos = dist ();
      robo_stop ();
      delay (100);
      Serial.println (pos);
      Serial.print (" turning.");
      
    }
    
  }

//BACK
  int robo_back () {
    // настройки для езды назад
    digitalWrite (IN1, HIGH); 
    digitalWrite (IN2, LOW);
  
    digitalWrite (IN4, HIGH);
    digitalWrite (IN3, LOW); 
    
    analogWrite(EN1, BACKspeed);
    analogWrite(EN2, BACKspeed);
    
    delay(BACKtime);
    
  }


//Sonar
  int dist () {
    
    digitalWrite(Trig, HIGH); 
    /* Подаем импульс на вход trig дальномера */
    delayMicroseconds(10); // равный 10 микросекундам 
    digitalWrite(Trig, LOW); // Отключаем 
    impulseTime=pulseIn(Echo, HIGH); // Замеряем длину импульса 
    distance_sm=impulseTime/58; // Пересчитываем в сантиметры 
    return distance_sm;
  }
