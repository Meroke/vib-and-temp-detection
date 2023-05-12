char var;
int num = 0;
byte Temp[11] = {0};
float D_speed[3] = {0};
float D_angle[3] = {0};
float D_range[3] = {0};
float D_temp = 0;
// 获取震动速度
unsigned char V[8]={
  0X50,0X03,0X00,0X3A,0X00,0X03,0X28,0X47
};
// 获取震动位移
unsigned char D[8]={
  0X50,0X03,0X00,0X41,0X00,0X03,0X58,0X5E
};
// 获取震动角度
unsigned char AD[8]={
  0X50,0X03,0X00,0X3D,0X00,0X03,0X99,0X86
};
// 获取温度
unsigned char TEMP[8]={
  0X50,0X03,0X00,0X40,0X00,0X01,0X88,0X5F
};
// 获取振动速度
void get_speed();
// 获取震动角度
void get_angle();
// 获取震动位移
void get_range();
// 获取温度
void get_temp();