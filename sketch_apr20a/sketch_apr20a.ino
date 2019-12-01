#include <ThingSpeak.h>
#include "ThingSpeak.h"
#include <SoftwareSerial.h>  // serial software library for interfacing gsm module
SoftwareSerial Serial1(2, 3); // RX, TX  // connect gsm Tx at D2 and Rx at D3
#include<LiquidCrystal.h>     // LCD library for interfacing LCD
LiquidCrystal lcd(14,15,16,17,18,19);   // connect rs,en,d4,d5,d6,d7 respectevely

String pvtKey="B4HYCEPGZ8I7Q3ZS";     // private key for posting data to thingspeak
//String publicKey="w5nXxM6rp0tww5YVYg3G";  // public key for open page of thingspeak 
String url="";
String ip="\"api.thingspeak.com\"";        // thingspeak server ip or url
int port=80;                              // thingspeak server port
unsigned long mcn=761938;
const char * mwk= "B4HYCEPGZ8I7Q3ZS";
String SendCmd="AT+CIPSEND=";           // sending number of byte command
String Start="AT+CIPSTART=\"TCP\"";     // TCPIP start command 

// strings and variables
//String msg="";
String instr="";
String str_sms="";
String str1="";
int i=0,temp=0;

#include <Keypad.h>               // keypad library for interfacing keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
int x=0;
int y=0;
int n=0;
int minValue=0;
int maxValue=0;
char keyPress=0;
int keyPressTime=100;
String msg="";

char hexaKeys[ROWS][COLS] = 
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {11, 10, 9, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 6, 5, 4}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

String alpha="1.@_$%?2ABC3DEF4GHI5JKL6MNO7PQRS8TUV9WXYZ*0 #"; 

void setup() 
{
  Serial1.begin(9600);    // init serial1 for GSM
  lcd.begin(16,2);        // init LCD
  lcd.print("Sending Data  ");
  lcd.setCursor(0,1);
  lcd.print("to Server");
  delay(2000);
  lcd.clear();
  lcd.print("Initializing GSM");
  initGSM();      // init GSM module
  lcd.clear();
  lcd.print("Initializing GPRS");
  initGPRS();     // init GPRS in GSM Module
  lcd.clear();
  lcd.print("System Ready");
  delay(2000);
}

void loop()
{
  int n=0;
  lcd.clear();
  lcd.noCursor();
  while(1)
  {
    lcd.cursor();
    char key = customKeypad.getKey();
    if(key=='1')
      getkey(0, 6, key);

     if(key=='2')
      getkey(7, 10, key);

     else if(key=='3')
      getkey(11, 14, key); 

     else if(key=='4')
      getkey(15, 18, key);

    else if(key=='5')
      getkey(19, 22, key);

    else if(key=='6')
      getkey(23, 26, key);

    else if(key=='7')
      getkey(27, 31, key);

    else if(key=='8')
      getkey(32,35, key);

    else if(key=='9')
      getkey(36, 40, key);

    else if(key=='*')
      getkey(41, 41, key);

    else if(key=='0')
      getkey(42, 43, key);

    else if(key=='#')
      getkey(44, 44, key);
      
    else if(key == 'C')
    {
         x--;
         lcd.setCursor(x,y);
         lcd.print(" ");
         n--;
         msg[n]=' '; 
         lcd.setCursor(x,y);
    }

    else if(key == 'D')
    {
      lcd.clear();
      lcd.noBlink();
      lcd.print("Sending Data");
      lcd.setCursor(0,1);
      lcd.print("To Server");
      url="GET /update";
      //url+=publicKey;
      url+="?api_key=";
      url+=pvtKey;
      url+="&field1=";
      url+=msg;
      url+=" HTTP/1.0\r\n\r\n";
      String svr=Start+","+ip+","+port;
      delay(1000);
      connectGSM(svr,"CONNECT");
      delay(1000);
      int len = url.length();
      String str="";
      str=SendCmd+len;
      sendToServer(str);
       Serial1.print(url);
      delay(1000);
      Serial1.write(0x1A);
      delay(1000);
     
      lcd.clear();
      lcd_status();
       //  clearmsg();
       n=0;
       i=0;
       x=0;
       y=0;
       msg="";
    }
  }
}

void getkey(int minValue, int maxValue, char keyPress)
{
   int ch=minValue;
   int pressed=1;
   char key=keyPress;
   lcd.noBlink();
   for(int i=0;i<keyPressTime;i++)
   {     
      if(key==keyPress)
      {
         lcd.setCursor(x,y);
         lcd.print(alpha[ch]);
         ch++;
         if(ch>maxValue)
         ch=minValue;
         i=0;   
      }
      key=customKeypad.getKey();
      delay(10);
    }

     if(pressed)
     {  
        x++;
        msg+=alpha[ch-1];
        n++;
        if(x>15)
        {
          x=0;
          y=1;
        }
     }
    pressed=0;
    lcd.blink();
}

void lcd_status()
{
  lcd.clear();
  lcd.print("Data Sent to");
  lcd.setCursor(0,1);
  lcd.print("Server");
  delay(2000);
  lcd.clear();
}


void sendToServer(String str)
{
  Serial1.println(str);
  delay(1000);
}

void initGSM()
{
  connectGSM("AT","OK");
  connectGSM("ATE1","OK");
  connectGSM("AT+CPIN?","READY");
}
void initGPRS()
{
  connectGSM("AT+CIPSHUT","OK");
  connectGSM("AT+CGATT=1","OK");
  connectGSM("AT+CSTT=\"airtelgprs.com\",\"\",\"\"","OK");
  connectGSM("AT+CIICR","OK");
  delay(1000);
  Serial1.println("AT+CIFSR");
  delay(1000);
}
void connectGSM (String cmd, char *res)
{
  while(1)
  {
    Serial.println(cmd);
    Serial1.println(cmd);
    delay(500);
    while(Serial1.available()>0)
    {
      if(Serial1.find(res))
      {
        delay(1000);
        return;
      }
    }
    delay(1000);
   }
 }
