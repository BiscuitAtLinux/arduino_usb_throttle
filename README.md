# arduino_usb_throttle

用Arduino Leonardo实现一个简单的模拟飞行用油门（也可以当赛车手刹，或扩展其他功能）
 
最早的版本是Uno上实现的，通过串口发送数据，并用SimConnect控制模拟飞行,
现在迁移到Leonardo上，可以用USB模拟游戏控制器

硬件及接线
 * 电位器：GND, AREF, A0
 * SH1106屏幕：SPI接法，接 3.3V, GND, SCL, SDA