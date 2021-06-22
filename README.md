# hw04

#part1 XBee Controlled BB Car

在bbcar_rpc.h 中宣告RPC_park()function 並在bbcar_rpc.h中實作。RPC_park()透過輸入d1,d2和direction判斷停車的行動，以上數值透過pc端的xbee傳輸給mbed接收。pc端的xbee透過car_control.py控制。car_control.py透過compile時輸入的argv傳送d1,d2和direction給mbed。

#part2 Line Following BB Car

openmv執行part2.py，尋找y1值最小的line，將line的數值(x1,x2,y1,y2)傳給mbed。mbed取得數值後計算tan，根據tan值來控制car的左擺與右擺來沿著line前進。

#part3 BB Car Position Calibration

openmv執行part3.py，尋找apriltag，將值x_translation()和degrees(tag.x_rotation()傳給mbed，因mbed接受值後要控制車車一段時間，所以openmv間隔2秒才傳一次。在mbed裡mbed透過x和degree控制車車左右以對準apriltag，對準後回傳ping測量到的距離，print到screen上。
