#include <Servo.h>
Servo servo;

int val; // переменная val равна полученной команде
int time; // время одного полива
int count; // сутки/недели/месяцы
int days; // для получения первоначального интервала полива
long sytki; // промежуточная переменная для вычисления интервала полива
long sytki1; // периодичность полива (окончательно - в мс)
int pos; // положение сервопривода
uint16_t count1;
int flag;

void setup()
{   Serial.begin(9600);  // подключаем последовательный порт
    servo.attach(11);
}

void loop()
{   servo.write(57);

    if (Serial.available()) // проверяем, поступают ли какие-то команды
    {   val = Serial.read();

        if (val == 115)
        {   time = 2.5*1000;}
        if (val == 97)
        {   time = 5*1000;}
        if (val == 98)
        {   time = 10*1000;}

        if (val == 99)
        {   count = 99;}
        if (val == 110)
        {   count = 110;}
        if (val == 109)
        {   count = 109;}

        if (val != 97 && val != 98 && val != 115 && val != 99 && val != 109 && val != 110 && val != 120 && time > 0 && count > 0)
        {   days = ((char)val - '0');
            sytki = 10 * sytki + days;}

        if (val == 120)
        {   if (count == 99)
            {   count1 = 57600;
                sytki1 = sytki*1500;}
            if (count == 110)
            {   count1 = 50000;
                sytki1 = sytki*12096;}
            if (count == 109)
            {   count1 = 50220;
                sytki1 = sytki*52416;}
        
            sytki = 0;
            time = 0;
            count = 0;
        }
    }

    if (flag == 1)
    {   val = 1;}

    // работа системы без участия bluetooth-модуля

    if (val == 1 && time > 0 && sytki > 0)
    {   for (pos = 57; pos <= 40; pos -= 1)
        {   servo.write(pos);}
        delay(time); ///
        for (pos = 40; pos >= 57; pos += 1)
        {   servo.write(pos);}
        for (int i = 0; i < count1; i++) ///
        {   delay(sytki1);
            val = Serial.read();
            Serial.println(val);
            if (val == -1)
            {   continue;}
            if (val == 0)
            {   break;}
        }
        flag = 1;
    }
    if (val == 0)
    {   servo.write(57);
        flag = 0;}
}
