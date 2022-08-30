/*
 *  Initial functions in setup
 */

 void InitPinMode(){
  
  // OUTPUT pins
  for(int i=22;i<=37;i++){pinMode(i, OUTPUT); digitalWrite(i, LOW);}
  int i;
  i=FEED3;    pinMode(i, OUTPUT); digitalWrite(i, LOW);
  i=FEED4;    pinMode(i, OUTPUT); digitalWrite(i, LOW);
  i=DISCARD3; pinMode(i, OUTPUT); digitalWrite(i, LOW);
  i=DISCARD4; pinMode(i, OUTPUT); digitalWrite(i, LOW);
  for(int i=50;i<=53;i++){pinMode(i, OUTPUT); digitalWrite(i, LOW);}
  
  // INPUT pins
  for(int i=38;i<=47;i++){pinMode(i, INPUT);}
  pinMode(PORKING1, INPUT);
  pinMode(PORKING2, INPUT);
  pinMode(PORKING3, INPUT);
  pinMode(PORKING4, INPUT);

  // other control pins
 }
