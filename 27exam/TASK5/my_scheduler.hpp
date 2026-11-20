#include<iostream>
#include<vector>
#include"simulator.hpp"

class MyScheduler{
public:
MyScheduler()=default;
int Floor(const Car& c){
    floor=c.floor;
    return floor;
}
bool Full(const Car& c){
    full = c.load >= c.capacity;
    if(full)
      return true;
    else
      return false;
}
int callNearCar(const View& v, int e){
    const Car& c = v.cars[e];
    int best = -1;
    int bestDist = 1 << 30;

    for (int x = 1; x <= kFloors; ++x) {
        if (c.car_call[x] == -1) continue;          
        int dist = (x > c.floor) ? (x - c.floor) : (c.floor - x);
        if (dist < bestDist) {
            bestDist = dist;
            best = x;
        }
    }
    return best; 
}
bool hasDemandAhead(const View& v, int e, int direct[]){
    int f = v.cars[e].floor;
    bool full = v.cars[e].load >= v.cars[e].capacity;

    for (int x = f + direct[e]; x >= 1 && x <= kFloors; x += direct[e]) {
        if (v.cars[e].car_call[x] != -1) return true;
        if (!full && direct[e] == +1 && v.hall_up[x] != -1) return true;
        if (!full && direct[e] == -1 && v.hall_down[x] != -1) return true;
    }
    return false;
}
bool hasAnyDemand(const View& v, int e) {
    const Car& c = v.cars[e];

    
    for (int f = 1; f <= kFloors; ++f) {
        if (c.car_call[f] != -1)
            return true;
    }

    
    if (c.load >= c.capacity)
        return false;

    
    for (int f = 1; f <= kFloors; ++f) {
        if (v.hall_up[f] != -1 || v.hall_down[f] != -1)
            return true;
    }

    return false;
}
Action decide(const View& v, int e){
    MyScheduler s1;
    const Car& c = v.cars[e];
    
    int f=s1.Floor(c);
    bool full=s1.Full(c);

    if (c.car_call[f] != -1)
      return direct[e] == +1 ? Action::OpenUp : Action::OpenDown;
    
    if (!full && direct[e] == +1 && v.hall_up[f] != -1)
        return Action::OpenUp;
    if (!full && direct[e] == -1 && v.hall_down[f] != -1)
        return Action::OpenDown;
    
    if(full==true){
        int t = s1.callNearCar(v, e);
        if (t == -1) return Action::Idle;
        if (t > f) return Action::Up;
        if (t < f) return Action::Down;
        return direct[e] == +1 ? Action::OpenUp : Action::OpenDown;
    }

    if (s1.hasDemandAhead(v, e, direct)) {
        if (direct[e] == +1 && f < kFloors) return Action::Up;
        if (direct[e] == -1 && f > 1) return Action::Down;
    }
    
    if (s1.hasAnyDemand(v, e)){
        direct[e]=-direct[e];
        if (!full && direct[e] == +1 && v.hall_up[f] != -1)
            return Action::OpenUp;
        if (!full && direct[e] == -1 && v.hall_down[f] != -1)
            return Action::OpenDown;

        return direct[e] == +1
             ? (f < kFloors ? Action::Up : Action::Idle)
             : (f > 1 ? Action::Down : Action::Idle);
        
    }

  return Action::Idle;
}
private:
int floor;
bool full;
int direct[2]={-1,1};
};
