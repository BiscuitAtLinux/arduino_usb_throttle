/**
 * 用Arduino Leonardo实现一个简单的模拟飞行用油门（也可以当赛车手刹，或扩展其他功能）
 * 最早的版本是Uno上实现的，通过串口发送数据，并用SimConnect控制模拟飞行
 * 现在迁移到Leonardo上，可以用USB模拟游戏控制器
 * 
 * 硬件及接线
 * 电位器：GND, AREF, A0
 * SH1106屏幕：SPI接法，接 3.3V, GND, SCL, SDA
*/
#include <Arduino.h>
#include <U8x8lib.h>
#include <Joystick.h>

U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/U8X8_PIN_NONE);
Joystick_ Joystick;

int analogReadWithFilter();

void setup(void)
{
  // 提高响应速度，比默认频率高一倍，实际提高应该不到一倍
  u8x8.setBusClock(800000);
  u8x8.begin();
  // 设置大字体，占满一行
  u8x8.setFont(u8x8_font_inb46_4x8_n);
  // 降低屏幕亮度
  u8x8.setContrast(64);
  // 初始化USB游戏控制器
  Joystick.begin();
}

void loop(void)
{
  // 读传感器值
  int aValue = analogReadWithFilter();
  // 手柄上报
  Joystick.setThrottle(aValue);

  // 屏幕显示
  char showStr[5];
  // 归一化到100
  float nValue = (float)aValue / 10.23;
  sprintf(showStr, "%4d", (int)nValue); // avr的sprintf默认竟然不支持处理浮点
  u8x8.home();
  u8x8.print(showStr);
}

/**
 * @brief 带简单滤波的ADC读取
 * 
 * @return int 
 */
int analogReadWithFilter()
{
  int max = 0;
  int min = 1023;
  int sum = 0;
  // 采样6次
  for (int i = 0; i < 6; i++)
  {
    int current = analogRead(A0);
    sum += current;
    if (current > max)
    {
      max = current;
    }
    if (current < min)
    {
      min = current;
    }
    delay(2);
  }
  // 去掉一个最大最小值，取平均
  float avg = float(sum - max - min) / 4.0;
  // 四舍五入
  return int(avg + 0.5);
}
