use <enclosure_v1.scad>
L=100; W=50; H=22;
// Curved armband strap segment beneath the enclosure
inner_r=30; strap_t=2.5; strap_w=42; arc=220;
translate([L/2, W/2, -strap_w/2])
  rotate([90,0,0])
  rotate_extrude(angle=arc, convexity=10, $fn=120)
    translate([inner_r, -strap_w/2]) square([strap_t, strap_w], center=false);
// enclosure base + lid
translate([0,0,0]) base();
translate([0,0,H]) lid();
