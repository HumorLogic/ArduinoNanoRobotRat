#include <Servo.h>

Servo Front; //实例化前舵机
Servo Back;  //实例化后舵机

int obstcleSensor = 2; //定义红外避障传感器数字口2
unsigned long previousMillis = 0;
int walkState = 1; //行走状态

void setup()
{

    pinMode(obstcleSensor, INPUT);
    Front.attach(3);
    Back.attach(4);

    Front.write(90); // 初始舵机转到90度，前后两对脚需要摆正对前方
    Back.write(90);

    delay(3000);
    //Serial.begin(9600);
}

void loop()
{

    unsigned long currentMillis = millis();
    int obstcleState = digitalRead(obstcleSensor);
    //Serial.println(obstcleState);
    if (obstcleState == 0)
    {
        walkState = 0;
        previousMillis = currentMillis;
    }
    if (walkState == 1)
    {
        walkForward();
    }

    if (walkState == 0)
    {
        if (currentMillis - previousMillis <= 2000)//检测到障碍，后退2S
        {
            walkBackward();
        }
        if (currentMillis - previousMillis > 2000 && currentMillis - previousMillis <= 2900)
        {
            moveStraight();
        }
        if (currentMillis - previousMillis >= 3000)
        {
            turnRight();
        }
        if (currentMillis - previousMillis >= 6000)
        {
            walkState = 1;
        }
    }
}

//直行Forward方法，通过调节前后腿旋转角度和延迟时间调整机器人的步幅和速度
void walkForward()
{
    Front.write(140);
    delay(100);
    Back.write(70);
    delay(150);

    Front.write(70);
    delay(100);
    Back.write(140);
    delay(150);
}

//后退backward方法
void walkBackward()
{
    Back.write(140);
    delay(100);
    Front.write(70);
    delay(150);

    Back.write(70);
    delay(100);
    Front.write(140);
    delay(150);
}

//右转turn right方法
void turnRight()
{

    Front.write(150);
    delay(100);
    Back.write(70);
    delay(150);

    Front.write(80);
    delay(100);
    Back.write(140);
    delay(150);
}

//左转turn left
void turnLeft()
{
    Front.write(120);
    delay(200);
    Front.write(40);
    delay(200);
}

//摆正
void moveStraight()
{
    Front.write(90);
    Back.write(90);
    delay(200);
}
