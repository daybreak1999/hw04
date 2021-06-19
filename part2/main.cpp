#include"mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"


Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);

BBCar car(pin5, pin6, servo_ticker);

BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx

int main(){
   uart.set_baud(9600);
   car.goStraight(-20);
   while(1){
      if(uart.readable()){
            char recv[1];
            int x1 = -1, x2 = -1, y1 = -1, y2 = -1;
            uart.read(recv, sizeof(recv));
            // pc.write(recv, sizeof(recv));
            if(recv[0] == 'l') {
               uart.read(recv, sizeof(recv));
               // pc.write(recv, sizeof(recv));
               char recv2[1], recv3[1], recv4[1];

               uart.read(recv2, sizeof(recv2));
               // pc.write(recv2, sizeof(recv2));
               uart.read(recv3, sizeof(recv3));
               // pc.write(recv3, sizeof(recv3));
               uart.read(recv4, sizeof(recv4));
               // pc.write(recv4, sizeof(recv4));
               x1 = (recv2[0] - '0') * 100 + (recv3[0] - '0') * 10 +(recv4[0] - '0');
               uart.read(recv, sizeof(recv));
               // pc.write(recv, sizeof(recv));

               uart.read(recv2, sizeof(recv2));
               // pc.write(recv2, sizeof(recv2));
               uart.read(recv3, sizeof(recv3));
               // pc.write(recv3, sizeof(recv3));
               uart.read(recv4, sizeof(recv4));
               // pc.write(recv4, sizeof(recv4));
               y1 = (recv2[0] - '0') * 100 + (recv3[0] - '0') * 10 +(recv4[0] - '0');
               uart.read(recv, sizeof(recv));
               // pc.write(recv, sizeof(recv));

               uart.read(recv2, sizeof(recv2));
               // pc.write(recv2, sizeof(recv2));
               uart.read(recv3, sizeof(recv3));
               // pc.write(recv3, sizeof(recv3));
               uart.read(recv4, sizeof(recv4));
               // pc.write(recv4, sizeof(recv4));
               x2 = (recv2[0] - '0') * 100 + (recv3[0] - '0') * 10 +(recv4[0] - '0');
               uart.read(recv, sizeof(recv));
               // pc.write(recv, sizeof(recv));

               uart.read(recv2, sizeof(recv2));
               // pc.write(recv2, sizeof(recv2));
               uart.read(recv3, sizeof(recv3));
               // pc.write(recv3, sizeof(recv3));
               uart.read(recv4, sizeof(recv4));
               // pc.write(recv4, sizeof(recv4));
               y2 = (recv2[0] - '0') * 100 + (recv3[0] - '0') * 10 +(recv4[0] - '0');
               uart.read(recv, sizeof(recv));
               // pc.write(recv, sizeof(recv));

               float tan = ((float)x2-x1) / ((float)y2 - y1);
               
               if (tan < -0.05) {
                  char out[5] = "left";
                  pc.write(out, sizeof(out));
                  car.turn(-20, -0.5);
                  ThisThread::sleep_for(std::chrono::milliseconds(100));
               }
               if (tan > 0.05) {
                  char out[6] = "right";
                  pc.write(out, sizeof(out));
                  car.turn(-20, 0.5);
                  ThisThread::sleep_for(std::chrono::milliseconds(100));
               }
                 
            }
      }
   }
}