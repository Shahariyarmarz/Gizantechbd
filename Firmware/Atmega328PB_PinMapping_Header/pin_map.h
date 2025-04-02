#ifndef pin_map_h
#define pin_map_h


// Pin definitions (#define Pin_Name Arduino_Pin //Atmega_Pin)

//-----------------Digital Pin Definitions---------------
#define Output_EN_48V 3 //1
#define IN4_48V 8 //12
#define S_LDO 9 //13
#define IC1_VCC S 21 //8
#define IC2_VCC S 20 //7
#define V_CORE_CN 2 //32


//--------------Arduino ISP Header Pin Definitions (Digital Pin)----------
#define MCU_MOSI 11 //15
#define MCU_MISO 12 //16
#define MCU_SCK 13 //17
#define MCU_RST 22 //29


//-----------------Analog Pin Definitions---------------
#define OUT_48V 26 //22
#define N48V_OUT 25 //19
#define Load_Current 17 //26
#define Supply_Current 16 //25
#define N48V_OUT_2 14 //23




#endif