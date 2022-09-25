#include <DFRobot_PS2X.h>
#include <QMC5883LCompass.h>

// 动态变量
volatile float mind_n_modeA;
// 函数声明
void DF_stopAll();
void DF_runAll();
void DF_fRunAll();
void stopL();
void stopR();
void runL();
void runR();
void frunL();
void frunR();
void sRun();
void turnRAround();
void nXstop();

DFRobot_PS2X ps2x;
QMC5883LCompass compass;

void setup()
{
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
  ps2x.config_gamepad(A1, A3, A2, 3, true, true);
  compass.init();
  Serial.begin(115200);
  mind_n_modeA = 0; //自动和手动状态
  digitalWrite(13, HIGH);
}

double LX;
double LXBl;
double LXBr;
double LXB11;
double LXB22;
double LY;

int sx;
int sy;
int ds;
int lds, ldsmax, ldsmin;
double hw;
double timee, timeel;

int tmpl;
int a_temp;

const int speedr = 90;

void loop()
{
  ps2x.read_gamepad(); //刷新
  compass.read();
  if (ps2x.Button(PSB_BLUE))
  {
    DF_stopAll();
    Serial.println("x down");
  }
  else
  {
    if (ps2x.Button(PSB_SELECT))

      if ((mind_n_modeA == 1))
      {
        mind_n_modeA = 0;
        digitalWrite(13, HIGH);
      }
      else if ((mind_n_modeA == 0))
      {
        mind_n_modeA = 1;
        digitalWrite(13, LOW);
      }
  }
  if ((mind_n_modeA == 0))
  {
    if ((ps2x.Analog(PSS_LY) < 120))
    {
      sRun();
      DF_fRunAll();
    }
    else if (ps2x.Analog(PSS_LY) > 134)
    {
      sRun();
      DF_runAll();
    }
    else if ((ps2x.Analog(PSS_LX) < 120))
    {
      sRun();
      frunR();
      runL();
    }
    else if (ps2x.Analog(PSS_LX) > 134)
    {
      sRun();
      runR();
      frunL();
    }
    else
    {
      DF_stopAll();
    }
  }
  else if (mind_n_modeA == 1)
  {
    hw = analogRead(A0);
    Serial.print("hw");
    Serial.println(hw);
    if (hw < 100)
    {
      Serial.println("meet black");
      turnRAround();
      analogWrite(10, speedr);
      analogWrite(5, speedr);
    }
    DF_fRunAll();
    analogWrite(10, speedr);
    analogWrite(5, speedr);
  }
  delay(50);
}

// 自定义函�?
void nXstop()
{
  if (ps2x.Button(PSB_BLUE))
  {
    DF_stopAll();
    Serial.println("x down");
  }
}
void turnLAround()
{
  Serial.println("into trunLAruond");
  ds = compass.getAzimuth();
  Serial.println(ds);
  delay(3000);
  if (ds > 90)
  {

    a_temp = ds - 90;
  }
  else
  {
    a_temp = 360 - abs(ds - 90);
  }

  Serial.print("a_temp:");
  Serial.println(a_temp);
  delay(5000);
  runL();
  analogWrite(5, speedr);
  analogWrite(10, speedr);
  while (abs(ds - a_temp) > 4 & abs(ds - a_temp) < 354)
  {
    compass.read();
    ds = compass.getAzimuth();
    Serial.print("ds:");
    Serial.println(ds);
    Serial.print("atemp:");
    Serial.println(a_temp);

    // Serial.print("abs:");
    // Serial.println(abs(ds-a_temp));
    delay(50);
  }

  // while((abs(ds-a_temp)<4)||(abs(ds-a_temp)>356));
  DF_stopAll();
  Serial.println("stop runl");
}
void DF_stopAll()
{
  stopR();
  stopL();
}
void DF_runAll()
{
  runL();
  runR();
}
void DF_fRunAll()
{
  frunL();
  frunR();
}
void stopL()
{
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}
void stopR()
{
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
}
void runR()
{
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
}
void runL()
{
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
}
void frunR()
{
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
}
void frunL()
{
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
}
void sRun()
{
  sx = abs(ps2x.Analog(PSS_LX) - 127) * 2 - 1;
  sy = abs(ps2x.Analog(PSS_LY) - 127) * 2 - 1;
  if (sx > sy)
  {
    analogWrite(5, sx);
    analogWrite(10, sx);
    Serial.println(sx);
  }
  else
  {
    analogWrite(5, sy);
    analogWrite(10, sy);
    Serial.println(sy);
  }
}