#include <SPI.h>
#include "src/LCD/LCD_Driver.h"
#include "src/LCD/GUI_Paint.h"
#include "src/LCD/image.h"
#include "src/max6675/temperature.h"
#include "src/WTVB01M/vibration.h"

// 获取震动位移
void get_range(){
  Serial.write(D,8);
  while(1){
    if (Serial.available())
    {
      byte incomingByte = Serial.read();
  
      Temp[num] = incomingByte;
      num++;
      // 已经接收到了一串完整字符
      if(num == 11)
      {
        for(int i=0;i<3;i++)
        {
          D_range[i] = (((short)Temp[3+(i*2)]<<8)|Temp[4+(i*2)]);
          Serial.print("range");
          Serial.print(i);
          Serial.print("=");
          Serial.println(D_range[i]);
        }
        num = 0;
        return;
      }
    }
  }
}


void drawOnce()
{
  
  Paint_DrawRectangle(1, 1, 320, 240, BLUE,  DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
  Paint_DrawString_CN(30,45, "当前温度:",  &Font24CN, BLACK, BLUE);
  Paint_DrawString_CN(270, 45, "℃", &Font24CN, BLACK, BLUE);

  float temperature = get_temperature();
  char temp[10];
  dtostrf(temperature, 5, 2, temp); 
  Paint_DrawString_EN(180, 60, temp, &Font24, BLACK, BLUE);
  
  Serial.println(temp);
  Paint_DrawString_CN(30,90, "振动方向",  &Font24CN, BLACK, BLUE);
  Paint_DrawString_CN(180,90, "振幅mm",  &Font24CN, BLACK, BLUE);
  Paint_DrawString_EN(70, 140, "X", &Font24, BLACK, BLUE);
  Paint_DrawString_EN(70, 170, "Y", &Font24, BLACK, BLUE); 
  Paint_DrawString_EN(70, 200, "Z", &Font24, BLACK, BLUE);
  char vibe[10];
  float x_vibe = D_range[0];
  float y_vibe = D_range[1];
  float z_vibe = D_range[2];
  dtostrf(x_vibe, 5, 2, vibe); 
  Paint_DrawString_EN(190, 140, vibe, &Font24, BLACK, BLUE);
  dtostrf(y_vibe, 5, 2, vibe); 
  Paint_DrawString_EN(190, 170, vibe, &Font24, BLACK, BLUE); 
  dtostrf(z_vibe, 5, 2, vibe); 
  Paint_DrawString_EN(190, 200, vibe, &Font24, BLACK, BLUE);

}
void drawFlush()
{
  float temperature = get_temperature();
  char temp[10];
  dtostrf(temperature, 5, 2, temp); 
  Paint_DrawString_EN(180, 60, temp, &Font24, BLACK, BLUE);

  char vibe[10];
  float x_vibe = D_range[0];
  float y_vibe = D_range[1];
  float z_vibe = D_range[2];
  dtostrf(x_vibe, 5, 2, vibe); 
  Paint_DrawString_EN(190, 140, vibe, &Font24, BLACK, BLUE);
  dtostrf(y_vibe, 5, 2, vibe); 
  Paint_DrawString_EN(190, 170, vibe, &Font24, BLACK, BLUE); 
  dtostrf(z_vibe, 5, 2, vibe); 
  Paint_DrawString_EN(190, 200, vibe, &Font24, BLACK, BLUE);
}

void Paint_back_flush()
{

  char vibe[10];
  int x_vibe = D_range[0];
  int y_vibe = D_range[1];
  int z_vibe = D_range[2];
  itoa(x_vibe, vibe, 10);
  Paint_back_DrawString_EN(10, 20, vibe, &Font24, BLACK, BLUE);
  itoa(y_vibe, vibe, 10);
  Paint_back_DrawString_EN(10, 50, vibe, &Font24, BLACK, BLUE); 
  itoa(z_vibe, vibe, 10);
  Paint_back_DrawString_EN(10, 80, vibe, &Font24, BLACK, BLUE);
}
void setup()
{
  Config_Init();
  LCD_Init();
  LCD_Clear(0xffff);
  Paint_NewImage(320, 240, 0, BLACK);
  Paint_Clear(BLACK);
  // Paint_back_NewImage(120,90,0,BLACK);
  // Paint_back_Clear(BLACK);

  Serial.begin(9600);
  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);
  drawOnce();
}

void loop()
{
  drawFlush();
  get_range();
  // Paint_back_flush();
  // Paint_DrawImage(Paint_back.Image,180,130,120,90); 
  // Paint_Clear_Part(180,130,BLACK,300,220);
  // Paint_SelectImage();
}



/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
