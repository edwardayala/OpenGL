// PoVRay 3.7 Scene File "Test_2_Ray_Tracing_Animation_Edward_Ayala.pov"
// author:  Edward Ayala
// date: 04/24/2020
//--------------------------------------------------------------------------
#version 3.7;
global_settings{ assumed_gamma 1.0 }
#default{ finish{ ambient 0.1 diffuse 0.9 }} 
//--------------------------------------------------------------------------
#include "colors.inc"
#include "textures.inc"
#include "glass.inc"
#include "metals.inc"
#include "golds.inc"
#include "stones.inc"
#include "woods.inc"
#include "shapes.inc"
#include "shapes2.inc"
#include "functions.inc"
#include "math.inc"
#include "transforms.inc"  

//--------------------------------------------------------------------------
// camera ------------------------------------------------------------------
#declare Camera_0 = camera {perspective angle 75               // front view
                            location  <clock/3 + 0.0 , 1.0 ,-4.0>
                            right     x*image_width/image_height
                            look_at   <clock/3 + 0.0 , 1.0 , 0.0>}
#declare Camera_1 = camera {/*ultra_wide_angle*/ angle 90   // diagonal view
                            location  <clock/3 + 2.0 , 2.5 ,-3.0>
                            right     x*image_width/image_height
                            look_at   <clock/3 + 0.0 , 1.0 , 0.0>}
#declare Camera_2 = camera {/*ultra_wide_angle*/ angle 90  //right side view
                            location  <clock/3 + 3.0 , 1.0 , 0.0>
                            right     x*image_width/image_height
                            look_at   <clock/3 + 0.0 , 1.0 , 0.0>}
#declare Camera_3 = camera {/*ultra_wide_angle*/ angle 90        // top view
                            location  <clock/3 + 0.0 , 5.0 ,-0.001>
                            right     x*image_width/image_height
                            look_at   <clock/3 + 0.0 , 1.0 , 0.0>}
#if (clock < 30 & clock > 0) camera{Camera_0}
#elseif (clock < 60 & clock > 30) camera{Camera_1}
#elseif (clock < 90 & clock > 60) camera{Camera_2}
#else camera{Camera_3} 
#end
// sun ----------------------------------------------------------------------
light_source{< 3000,3000,-3000> color White}
// sky ----------------------------------------------------------------------
sky_sphere { pigment { gradient <0,1,0>
                       color_map { [0.00 rgb <0.6,0.7,1.0>]
                                   [0.35 rgb <0.1,0.0,0.8>]
                                   [0.65 rgb <0.1,0.0,0.8>]
                                   [1.00 rgb <0.6,0.7,1.0>] 
                                 } 
                       scale 2         
                     } // end of pigment
           } //end of skysphere
// ground -------------------------------------------------------------------
plane{ <0,1,0>, 0 
       texture{ pigment{ checker color rgb<1,1,1>*1.2 color rgb<0.25,0.15,0.1>*0}
              //normal { bumps 0.75 scale 0.025}
                finish { phong 0.1}
              } // end of texture
     } // end of plane
//---------------------------------------------------------------------------
//---------------------------- objects in scene -----------------------------
//---------------------------------------------------------------------------     
// CHROME FISHY
// FISH BODY
sphere{ <0,0,0>, 0.5 
        texture { Polished_Chrome
                  //pigment{color rgb< 1, 0.6, 0> }
                  //normal {bumps 0.5 scale 0.10}
                  finish { phong 1 phong_size 50}
                } // end of texture

        scale<2.5,1,1>  rotate<0,0,0>  translate<clock/3 + 0,1,0>  
      } // end of sphere ----------------------------------- 
                                                                   
                                                                   
// FISH TAIL 
//----------------------------------------------------------------------------
#include "shapes3.inc"
//----------------------------------------------------------------------------
//      Pyramid_N( N, Radius1, Radius2, Height )
object{ Pyramid_N( 8,    1.20,    0.00,   1.30 ) 
        texture{ Polished_Chrome
                  //pigment{color rgb< 1, 0.6, 0> }
                  //normal {bumps 0.5 scale 0.10}
                  finish { phong 1 phong_size 50}
               } // end of texture
        scale <0.6,0.6,0.1> rotate<0,0,-90> translate<clock/3 + -2,1,0>
      } // end of object -----------------------------------------------------
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// NAME ----------------------------------------------------------------------
//----------------------------------------------------------------------------

text { ttf "arial.ttf", "Edward Ayala | Test 2: Ray Tracing Animation", 0.05, 0.0 // thickness, offset

       texture{ pigment{ color rgb<1,0,0>*1.3 } 
                finish { phong 0.1 }
              } // end of texture

       scale<1,1.25,1>*0.8
       translate<2.10,0.10,-0.5 >
      } // end of text object ---------------------------------------------

//----------------------------------------------------------------------------
// background objects --------------------------------------------------------
//----------------------------------------------------------------------------
#declare Random_1 = seed (10053); // Use: "rand(Random_1)" 
#declare Random_2 = seed ( 4953); // Use: "rand(Random_2)"


union{
 // outer loop
 #local NrX = -5;    // start x
 #local EndNrX = 5; // end   x
 #while (NrX< EndNrX) 
       // inner loop
       #declare NrZ = 0;    // start z
       #declare EndNrZ = 10; // end   z
       #while (NrZ< EndNrZ) 
     
       sphere{ <0,0,0>,0.15
               texture { pigment{ color rgb< 1.0, 0.5, 0.0> }  
                         finish {  diffuse 0.9 phong 1}
                       } // end of texture 
        
        //    translate<NrX*0.5 0.15 NrZ*0.5>} 
              translate<  NrX*0.5 + 0.35*(-0.5+rand(Random_1)) , 
                          0.15 , 
                          NrZ*0.5 + 0.35*(-0.5+rand(Random_2)) 
                        >
            } // end of sphere  

       #declare NrZ = NrZ + 1;  // next Nr z
       #end // --------------- end of loop z
       // end inner loop
 #local NrX = NrX + 1;  // next Nr x
 #end // --------------- end of loop x
 // end of outer loop
rotate<0,0,0> 
translate<15,0.0,-2.5>} // end of union




//---------------------------------------------------------------------------- 
#include "shapes3.inc"
//----------------------------------------------------------------------------
object{ Round_N_Tube_Polygon ( // A round polygon tube ring with N corners 
                            8, // number of corners must be >= 3 !!!
                            0.125+0.05,// tube radius < base width
                            0.9,      // base width (center to edge middle)
                            0.25,    // corner torus segment major radius
                            0, // 1 = filled, 0 = ring
                            0 // 0 uses union; 1 uses merge for transparent
                          ) //------------------------------------------------ 
 
      texture{ Polished_Chrome
               pigment{ color rgbf<1,0,0,0>}
               finish { phong 1}
             } // end of texture
  
      rotate<0,90,0>
      translate<25,1,0>
} // end of object -----------------------------------------------------------
//----------------------------------------------------------------------------

#declare Random_1 = seed (27053); // Use: "rand(Random_1)" 

union{
 #local Nr = -8;   // start
 #local EndNr = 8; // end
 #while (Nr< EndNr+1) 

 sphere{ <0,0,0>,0.125 
	 texture{ pigment{ color rgb<1,0.65,0>}
                  finish { diffuse 0.9 phong 1}
                } // end of texture

         translate< 35 + Nr*0.25, 2*rand(Random_1) ,2*rand(Random_1)>

       } // end of sphere ----------------------


 #local Nr = Nr + 1;  // next Nr
 #end // --------------- end of loop 

rotate<0,0,0> 
translate<0,0,0>
} // end of union
 