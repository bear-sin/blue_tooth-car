/*
RX11      TX10
IN1 5  //定义IN1为3口
IN2 4  //定义IN2为4口
IN3 3  //定义IN1为3口
IN4 2  //定义IN2为4口
*/
#define BLINKER_PRINT Serial
#define BLINKER_BLE
#define IN1 5  //定义IN1为3口
#define IN2 4  //定义IN2为4口
#define IN3 3  //定义IN1为3口
#define IN4 2  //定义IN2为4口
#include <Blinker.h>
// 新建组件对象
BlinkerButton Button1("btn-a");//"btn-abc"为标识符，可自定义
BlinkerButton Button2("btn-b");//"btn-abc"为标识符，可自定义
BlinkerButton Button3("btn-c");//"btn-abc"为标识符，可自定义
BlinkerButton Button4("btn-d");//"btn-abc"为标识符，可自定义
BlinkerNumber Number1("num-abc");
int counter = 0;
// 按下按键即会执行该函数
void button1_callback(const String & state) {
  BLINKER_LOG("get button state: ", state);
  if(state=="press")
  {forward();}
  if(state=="pressup")
  {stop();}
  delay(100);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
void button2_callback(const String & state) {
  BLINKER_LOG("get button state: ", state);
   if(state=="press")
  {backward();}
  if(state=="pressup")
  {stop();}
  delay(100);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
void button3_callback(const String & state) {
  BLINKER_LOG("get button state: ", state);
   if(state=="press")
  {left();}
  if(state=="pressup")
  {stop();}
  delay(100);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
void button4_callback(const String & state) {
  BLINKER_LOG("get button state: ", state);
   if(state=="press")
  {right();}
  if(state=="pressup")
  {stop();}
  delay(100);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
void forward()
{
analogWrite(IN1,255);  //控制电机正转
   analogWrite(IN2,0);
   analogWrite(IN4,240);  //控制电机正转
   analogWrite(IN3,0);
}
void backward()
{
   analogWrite(IN1,0);   //电机反转
   analogWrite(IN2,255);
   analogWrite(IN4,0);   //电机反转
   analogWrite(IN3,240);
}

void right()
{
   analogWrite(IN1,0);   //电机反转
   analogWrite(IN2,180);
   analogWrite(IN3,0);   //电机反转
   analogWrite(IN4,180);
}

void left()
{
     analogWrite(IN2,0);   //电机反转
   analogWrite(IN1,180);
   analogWrite(IN4,0);   //电机反转
   analogWrite(IN3,180);
}
void stop()
{
     analogWrite(IN2,0);   //电机反转
   analogWrite(IN1,0);
   analogWrite(IN4,0);   //电机反转
   analogWrite(IN3,0);
}
// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
 BLINKER_LOG("Blinker readString: ", data);
 counter++;
 Number1.print(counter);
}
void setup() {
  // 初始化串口
 Serial.begin(115200);
  #if defined(BLINKER_PRINT)
  BLINKER_DEBUG.stream(BLINKER_PRINT);
   #endif
  
 // 初始化有LED的IO
 pinMode(LED_BUILTIN, OUTPUT);
 digitalWrite(LED_BUILTIN, HIGH);
 // 初始化blinker
 Blinker.begin(10, 11, 9600); // 设置数字IO 10(RX) 11(TX) 及波特率 9600 bps ,蓝牙频率默认9600.
 Blinker.attachData(dataRead);
 Button1.attach(button1_callback);
 Button2.attach(button2_callback);
 Button3.attach(button3_callback);
 Button4.attach(button4_callback);

}

void loop() {
 Blinker.run();
}