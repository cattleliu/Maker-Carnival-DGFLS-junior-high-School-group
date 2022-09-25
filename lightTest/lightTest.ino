/*!
 * MindPlus
 * uno
 *
 */
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
void turnLAround();
void nXstop();
// 创建对象
DFRobot_PS2X ps2x;
QMC5883LCompass compass;

// 主程序开始
void setup() {
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
  ps2x.config_gamepad(A1, A3, A2, 3, true, true);
  compass.init();
  Serial.begin(115200);
  mind_n_modeA = 0;  //自动和手动状态
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

void loop() {
  ps2x.read_gamepad();  //刷新
  compass.read();
  if (ps2x.Button(PSB_BLUE)) {
    DF_stopAll();
    Serial.println("x down");
  } else {
    if (ps2x.Button(PSB_SELECT))

      if ((mind_n_modeA == 1)) {
        mind_n_modeA = 0;
        digitalWrite(13, HIGH);
      } else if ((mind_n_modeA == 0)) {
        mind_n_modeA = 1;
        digitalWrite(13, LOW);
      }
  }
  if ((mind_n_modeA == 0)) {
    if ((ps2x.Analog(PSS_LY) < 120)) {
      sRun();
      DF_fRunAll();
    } else if (ps2x.Analog(PSS_LY) > 134) {
      sRun();
      DF_runAll();
    } else if ((ps2x.Analog(PSS_LX) < 120)) {
      sRun();
      frunL();
      runR();
    } else if (ps2x.Analog(PSS_LX) > 134) {
      sRun();
      runL();
      frunR();
    } else {
      DF_stopAll();
    }
  } else if (mind_n_modeA == 1) {
    hw = analogRead(A0);
    Serial.println(hw);
    if (hw < 90) {
      Serial.println("meet black");
      turnLAround();
      analogWrite(10,100);
      analogWrite(5,100);
    }    
    DF_fRunAll();
    analogWrite(10,100);
    analogWrite(5,100);
  }
  hw = analogRead(A0);
  Serial.println(hw);
  delay(100);
}

// 自定义函数
void nXstop() {
  if (ps2x.Button(PSB_BLUE)) {
    DF_stopAll();
    Serial.println("x down");
  }
}
void turnLAround() {
  Serial.println("into trunLAruond");
  ds = compass.getAzimuth();
  lds = ds > 270 ? ds + 90 - 360 : ds + 90;
  ldsmax = lds > 355 ? lds + 5 - 360 : lds + 5;
  ldsmin = lds < 10 ? lds - 5 + 360 : lds - 5;
  while (!(ds > ldsmin && ds < ldsmax)) {
    nXstop();
    compass.read();
    Serial.println("inturn");
    ds = compass.getAzimuth();
    Serial.print(ds);
    Serial.print(" max:");
    Serial.print(ldsmax);
    Serial.print(" min:");
    Serial.println(ldsmin);
    hw = analogRead(A0);
    Serial.println(hw);
    stopL();
    runR();
    analogWrite(10, 100);
    analogWrite(5, 100);
    delay(5);
  }
  timee = millis();
  timeel = timee + 400;
  while (timee <= timeel) {
    nXstop();
    timee = millis();
    Serial.println("ingo");
    DF_runAll();
    delay(5);
  }
  ds = compass.getAzimuth();
  lds = ds > 270 ? ds + 90 - 360 : ds + 90;
  ldsmax = lds > 355 ? lds + 5 - 360 : lds + 5;
  ldsmin = lds < 10 ? lds - 5 + 360 : lds - 5;
  if (ldsmin>ldsmax){
    
  }
  while ((ldsmin>ldsmax ? !(ds < ldsmax) : !(ds > ldsmin))) {
    nXstop();
    compass.read();
    Serial.println("inturn2");
    ds = compass.getAzimuth();
    Serial.print(ds);
    Serial.print(" max:");
    Serial.print(ldsmax);
    Serial.print(" min:");
    Serial.println(ldsmin);
    hw = analogRead(A0);
    Serial.println(hw);
    stopL();
    runR();
    analogWrite(10, 100);
    analogWrite(5, 100);
    delay(5);
  }
}
void DF_stopAll() {
  stopR();
  stopL();
}
void DF_runAll() {
  runL();
  runR();
}
void DF_fRunAll() {
  frunL();
  frunR();
}
void stopL() {
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}
void stopR() {
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
}
void runL() {
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
}
void runR() {
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
}
void frunL() {
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
}
void frunR() {
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
}
void sRun() {
  sx = abs(ps2x.Analog(PSS_LX) - 127) * 2 - 1;
  sy = abs(ps2x.Analog(PSS_LY) - 127) * 2 - 1;
  if (sx > sy) {
    analogWrite(5, sx);
    analogWrite(10, sx);
    Serial.println(sx);
  } else {
    analogWrite(5, sy);
    analogWrite(10, sy);
    Serial.println(sy);
  }
}