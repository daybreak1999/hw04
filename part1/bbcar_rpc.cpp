#include "bbcar_rpc.h"
RPCFunction rpcStop(&RPC_stop, "stop");
RPCFunction rpcCtrl(&RPC_goStraight, "goStraight");
RPCFunction rpcTurn(&RPC_turn, "turn");
RPCFunction rpcPark(&RPC_park, "park");
extern BBCar car;

void RPC_stop (Arguments *in, Reply *out)   {
    car.stop();
    return;
}

void RPC_goStraight (Arguments *in, Reply *out)   {
    int speed = in->getArg<double>();
    car.goStraight(speed);
    return;
}

void RPC_turn (Arguments *in, Reply *out)   {
    int speed = in->getArg<double>();
    double turn = in->getArg<double>();
    car.turn(speed,turn);
    return;
}

void RPC_park (Arguments *in, Reply *out)   {
    int d1 = in->getArg<double>();
    int d2 = in->getArg<double>();
    int direction = in->getArg<double>();
    
    if(direction == 0)
        d1 += 4;
    car.goStraight(52);

    for(; d1 > 0; d1 -= 1) {
        ThisThread::sleep_for(std::chrono::milliseconds(125));
    }
    car.stop();
    
    if (direction == 1) {
        car.turn(100 , 0.3);
        ThisThread::sleep_for(std::chrono::milliseconds(2200));
    }
    else  {
        car.turn(100, -0.3);
        ThisThread::sleep_for(std::chrono::milliseconds(1800));
    }
    car.stop();
    
    car.goStraight(52);
    d2 -= 10;
    for(; d2 > 0; d2 -= 1) {
        ThisThread::sleep_for(std::chrono::milliseconds(125));
    }
    car.stop();

    return;
}
