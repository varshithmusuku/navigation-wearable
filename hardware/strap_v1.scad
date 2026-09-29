// Simple printable curved armband strap segment
// Dimensions in mm; intended as a visual/fit prototype.
inner_r = 30;
strap_t = 2.5;
strap_w = 42;
arc = 220;

rotate([90,0,0])
rotate_extrude(angle=arc, convexity=10, $fn=120)
  translate([inner_r, -strap_w/2])
    square([strap_t, strap_w], center=false);
