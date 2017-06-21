#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // put your setup code here, to run once:
 lcd.begin(16, 2);
 lcd.setCursor(0,0);
      lcd.print("GLUCOMETER");
      delay(100);
      
    
Serial.begin(9600);
}

void loop() {
  static double glucose=0,adcv=0,glevel=0,flag=0,avg=0,avgt=0,disp=0;
  // put your main code here, to run repeatedly:
pinMode(9,OUTPUT);
tone(9,55000);
analogWrite(10,127);
adcv=analogRead(A0);
adcv=adcv*5/1024;

glucose=(adcv-2.5)/1.414;
Serial.println(glucose);
glevel = -0.041*(glucose*glucose) - 0.617*glucose + 5.648 ;

flag++;
if(flag>=5500)
{
  avg+=glevel;
  if(flag==6000)
  {
    avg=avg/500;
    avgt+=avg;
    disp++;
    lcd.setCursor(0,0);
      lcd.print("Calc. glucose level");
      lcd.setCursor(0,1);
      lcd.print("Please Wait");
      for(int i=0;i<disp;i++)
      lcd.print(".");
    if(disp==5)
    {avgt=avgt/5;
    lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Glucose level is :");
      lcd.setCursor(0,1);
     lcd.print(avgt);
     lcd.print(" mmol/L");
      avgt=0;
      disp=0;
      }
    
    avg=0;
    flag=0;
    }
  }

glucose=0;
glevel=0;

}

