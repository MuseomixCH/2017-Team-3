

 const int S1Pin = A0;
 const int S2Pin = A2;
 const int S3Pin = A4;
 const int RPin = 11;
 const int GPin = 9;
 const int BPin = 10;

  int numCards = 4;
 
  int TotalCount = 0;
  int count1 = 0;
  int count2 = 0;
  int count3 = 0;

  int timeoutWait = 7000;
  int cardWait = 500;

  unsigned long Timeout = 0;

  int S1Read = 0;
  int S2Read = 0;
  int S3Read = 0;

double threshold = 1;

void setup() {
pinMode(S1Pin, INPUT);
pinMode(S2Pin, INPUT);
pinMode(S3Pin, INPUT);
pinMode(RPin, OUTPUT);
pinMode(GPin, OUTPUT);
pinMode(BPin, OUTPUT);

  Serial.begin(115200);
}

void loop() {

  S1Read = digitalRead(S1Pin);
  S2Read = digitalRead(S2Pin);
  S3Read = digitalRead(S3Pin);

  //// Debugging \\\\
/*
  Serial.print(S1Read);
  Serial.print(S2Read);
  Serial.print(S3Read);
  /*
  digitalWrite(RPin, HIGH);
  Serial.print("LED on");
  delay(1000);
  digitalWrite(RPin, LOW);
  Serial.print("LED off");
  delay(1000);
  */

//// Check for card drops \\\\

  if(S1Read < threshold)
  {
    //Serial.print("Card ");
    //digitalWrite(RPin, HIGH);
    count1++;
    TotalCount++;
    delay(cardWait); //avoid reading the same card twice
    Timeout = millis() + timeoutWait; // time out
    /*Serial.print("new time: ");
    Serial.print(Timeout);
    Serial.print("\n");
    Serial.print("current time: ");
    Serial.print(millis());
    Serial.print("\n");
    
    digitalWrite(RPin, LOW);
*/
  }
  if(S2Read < threshold)
  {
    //Serial.print("Card2 ");
    //digitalWrite(GPin, HIGH); 
    count2++;
    TotalCount++;
    delay(cardWait); //avoid reading the same card twice
    Timeout = millis() + timeoutWait; // time out
    /*Serial.print("new time: ");
    Serial.print(Timeout);
    Serial.print("\n");
    Serial.print("current time: ");
    Serial.print(millis());
    Serial.print("\n");
    digitalWrite(GPin, LOW);
    */
  }
  if(S3Read < threshold)
  {
    //Serial.print("Card3 ");
    //digitalWrite(BPin, HIGH);
    count3++;
    TotalCount++;
    delay(cardWait); //avoid reading the same card twice
    Timeout = millis() + timeoutWait; // time out
    /*Serial.print("new time: ");
    Serial.print(Timeout);
    Serial.print("\n");
    Serial.print("current time: ");
    Serial.print(millis());
    Serial.print("\n");
    digitalWrite(BPin, LOW);
    */
  }

////  Make a descision  \\\\

  if(TotalCount == numCards)
  {
    if(count1 >= 2)
    {
      
      digitalWrite(RPin, HIGH); //turn LED on
      digitalWrite(GPin, HIGH); //turn LED Yellow
      delay(10000); // 10 second delay to read light color
      digitalWrite(RPin, LOW); //turn LED off
      digitalWrite(GPin, LOW); //turn LED off
      
    }
    else if(count2 >= 2)
    {
      digitalWrite(RPin, HIGH); //turn LED on
      delay(10000); // 10 second delay to read light color
      digitalWrite(RPin, LOW); //turn LED off
    }
    else
    {
      digitalWrite(GPin, HIGH); //turn LED Green
      delay(10000); // 10 second delay to read light color
      digitalWrite(GPin, LOW); //turn LED off
    }
    // Reset
    TotalCount = 0;
    count1 = 0;
    count2 = 0;
    count3 = 0;
    Timeout = 0;
  }


  if(millis() > Timeout)
  {
    
  //Serial.print("Timed out! \n");
    if(TotalCount > 1)
    {
      if(count1 >= 1)
      {
        
        digitalWrite(RPin, HIGH); //turn LED on
        digitalWrite(GPin, HIGH); //turn LED Yellow
        delay(10000); // 10 second delay to read light color
        digitalWrite(RPin, LOW); //turn LED off
        digitalWrite(GPin, LOW); //turn LED off
      }
      else if(count2 >= 1)
      {
        digitalWrite(RPin, HIGH); //turn LED on
        delay(10000); // 10 second delay to read light color
        digitalWrite(RPin, LOW); //turn LED off
      }
      else
      {
        digitalWrite(GPin, HIGH); //turn LED Yellow
        delay(10000); // 10 second delay to read light color
        digitalWrite(GPin, LOW); //turn LED off
      }
    
    }
    // Reset
    TotalCount = 0;
    count1 = 0;
    count2 = 0;
    count3 = 0;
    Timeout = 0;
    
  }
  
}
