// Wrist/armband enclosure v1: navigation wearable
// Export: OpenSCAD -> Design > Render (F6) -> File > Export > STL
// Render base and lid separately by changing PART.
PART   = "base";      // "base" or "lid"

// --- Outer size (mm). See hardware/README.md for why not 90x40x15 ---
L = 100; W = 50; H = 22; wall = 2; r = 3;

// --- HC-SR04 transducers: 16 mm dia, 26 mm centre spacing ---
tx_d = 16.6; tx_pitch = 26;
btn_d = 12.2;         // 12 mm pushbutton
usb_w = 12; usb_h = 7;

module rbox(l,w,h,rad){ hull() for(x=[rad,l-rad]) for(y=[rad,w-rad]) translate([x,y,0]) cylinder(r=rad,h=h,$fn=40); }

module base(){
  difference(){
    rbox(L,W,H,r);
    translate([wall,wall,wall]) rbox(L-2*wall,W-2*wall,H,r-1);            // cavity
    // FRONT sensor: on the +X end face (toward the fingers)
    for(s=[-1,1]) translate([L-wall-1, W/2+s*tx_pitch/2, H/2]) rotate([0,90,0]) cylinder(d=tx_d,h=wall+2,$fn=40);
    // LEFT sensor: on the -Y long face
    for(s=[-1,1]) translate([L/2+s*tx_pitch/2, -1, H/2]) rotate([-90,0,0]) cylinder(d=tx_d,h=wall+2,$fn=40);
    // RIGHT sensor: on the +Y long face
    for(s=[-1,1]) translate([L/2+s*tx_pitch/2, W-wall-1, H/2]) rotate([-90,0,0]) cylinder(d=tx_d,h=wall+2,$fn=40);
    // USB access on the -X end face
    translate([-1, W/2-usb_w/2, H/2-usb_h/2]) cube([wall+2,usb_w,usb_h]);
  }
  // screw posts for the lid
  for(x=[6,L-6]) for(y=[6,W-6]) translate([x,y,wall]) difference(){ cylinder(d=6,h=H-wall-2,$fn=30); cylinder(d=2.2,h=H,$fn=20); }
}

module lid(){
  difference(){
    rbox(L,W,wall,r);
    translate([L/2,W/2,-1]) cylinder(d=btn_d,h=wall+2,$fn=40);              // mode button
    for(x=[6,L-6]) for(y=[6,W-6]) translate([x,y,-1]) cylinder(d=3.2,h=wall+2,$fn=20); // M2 screws
  }
}

if (PART=="base") base(); else lid();
