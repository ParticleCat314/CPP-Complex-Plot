#include <iostream>
#include <math.h>
//#include "vec3.h"
/// Define pi as a value that won't change throughout the runtime. I believe the compiler just subs this for the keyword.
#define PI 3.14159265358979323

class complex{
public:
    float real;
    float imaginary;
    complex(){};
    complex(float a, float b) {real = a; imaginary = b;}
};

inline complex operator* (const complex &z1, const complex &z2){
    return complex(z1.real*z1.real + z1.imaginary*z2.imaginary,z1.real*z2.imaginary+z1.imaginary*z2.real);
}
inline complex operator+ (const complex &z1, const complex &z2){
    return complex(z1.real+z2.real,z1.imaginary+z2.imaginary);
}
inline complex operator- (const complex &z1, const complex &z2){
    return complex(z1.real-z2.real,z1.imaginary-z2.imaginary);
}
inline complex operator- (const complex &z1, const int &r2){
    return complex(z1.real-r2,z1.imaginary);
}
inline complex operator+ (const complex &z1, const int &r2){
    return complex(z1.real+r2,z1.imaginary);
}
inline complex operator* (const float &r, const complex &z2){
    return complex(r*z2.real,r*z2.imaginary);
}

class vec3{
public:
        float x;
        float y;
        float z;

        vec3() {};
        vec3(float a, float b, float c) {x = a; y = b; z = c;};

        float length(){return sqrt(x*x+y*y+z*z);}
        float squared_length(){return length()*length();}

        vec3 unit(){float l = length(); return vec3(x/l,y/l,z/l);}
};

inline vec3 operator+ (const vec3 &a, const vec3 &b){
    vec3 temp;
    temp.x = a.x+b.x;
    temp.y = a.y+b.y;
    temp.z = a.z+b.z;
    return temp;
}

inline vec3 operator- (const vec3 &a, const vec3 &b){
    vec3 temp;
    temp.x = a.x-b.x;
    temp.y = a.y-b.y;
    temp.z = a.z-b.z;
    return temp;
}

inline float operator* (vec3 &a, vec3 &b){
    float temp = a.x*b.x + a.y*b.y + a.z*b.z;
    return temp;
}

inline vec3 operator* (const vec3& a, const float& s){return vec3(s*a.x,s*a.y,s*a.z);}
inline vec3 operator* (const float& s, const vec3& a){return a*s;}
using color = vec3;

/// This function recieves a 'file' & the color of the pixel to write into the file.
void ColorPixel(std::ostream &s, color PixelColor){
    s << static_cast<int>(255.999*PixelColor.x) << ' '
          << static_cast<int>(255.999*PixelColor.y) << ' '
          << static_cast<int>(255.999*PixelColor.z) << '\n';
}

/// Just a simple function to convert HSL color into RGB values.
/// This is useful for converting an angle (phase) of the compelx function to color.As 360 degrees maps all the colors. Feel free to read up on HSL.
/// TBH I don't really understand HSL that well.
color HSL_RGB(int h, float s, float l){
    float C = (1-abs(2*l-1))*s;
    float X = C*(1-abs(fmod(h/60.0,2) - 1));
    float m = l - C/2;

    color Prime;

    if (h<60){Prime = color(C,X,0);}
    else if (h<120){Prime = color(X,C,0);}
    else if (h<180){Prime = color(0,C,X);}
    else if (h<240){Prime = color(0,X,C);}
    else if (h<300){Prime = color(X,0,C);}
    else if (h<360){Prime = color(C,0,X);}

    return Prime+color(m,m,m);
}

// This is my complex function. It returns a vec3 with the real, imaginary & nothing. IDK why I used vec3, I was probably just lazy.
vec3 funky(float x, float y){
    complex z = complex(x,y);
    complex function = (2*z-z*z*z);
    /// This should hopefully be equilevant to the complex function Z = 2*(x+yi) - (x+yi)*(x+yi)*(x+yi) --- I'm too lazy to expand

    float real = function.real;
    float imaginary = function.imaginary;
    return vec3(real,imaginary,0);
}



// Program's entry point - main code here.
int main(){

    // Define constant values for the width & height of the image. 
    const int width = 1000;
    const int height = 1000;

    // Write the formatting details into the file. Might want to read about PPM or use a proper image library. 
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    // Here we loop over every pixel, and calculate the complex value associated with it.
    for (int j = height-1; j>=0; --j ){
        
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush; // Just print details to console.
        
        for (int i = 0; i<width; i++){
            float u = float(-500+i) / (width-1);
            float v = float(-500+j) / (height-1);

            vec3 comp = funky(6*u,6*v);
            int theta = int(179+(atan2(comp.x,comp.y))*(180/PI));

            float r = sqrt(comp.x*comp.x + comp.y*comp.y);
            color rgb = HSL_RGB(theta,1,r);
            ColorPixel(std::cout,HSL_RGB(theta,1,2/PI * atan(r)));
        }
    }

    std::cerr << "\nDone.\n";
    return 0;
}
