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
                            location  <0.0 , 1.0 ,-4.0>
                            right     x*image_width/image_height
                            look_at   <0.0 , 1.0 , 0.0>}
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


camera{Camera_0} 

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
/*
plane{ <0,1,0>, 0 
       texture{ pigment{ checker color rgb<1,1,1>*1.2 color rgb<0.25,0.15,0.1>*0}
              //normal { bumps 0.75 scale 0.025}
                finish { phong 0.1}
              } // end of texture
     } // end of plane       
*/     
     
 //-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
#if (clock < 45)                                        
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
                                    
isosurface { //-------------------------------------------------------------

  function { f_heart( x,y,z,  -0.15 )
           }

  threshold 0.0
  accuracy 0.0001
  max_gradient 100
  contained_by {box {<-1.1,-1.5,-1.1>,< 1.1,1.22,1.5>}}
  //open
  texture { pigment{ color rgb<1,0.7,0.1>}
            //normal {bumps 0.5 scale 0.05}
            finish { phong 1 specular 0.3 }
	  }
  scale 1.00
  rotate <-90, clock/6 * 90, 0>
  translate <-0, 1.1, 5>
} // end of isosurface -------------------------------------------------------   


// ----------------- HF_Torus macro ---------------------
#declare Fn_1 =  
   function(x, y, z)
   {1-(-f_snoise3d(x*3,y*3,z*3)*0.8)}

//-------------------------------------------------------
object{ HF_Torus( Fn_1, //Function,
                  0, // UseUVheight:  0 or 1
                  1, // UseUVtexture: 0 or 1
                 <50,50>, // Resolution,
                 1, // Smooth: 0 or 1
                 "",// FileName, ""=no file,
                 2.00, 1.00 ,// R_Major, R_Minor// Radius
                 -0.25   // Depth
               ) //--------------------------------------
  texture{ 
    pigment{ gradient  x+y 
             color_map{
             [ 0.0 color  rgb< 1.0,0.95, 0.9>*1]
             [ 0.5 color  rgb< 1.0,0.95, 0.9>*1]
             [ 0.5 color  rgb< 0.8, 0.0, 0.05> ]
             [ 1.0 color  rgb< 0.8, 0.0, 0.05> ]
             } // end color_map
             turbulence 0.0 scale< 1,3,1>*0.015
           } // end pigment
    finish {  phong 1 reflection 0.01}
  } // end of texture 

  scale<1,1,1>*1
  rotate<0,clock/4 * 90,0>
  translate<0,-1,5>
} // end of HF_Torus ------------------------------------      

isosurface { //-------------------------------------------------------------

  function{ abs(x)+abs(y)+abs(z)-2.7  }

  contained_by { box { -2, 2 } }
  accuracy 0.003
  max_gradient 5

  texture{ pigment{ color rgb<1,0.25,0.35>}
           normal { bumps 0.5 scale 0.035}
           finish { specular 0.2 phong 1 reflection 0.15}}
  scale 0.5
  rotate<0,clock * 10,clock * 10>
  translate <0, 3.5, 5>
} // end of isosurface ----------------------------------------------------- 

isosurface { //-------------------------------------------------------------
  function{
     f_helix1(
        x,y,z,
        1,    // number of helixes, (1 = single helix, 2 = double helix etc.)
        22,   // period,      turns on the length of 2*pi 
        0.07, // minor radius,
        0.80, // major radius,
        1,    // shape parameter, 
        0.3,  // cross section type, (0.0 to 1.0 = square ... rounded to circle
              //                 over 2.0 to 3.0 = rounded to diamond and concave diamond
        0     // cross section rotation angle
      )
  }          
 contained_by {box {<-1,-1,-1>,<1,1,1>}}
 max_gradient 8

 texture{ pigment{ color rgb <1,0.9,0.5>} 
          finish { specular 0.1 roughness 0.1 phong 0.2 }
        }
 rotate<0,clock * 10,0>
 scale 5
 translate< 0,clock + -10,5>
} // end of isosurface -------------------------------------------------------

sphere{ <0,0,0>, 0.25 
        texture { Polished_Chrome
                  //pigment{color rgb< 1, 0.6, 0> }
                  //normal {bumps 0.5 scale 0.10}
                  finish { phong 1 phong_size 50}
                } // end of texture 
        scale<2,2,2> 
        translate<cos(clock/4)*2,1,5 + sin(clock/4)*2>
        rotate<0,0,0>    
      } // end of sphere -----------------------------------
      
 text { ttf "arial.ttf", "Edward Ayala - Test 2: Ray Tracing Animation (2)", 0.02, 0.0 // thickness, offset

       texture{ pigment{ color rgb<1,0,0>*1.3 } 
              //normal { bumps 0.5  scale 0.01 }
                finish { phong 0.1 }
              } // end of texture

       scale<1,1.25,1>*0.8
       translate<20 - clock,0.10,0.00 >
      } // end of text object ---------------------------------------------
 
#elseif (clock > 45)
isosurface{ // ------------------------------------------------------------

  function {  sqrt(x*x + y*y + z*z) - 0.9
              + sin(12*atan2(x, z))*sin(8*atan2(y, sqrt(x*x + z*z)))*0.1
           }

  threshold 0
  accuracy 0.0001
  max_gradient 5
  contained_by {box {<-1,-1,-1>, < 1, 1, 1>}}
  //open

  texture{ Polished_Chrome
           //pigment{color rgb< 1, 0.6, 0> }
           //normal {bumps 0.5 scale 0.10}
           finish { phong 1 phong_size 50}
	  }
  scale 1.00
  rotate <0, -clock + 25, 5>
  translate <-0, 1.3, 0>
} // end of isosurface -----------------------------------------------------  

#declare Random_1 = seed (52053); // Use: "rand(Random_1)" 
#declare Random_2 = seed ( 1953); // Use: "rand(Random_2)"
#declare Random_3 = seed (  153); // Use: "rand(Random_3)"


union{
 // outer loop
 #local NrX = 0;    // start x
 #local EndNrX = 5; // end   x
 #while (NrX< EndNrX) 
    // more inner loop
    #local NrY = 0;    // start y 
    #local EndNrY = 5; // end   y
    #while (NrY< EndNrY) 
       // innerst loop
       #local NrZ = 0;    // start z
       #local EndNrZ = 8; // end   z
       #while (NrZ< EndNrZ) 
     
       sphere{ <0,0,0>,0.15
               texture { pigment{ color rgb< rand(Random_1),rand(Random_2), rand(Random_3)> }  
                         finish { diffuse 0.9 phong 1}
                       } // end of texture 
        
        //    translate<NrX*0.5 NrY*0.5 NrZ*0.5>} 
              translate< 5 * NrX*0.5 + 0.35*(-0.5+rand(Random_1)) , 
                         5 * NrY*0.5 + 0.35*(-0.5+rand(Random_2)) , 
                         5 * NrZ*0.5 + 0.35*(-0.5+rand(Random_3)) 
                        >
            } // end of sphere  

       #local NrZ = NrZ + 1;  // next Nr z
       #end // --------------- end of loop z
       // end innerst loop
    #local NrY = NrY + 1;  // next Nr y
    #end // --------------- end of loop y
    // end more inner loop
 #local NrX = NrX + 1;  // next Nr x
 #end // --------------- end of loop x
 // end of outer loop
rotate<clock,clock,0> 
translate<-3,-5,0>} // end of union

   
#end        