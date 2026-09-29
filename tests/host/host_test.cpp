// Runs one scenario against whichever firmware file is passed via -DFIRMWARE_FILE.
// This tests LOGIC on a PC. It is NOT a Wokwi or hardware result.
#include "arduino_stub.h"
#include FIRMWARE_FILE

static void run(int loops, double front, int btn) { g_dist[0]=front; g_btn=btn; for(int i=0;i<loops;i++) loop(); }

int main(int argc, char** argv) {
  int sc = argc > 1 ? atoi(argv[1]) : 0;
  setup();
  int changes = 0; int lastMode = currentMode; float gmin = 9, gmax = 0;
  auto track = [&](int loops, double front, int btn){
    for(int i=0;i<loops;i++){ run(1,front,btn);
      if (currentMode != lastMode) { changes++; lastMode = currentMode; }
      if (adaptiveGain<gmin) gmin=adaptiveGain; if (adaptiveGain>gmax) gmax=adaptiveGain; } };
  const char* name = "";
  switch (sc) {
    case 1: name = "sparse close events (~3.9 s apart)";
      for (int k=0;k<5;k++){ track(2,20,HIGH); track(63,200,HIGH);} break;
    case 2: name = "rapid close events (~0.36 s apart)";
      for (int k=0;k<8;k++){ track(2,20,HIGH); track(4,200,HIGH);} break;
    case 3: name = "normal close events (~1.5 s apart)";
      for (int k=0;k<5;k++){ track(2,20,HIGH); track(23,200,HIGH);} break;
    case 4: name = "one obstacle held close for 5 s";
      track(2,200,HIGH); track(83,20,HIGH); break;
    case 5: name = "button held LOW for 1 s, then released";
      track(3,200,HIGH); track(17,200,LOW); track(5,200,HIGH); break;
    case 6: name = "3 separate short presses";
      for (int k=0;k<3;k++){ track(3,200,HIGH); track(3,200,LOW); track(3,200,HIGH);} break;
  }
  printf("RESULT scenario %d (%s): final_gain=%.2f min_gain=%.2f max_gain=%.2f mode_changes=%d\n",
         sc, name, adaptiveGain, gmin, gmax, changes);
  return 0;
}
