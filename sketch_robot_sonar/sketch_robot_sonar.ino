int IN1 = 7; // Input1 подключен к выводу 5 
int IN2 = 6;
int IN3 = 5;
int IN4 = 4;

int EN1 = 9;
int EN2 = 3;

int Trig = 12;
int Echo = 13;

int LED = 13;
int MAXspeed = 120;
int i;
int t;

void setup()
{
  Serial.begin(9600);
  
  //выводы двигателей
  pinMode (EN1, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (EN2, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (IN3, OUTPUT);
  
  //выводы сонара
  pinMode(Trig, OUTPUT); 
  pinMode(Echo, INPUT); 
}

unsigned int impulseTime=0; 
unsigned int distance_sm=0; 

void loop()
{

int pos = dist ();

if (pos>10)
  {
    robo_forth ();
  }
  else
  {
    robo_turn ();
  }
  
 // robo_forth ();
 // robo_stop(); // остановка робота
 // delay(500);
  
 // robo_back ();
 // robo_stop();
 // delay(500);
 // конец блока
  
  
  
 
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
  
 // for (i = 50; i <= 150; ++i) // увеличение скорости
 // {
   i = MAXspeed;
      analogWrite(EN1, i);
      analogWrite(EN2, i);
      delay(50);
 // }
}

//TURN
int robo_turn () {
 // настройки для кругом
  digitalWrite (IN2, HIGH); 
  digitalWrite (IN1, LOW);
 
  digitalWrite (IN4, HIGH);
  digitalWrite (IN3, LOW); 
  
  //for (i = 50; i <= 150; ++i) // увеличение скорости
  //{
    i = MAXspeed;
      analogWrite(EN1, i);
      analogWrite(EN2, i);
      delay(1);
  //}
  delay(50); // здесь регулировать угол поворота.
}

//BACK
int robo_back () {
    // настройки для езды назад
  digitalWrite (IN1, HIGH); 
  digitalWrite (IN2, LOW);

  digitalWrite (IN4, HIGH);
  digitalWrite (IN3, LOW); 
  
  //for (i = 50; i <= 200; ++i) // увеличение скорости
  //{
    i = MAXspeed;
      analogWrite(EN1, i);
      analogWrite(EN2, i);
      delay(50);
  //}
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
