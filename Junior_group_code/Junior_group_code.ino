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
void stopL();
void stopR();
void runL();
void runR();
void frunL();
void frunR();
void sRun();
// 创建对象
DFRobot_PS2X ps2x;


// 主程序开始
void setup() {
	pinMode(6,OUTPUT);
	pinMode(7,OUTPUT);
	pinMode(8,OUTPUT);
	pinMode(9,OUTPUT);
	pinMode(13,OUTPUT);
	ps2x.config_gamepad(A2,A4,A3,A5, true, true);
	delay(300);
	ps2x.read_gamepad();
	delay(30);
	Serial.begin(9600);
	mind_n_modeA = 0;//自动和手动状态
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

int tmpl;

void loop() {
	ps2x.read_gamepad(); //刷新
	if (ps2x.Button(PSB_BLUE)) {
		DF_stopAll();
		Serial.println("x down");
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
			if ((ps2x.Analog(PSS_LY)<120)) {
				sRun();
				DF_fRunAll();
				Serial.println("后");				
				
			}
			else if (ps2x.Analog(PSS_LY)>134) {
				sRun();
				DF_runAll();
				Serial.println("前");			
				
			}
			else if ((ps2x.Analog(PSS_LX)<120)) {
				sRun();
				frunL();
				runR();
				Serial.println("左");				
				
			}
			else if (ps2x.Analog(PSS_LX)>134) {
				sRun();
				runL();
				frunR();
				Serial.println("右");
				
			}
			else {
				DF_stopAll();
				Serial.println("allstop");
			}
		}
	}
	Serial.println();
	delay(30);
}


// 自定义函数
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
    sx = abs(ps2x.Analog(PSS_LX)-127)*2-1;
	sy = abs(ps2x.Analog(PSS_LY)-127)*2-1;
    if (sx > sy) {
       analogWrite(5,sx);
       analogWrite(10,sx);
	   Serial.println(sx);
	}
	else{
      analogWrite(5,sy);
      analogWrite(10,sy);
	  Serial.println(sy);
	}
	
}