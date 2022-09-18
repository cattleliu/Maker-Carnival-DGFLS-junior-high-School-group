/*!
 * MindPlus
 * uno
 *
 */
#include <DFRobot_PS2X.h>

// 动态变量
volatile float mind_n_modeA;
// 函数声明
void DF_stopAll();
void DF_runAll();
void DF_fRunAll();
// 创建对象
DFRobot_PS2X ps2x;


// 主程序开始
void setup() {
	ps2x.config_gamepad(A2,A4,A3,A5, true, true);
	delay(300);
	ps2x.read_gamepad();
	delay(30);
	Serial.begin(9600);
	mind_n_modeA = 0;
	digitalWrite(13, HIGH);
}

double LX;
double LXBl;
double LXBr;
double LXB11;
double LXB22;
double LY;

void loop() {
	ps2x.read_gamepad();
	delay(30);
	if (ps2x.Button(PSB_BLUE)) {
		DF_stopAll();
		Serial.println("x down");
	}
	else {
		if (ps2x.Button(PSB_SELECT)) {
			if ((mind_n_modeA==1)) {
				mind_n_modeA = 0;
				digitalWrite(13, HIGH);
				Serial.println("select down");
			}
			else if ((mind_n_modeA==0)) {
				mind_n_modeA = 1;
				digitalWrite(13, LOW);
			}
		}
		if ((mind_n_modeA==0)) {
			if ((ps2x.Analog(PSS_LX)<127)) {
				DF_fRunAll();
				Serial.println("fRunAll");
			}
			else if ((127<ps2x.Analog(PSS_LX))) {
				DF_runAll();
				Serial.println("runAll");
			}
			LX = ps2x.Analog(PSS_LX);
      		LXBl = 256-LX;
      		LXBr = 256-LXBl;
      		analogWrite(5,LXBl);
      		Serial.println(LXBl);
      		analogWrite(10,LXBr);
      		Serial.println(LXBr);
		}
	}
	Serial.println();
	delay(300);
}


// 自定义函数
void DF_stopAll() {
	digitalWrite(7, LOW);
	digitalWrite(6, LOW);
	digitalWrite(8, LOW);
	digitalWrite(9, LOW);
}
void DF_runAll() {
	digitalWrite(6, LOW);
	digitalWrite(7, HIGH);
	digitalWrite(8, LOW);
	digitalWrite(9, HIGH);
}
void DF_fRunAll() {
	digitalWrite(6, LOW);
	digitalWrite(7, LOW);
	digitalWrite(8, HIGH);
	digitalWrite(9, LOW);
}

