#include"mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"
#include <string>
#include <iostream>
Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
DigitalInOut pin10(D10);
BBCar car(pin5, pin6, servo_ticker);

BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx
Timer t;

int main(){
   parallax_ping  ping1(pin10);
   uart.set_baud(9600);
   pc.set_baud(9600);
   while(1){
      if(uart.readable()){
            char recv[1];
            float x = 0;
            bool fin1 = 0, fin2 = 0;
            int degree = 180;
            uart.read(recv, sizeof(recv));
            if(recv[0] == 'a') {
               uart.read(recv, sizeof(recv));
               printf("%s",recv);
               char recv2[1], recv3[1], recv4[1];

               uart.read(recv2, sizeof(recv2));
               printf("%s",recv2);
               if (recv2[0]== '-') {
                  uart.read(recv2, sizeof(recv2));
                  printf("%c",recv2[0]);
                  uart.read(recv, sizeof(recv));
                  printf("%c",recv[0]);
                  uart.read(recv3, sizeof(recv3));
                  printf("%c",recv3[0]);
                  x =  -(1.0 * (recv2[0] - '0') + 0.1 * (recv3[0] - '0'));
               }
               else {
                  uart.read(recv2, sizeof(recv2));
                  printf("%c",recv2[0]);
                  uart.read(recv, sizeof(recv));
                  printf("%c",recv[0]);
                  uart.read(recv3, sizeof(recv3));
                  printf("%c",recv3[0]);
                  x =  1.0 * (recv2[0] - '0') + 0.1 * (recv3[0] - '0');
               }

               uart.read(recv, sizeof(recv));
               printf("%c",recv[0]);

               uart.read(recv2, sizeof(recv2));
               printf("%c",recv2[0]);
               uart.read(recv3, sizeof(recv3));
               printf("%c",recv3[0]);
               uart.read(recv4, sizeof(recv4));
               printf("%c",recv4[0]);
               degree = (recv2[0] - '0') * 100 + (recv3[0] - '0') * 10 +(recv4[0] - '0');
               
               if (x > 0.5) {;
                  printf("left\n");
                  car.turn(50, 0.3);
                  ThisThread::sleep_for(std::chrono::milliseconds(300));
               }
               else if (x < -0.5) {
                  printf("right\n");
                  car.turn(-50, 0.3);
                  ThisThread::sleep_for(std::chrono::milliseconds(300));
               }
               else fin1 = 1;
               car.stop();
               if (degree > 185){
                  printf("ll\n");
                  car.turn(-80, -0.7);
                  ThisThread::sleep_for(std::chrono::milliseconds(500));
                  car.turn(-50, 0.7);
                  ThisThread::sleep_for(std::chrono::milliseconds(500));
               }
               else if (degree < 175){
                  printf("rr\n");
                  car.turn(-80, 0.7);
                  ThisThread::sleep_for(std::chrono::milliseconds(500));
                  car.turn(-50, -0.7);
                  ThisThread::sleep_for(std::chrono::milliseconds(500));
               }
               else fin2 = 1;
               car.stop();
               if(fin1 && fin2) {
               float val;
               
               pin10.output();
               pin10 = 0; wait_us(200);
               pin10 = 1; wait_us(5);
               pin10 = 0; wait_us(5);

               pin10.input();
               while(pin10.read() == 0);
               t.start();
               while(pin10.read() == 1);
               val = t.read();
               printf("Ping = %lf\r\n", val*17700.4f);
               t.stop();
               t.reset();
               break;
               }
            }

      }

   }
}
   