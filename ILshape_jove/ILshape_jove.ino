#include <FlexiTimer2.h>  //Mega用タイマー割り込み
#include <avr/io.h>       //PWM出力用レジスタ設定

// Assign OUTPUT pins
#define GATE1         22
#define GATE2         23
#define GATE3         24
#define GATE4         25
#define GATE5         26
#define GATE6         27
#define GATE7         28
#define GATE8         29
#define RUN1          30  // Run treadmill 1 at speed1
#define RUN2          31  // Run treadmill 2 at speed1
#define DIRECTION1    32  // of Treadmill
#define DIRECTION2    33
#define DIRECTION3    50
#define RUN3          51
#define DIRECTION4    52
#define RUN4          53
#define FEED1         34
#define FEED2         35
#define DISCARD1      36
#define DISCARD2      37
#define FEED3         14  //changeable
#define FEED4         15
#define DISCARD3      16
#define DISCARD4      17

#define SP1        4
#define SP2        5
#define SP3        6
#define SP4        7

// Assign INPUT pins
#define SENSOR1       38
#define SENSOR2       39
#define SENSOR3       40
#define SENSOR4       41
#define SENSOR5       42
#define SENSOR6       43
#define SENSOR7       44
#define SENSOR8       45
#define MILLSENSOR1   46
#define MILLSENSOR2   47
#define PORKING1      2   //changeable
#define PORKING2      3
#define PORKING3      20
#define PORKING4      21
#define SWITCH1       11
#define SWITCH2       10
#define SWITCH        9
#define SWITCH3       13

#define maxspeed  255  //0~255

int prevPork = 0;
int i = 0;
unsigned long startTime;
unsigned long stopTime;
bool startTask = false;
short counter1 = 0;
bool endend = false;
#define TH  30//number of trial

void setup() {
  InitPinMode();
  pinMode(SWITCH3, INPUT_PULLUP);
  pinMode(SWITCH1, INPUT_PULLUP);
  pinMode(SP4, OUTPUT);
  digitalWrite(SP3, 0);
  digitalWrite(SP4, 0);
  digitalWrite(RUN1, HIGH);
  digitalWrite(RUN2, HIGH);
  digitalWrite(RUN3, HIGH);
  digitalWrite(RUN4, HIGH);
  digitalWrite(FEED1, LOW);
  digitalWrite(FEED4, LOW);
  digitalWrite(FEED3, LOW);
  digitalWrite(GATE5, LOW);
  digitalWrite(GATE7, HIGH);
  digitalWrite(GATE1, HIGH);
  digitalWrite(GATE2, HIGH);
  digitalWrite(DIRECTION3, HIGH);
  digitalWrite(DIRECTION4, HIGH);
  Serial.begin(9600);
  //PWM波の出力用設定---------------------------------------------
  pinMode(12, OUTPUT);//12camera

  //ユーザ設定部
  unsigned int frq = 50; // 周波数←ここカメラの設定と一致させる
  float duty = 0.5; // 指定したいデューティ比
  // モード指定
  TCCR1A = 0b00000001;
  TCCR1B = 0b00010010;  //分周８
  // TOP値指定
  OCR1A = (unsigned int)(1000000 / frq);
  // Duty比指定
  OCR1B = (unsigned int)(1000000 / frq * duty);
  //-----------------------------------------------------------
}

void loop() {
  if (startTask) {
    if (counter1 == TH) {
      endend = true;
    }

    if (digitalRead(PORKING2) && prevPork == 0) {
      startTime = millis();
      digitalWrite(FEED1, LOW);
      digitalWrite(FEED3, LOW);
      digitalWrite(FEED4, LOW);
      digitalWrite(GATE5, LOW);
      digitalWrite(DIRECTION4, HIGH);
      analogWrite(SP4, 120);
      delay(5000);
      analogWrite(SP4, 0);
      prevPork = 1;
    }

    if (digitalRead(PORKING3) && prevPork == 1) {
      stopTime = millis();
      Serial.println(stopTime - startTime);
      analogWrite(SP4, 0);
      digitalWrite(FEED1, LOW);
      digitalWrite(FEED3, LOW);
      digitalWrite(FEED4, LOW);
      digitalWrite(GATE1, HIGH);
      digitalWrite(GATE5, HIGH);
      digitalWrite(GATE7, LOW);
      prevPork = 2;
    }

    if (digitalRead(PORKING1) && prevPork == 2) {
      digitalWrite(FEED1, HIGH);
      digitalWrite(FEED4, LOW);
      digitalWrite(FEED3, LOW);
      digitalWrite(GATE5, HIGH);
      prevPork = 0;
      counter1 = counter1 + 1;
    }

  }


  //外部スイッチPWNオンオフ-------------------------------------
  if (digitalRead(SWITCH1) == LOW || endend == true) {
    if ( TCCR1A == 0b00100001 ) {
      TCCR1A = 0b00000001;
    }
    else if ( TCCR1A == 0b00000001 ) {
      TCCR1A = 0b00100001;
    }
    delay(1000);

    if (startTask) {
      ///START
      digitalWrite(SP3, 0);
      digitalWrite(SP4, 0);
      digitalWrite(RUN3, HIGH);
      digitalWrite(RUN4, HIGH);
      digitalWrite(FEED1, LOW);
      digitalWrite(FEED3, LOW);
      digitalWrite(FEED4, LOW);
      digitalWrite(GATE5, LOW);
      digitalWrite(DIRECTION4, HIGH);
      endend = false;
      counter1 = 0;
    }
    else {
      ///END
      digitalWrite(SP3, 0);
      digitalWrite(SP4, 0);
      digitalWrite(RUN3, HIGH);
      digitalWrite(RUN4, HIGH);
      digitalWrite(FEED1, LOW);
      digitalWrite(FEED3, LOW);
      digitalWrite(FEED4, LOW);
      digitalWrite(GATE5, LOW);
      digitalWrite(DIRECTION4, HIGH);
    }
    startTask = !startTask;

    //---------------------------------------------------------
  }
}
