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

int LY;
int LYBl;
int LYBr;
int LYB11;
int LYB22
int LX;

void loop() {
	ps2x.read_gamepad();
	delay(30);
	if (ps2x.Button(PSB_BLUE)) {
		DF_stopAll();
	}
	else {
		if (ps2x.Button(PSB_SELECT)) {
			if ((mind_n_modeA==1)) {
				mind_n_modeA = 0;
				digitalWrite(13, HIGH);
			}
			else if ((mind_n_modeA==0)) {
				mind_n_modeA = 1;
				digitalWrite(13, LOW);
			}
		}
		if ((mind_n_modeA==0)) {
			if ((ps2x.Analog(PSS_LX)<127)) {
				DF_fRunAll();
			}
			else if ((127<ps2x.Analog(PSS_LX))) {
				DF_runAll();
			}
			analogWrite(5, 200);
			analogWrite(10, 200);
		}
        LY = ps2x.Analog(PSS_LY);
        LYBl = 255-LY;
        LYBr = 255-LYBl;
        LYB11 = LYBl/LYBr;
        LYB22 = LYBr/LYBl;
        LX = ps2x.Analog(PSS_LX);
        analogWrite(5,LYB11*LX);
        analogWrite(10,LYB22*LX)
	}
	delay(50);
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
