CODE:                                                                                                                                                                                                                                               #include <SoftwareSerial.h>

SoftwareSerial gsm(9,10);   // RX, TX

int gasSensor = A0;
int buzzer = 7;
int led = 6;

int threshold = 300;

bool smsSent = false;

void setup()
{
  Serial.begin(9600);
  gsm.begin(9600);

  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);

  delay(15000);   // wait for GSM network
}

void loop()
{
  int gasValue = analogRead(gasSensor);

  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  if(gasValue > threshold)
  {
    digitalWrite(buzzer, HIGH);
    digitalWrite(led, HIGH);

    if(!smsSent)
    {
      sendSMS(gasValue);
      smsSent = true;
    }
  }
  else
  {
    digitalWrite(buzzer, LOW);
    digitalWrite(led, LOW);
    smsSent = false;
  }

  delay(1000);
}

void sendSMS(int value)
{
  gsm.println("AT+CMGF=1");
  delay(1000);

  gsm.println("AT+CMGS=\"+91XXXXXXXXXX\"");
  delay(1000);

  gsm.print("ALERT! Gas Leak Detected. Level: ");
  gsm.println(value);

  delay(1000);
  gsm.write(26);   // CTRL+Z to send SMS
}-
