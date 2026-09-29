// Minimal Arduino API stub so the real .ino files can be compiled and run on a PC.
#pragma once
#include <cstdio>
#include <cstdlib>
#include <cmath>
#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2
#define constrain(a,lo,hi) ((a)<(lo)?(lo):((a)>(hi)?(hi):(a)))
inline unsigned long g_ms = 0;              // fake clock
inline double g_dist[3] = {-1,-1,-1};       // front,left,right (cm, <0 = no echo)
inline int g_btn = HIGH;                    // button pin level
inline void pinMode(int,int){}
inline void digitalWrite(int,int){}
inline int digitalRead(int pin){ return pin==33 ? g_btn : LOW; }
inline void analogWrite(int,int){}
inline void tone(int,unsigned,unsigned long=0){}
inline void delayMicroseconds(unsigned){}
inline void delay(unsigned long ms){ g_ms += ms; }
inline unsigned long millis(){ return g_ms; }
inline long pulseIn(int echo,int,unsigned long){
  int i = echo==18 ? 0 : echo==21 ? 1 : 2;
  if (g_dist[i] < 0) return 0;
  return (long)(g_dist[i]*2.0/0.0343);
}
struct SerialStub {
  void begin(long){}
  void print(const char*s){printf("%s",s);} void print(int v){printf("%d",v);}
  void print(long v){printf("%ld",v);} void print(unsigned long v){printf("%lu",v);}
  void print(double v){printf("%.2f",v);}
  void println(const char*s){printf("%s\n",s);} void println(double v){printf("%.2f\n",v);}
  void println(){printf("\n");}
};
inline SerialStub Serial;
