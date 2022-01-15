#ifndef VEC3_H_INCLUDED
#define VEC3_H_INCLUDED
#include <cmath>


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
using point = vec3;

#endif // VEC3_H_INCLUDED
