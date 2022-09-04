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
        	LXBl = 255-(LX-1);
        	LXBr = 255-LXBl;
        	LXB11 = LXBr==0?LXBl/(LXBr+0.01):LXBl/LXBr;
        	LXB22 = LXBl==0?LXBr/(LXBl+0.01):LXBr/LXBl;
        	LY = ps2x.Analog(PSS_LY);
			Serial.print("LX:    ");Serial.println(LX);
			Serial.print("\nLXB1:  ");Serial.println(LXBl);
			Serial.print("LXBr:  ");Serial.println(LXBr);
			Serial.print("\nLXB11: ");Serial.println(LXB11);
			Serial.print("LXB22: ");Serial.println(LXB22);
			Serial.print("\nLY:    ");Serial.println(LY);
        	analogWrite(5,LXB11*LY);
        	analogWrite(10,LXB22*LY);
		}
	}
	Serial.println();
	delay(800);
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
