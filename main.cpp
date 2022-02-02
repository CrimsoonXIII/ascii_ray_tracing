#include <iostream>
#include "m_math.h"
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cmath>
#include <windows.h>
#include <vector>
#include <cfloat>
#include "matrix_operations.h"
#include "light.h"
#include<tuple>
#include<thread>
using namespace std;
tuple<int, vec3, vec3> check_ray(const vector<vec3>& VB, vec3 d, vec3 P)
{
    d = d / d.length();
    vec3 A, B, C;//points of triangle and vec3 describing brightness, opacity and reflectiveness
    vec3 AB, AC, n, Q;//
    float dp, t;

    int index_closest = -1;
    vec3 normal_closest;
    vec3 x_closest;
    float shortest_distance = FLT_MAX;
    float temp_distance;
    for(long long unsigned int k = 0; k < VB.size(); k += 4)
    {
        A = VB[k];
        B = VB[k+1];
        C = VB[k+2];
        AB = vec3(A,B);
        AC = vec3(A,C);
        n = (B-A).cross(C-A);
        n = n / n.length();

        if(n.dot(d)<0.0f)
        {
            dp = n.dot(A);
            t = (dp - n.dot(P))/n.dot(d);
            Q = P + (d * t);


            //cout.precision(3);
            //cout<< std::fixed <<'('<<A.x<<"; "<<A.y<<"; "<<A.z<<"), ("<<B.x<<"; "<<B.y<<"; "<<B.z<<"), ("<<C.x<<"; "<<C.y<<"; "<<C.z<<"):  "<<(char)9<< "("<<Q.x<<"; "<<Q.y<<"; "<<Q.z<<"); "<<t << "; "<< (C-B).cross(Q-B).dot(n)<< "; "<< (B-A).cross(Q-A).dot(n)<< "; "<< (A-C).cross(Q-C).dot(n)<< '\n';
            if((C-B).cross(Q-B).dot(n) >= -0.0f && (B-A).cross(Q-A).dot(n) >= -0.0f && (A-C).cross(Q-C).dot(n) >= -0.0f && t > 0)
            {
                temp_distance = (Q - P).length();
                if(temp_distance < shortest_distance)
                {
                    shortest_distance = temp_distance;
                    normal_closest = n;
                    index_closest = k;
                    x_closest = Q;
                }

            }
        }
    }
    return make_tuple(index_closest, normal_closest, x_closest);
}

bool shadow_check(const vector<vec3>& VB, vec3 d, vec3 P)
{
    d = d / d.length();
    vec3 A, B, C;//points of triangle and vec3 describing brightness, opacity and reflectiveness
    vec3 AB, AC, n, Q;//
    float dp, t;
    for(long long unsigned int k = 0; k < VB.size(); k += 4)
    {
        A = VB[k];
        B = VB[k+1];
        C = VB[k+2];
        AB = vec3(A,B);
        AC = vec3(A,C);
        n = (B-A).cross(C-A);
        n = n / n.length();
        if(n.dot(d)<0.0f)
        {
            dp = n.dot(A);
            t = (dp - n.dot(P))/n.dot(d);
            Q = P + (d * t);


            //cout.precision(3);
            //cout<< std::fixed <<'('<<A.x<<"; "<<A.y<<"; "<<A.z<<"), ("<<B.x<<"; "<<B.y<<"; "<<B.z<<"), ("<<C.x<<"; "<<C.y<<"; "<<C.z<<"):  "<<(char)9<< "("<<Q.x<<"; "<<Q.y<<"; "<<Q.z<<"); "<<t << "; "<< (C-B).cross(Q-B).dot(n)<< "; "<< (B-A).cross(Q-A).dot(n)<< "; "<< (A-C).cross(Q-C).dot(n)<< '\n';
            if((C-B).cross(Q-B).dot(n) >= -0.0f && (B-A).cross(Q-A).dot(n) >= -0.0f && (A-C).cross(Q-C).dot(n) >= -0.0f && t > 0.0000001f)
            {
                return true;

            }
        }
    }
    return false;
}

float calc_ray(const vector<vec3>& VB, vector<point_light>& LS, vec3 d, vec3 P, int reflection_depth, float default_b)
{
    tuple<int, vec3, vec3> closest_triangle = check_ray(VB,d, P);

    int index = get<0>(closest_triangle);
    if(index == -1)
        return default_b;
    vec3 n = get<1>(closest_triangle);
    vec3 Q = get<2>(closest_triangle);
    float ilumination = 0.0f;
    vec3 l;
    float temp;
    float reflection = 0.0f;
    for(unsigned long long int i = 0; i < LS.size(); i++)
    {
        l = LS[i].pos - Q;
        l = l/l.length();
        temp = n.dot(l)*LS[i].intensity;
        if(temp > 1.0f)
            temp = 1.0f;
        if(temp > 0.0f && !shadow_check(VB ,l ,Q))
            ilumination +=  temp;
    }
    if(ilumination > 1.0f)
        ilumination = 1.0f;
    d = d / d.length();
    n = n / n.length();
    if(reflection_depth > 0)
    {
        reflection += calc_ray(VB, LS, d - 2 * d.dot(n)*n, Q, reflection_depth - 1, default_b);
        return (VB[index+3].x * (ilumination * 0.9f + 0.1f)+ reflection * VB[index+3].z) / (1 + VB[index+3].z);
    }
    return VB[index+3].x * (ilumination * 0.9f + 0.1f);



}


const int WIDTH = 206;
const int HEIGHT = 117;
const float RATIO = (float)WIDTH/HEIGHT;
const int palette_size = 42;

const char palette[] = " .,:;^+<il!t?I[{1jrcoaxznumbOkhXQ8&Z0#MWB@";
int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    clock_t s_time = clock();
    clock_t c_time = clock();

    vec3 d = {-0.0f,-0.75f,-1.0f};
    vec3 P = { 0.0f, 4.0f, 7.50f};

    vector<vec3> cube =
    {
        { 1.0f, 1.0f, 1.0f},{-1.0f, 1.0f, 1.0f},{-1.0f,-1.0f, 1.0f},{1.0f, 1.0f, 0.5f},
        { 1.0f, 1.0f, 1.0f},{-1.0f,-1.0f, 1.0f},{ 1.0f,-1.0f, 1.0f},{1.0f, 1.0f, 0.5f},

        { 1.0f, 1.0f,-1.0f},{ 1.0f, 1.0f, 1.0f},{ 1.0f,-1.0f, 1.0f},{1.0f, 1.0f, 0.5f},
        { 1.0f, 1.0f,-1.0f},{ 1.0f,-1.0f, 1.0f},{ 1.0f,-1.0f,-1.0f},{1.0f, 1.0f, 0.5f},

        {-1.0f, 1.0f,-1.0f},{ 1.0f,-1.0f,-1.0f},{-1.0f,-1.0f,-1.0f},{1.0f, 1.0f, 0.5f},
        {-1.0f, 1.0f,-1.0f},{ 1.0f, 1.0f,-1.0f},{ 1.0f,-1.0f,-1.0f},{1.0f, 1.0f, 0.5f},

        {-1.0f, 1.0f, 1.0f},{-1.0f, 1.0f,-1.0f},{-1.0f,-1.0f,-1.0f},{1.0f, 1.0f, 0.5f},
        {-1.0f, 1.0f, 1.0f},{-1.0f,-1.0f,-1.0f},{-1.0f,-1.0f, 1.0f},{1.0f, 1.0f, 0.5f},

        { 1.0f,-1.0f,-1.0f},{-1.0f,-1.0f, 1.0f},{-1.0f,-1.0f,-1.0f},{1.0f, 1.0f, 0.5f},
        { 1.0f,-1.0f,-1.0f},{ 1.0f,-1.0f, 1.0f},{-1.0f,-1.0f, 1.0f},{1.0f, 1.0f, 0.5f}

        ,

        {-1.0f, 1.0f,-1.0f},{ 0.0f, 1.75f, 0.0f},{ 1.0f, 1.0f,-1.0f},{1.0f, 1.0f, 0.5f},
        {-1.0f, 1.0f, 1.0f},{ 0.0f, 1.75f, 0.0f},{-1.0f, 1.0f,-1.0f},{1.0f, 1.0f, 0.5f},
        { 1.0f, 1.0f, 1.0f},{ 0.0f, 1.75f, 0.0f},{-1.0f, 1.0f, 1.0f},{1.0f, 1.0f, 0.5f},
        { 1.0f, 1.0f,-1.0f},{ 0.0f, 1.75f, 0.0f},{ 1.0f, 1.0f, 1.0f},{1.0f, 1.0f, 0.5f}
    };
    vector<vec3> VB;
    float cube_size = 1.5f;
    float cube_offset = 3.0f;
    for(float i = -0.5f; i <= 0.5f; i++)
    {
        for(float j = -0.5f; j <= 0.5f; j++)
        {
            for(int k = 0; k < cube.size(); k+=4)
            {
                VB.push_back(cube[k  ]*(cube_size/2) + (vec3){i*cube_offset, 0.5f, j*cube_offset});
                VB.push_back(cube[k+1]*(cube_size/2) + (vec3){i*cube_offset, 0.5f, j*cube_offset});
                VB.push_back(cube[k+2]*(cube_size/2) + (vec3){i*cube_offset, 0.5f, j*cube_offset});
                VB.push_back(cube[k+3]);
            }
        }
    }

    int model_size = VB.size();
    vector<point_light> LS =
    {
        /*{0.25f,(vec3){-2.0f,  3.75f, 3.5f}*1.5f},
        {0.25f,(vec3){-2.5f,  3.75f, 3.5f}*1.5f},
        {0.25f,(vec3){-2.0f,  3.5f , 3.5f}*1.5f},*/
        {1.0f,(vec3){-2.5f,  3.5f , 3.5f}*1.5f}
    };
    for(float i = -3.5f; i <= 3.5f; i++)
        for(float j = -3.5f; j <= 3.5f; j++)
        {
                VB.push_back((vec3){ 2.5f*(i + 0.5f),-1.0f, 2.5f*(j + 0.5f)});
                VB.push_back((vec3){ 2.5f*(i + 0.5f),-1.0f, 2.5f*(j - 0.5f)});
                VB.push_back((vec3){ 2.5f*(i - 0.5f),-1.0f, 2.5f*(j - 0.5f)});
                VB.push_back({0.9f*((float)((int)abs(i - j)%2)+ 0.1f), 1.0f, 0.3f});

                VB.push_back((vec3){ 2.5f*(i + 0.5f),-1.0f, 2.5f*(j + 0.5f)});
                VB.push_back((vec3){ 2.5f*(i - 0.5f),-1.0f, 2.5f*(j - 0.5f)});
                VB.push_back((vec3){ 2.5f*(i - 0.5f),-1.0f, 2.5f*(j + 0.5f)});
                VB.push_back({0.9f*((float)((int)abs(i - j)%2) + 0.1f), 1.0f, 0.3f});
        }
    char screen[(WIDTH+1)*HEIGHT];
    int rot_time;
    vector<thread> ThreadVector;
    while(c_time - s_time < CLOCKS_PER_SEC * 20)
    {

        rot_time = clock();

        for(int i = 0; i < model_size; i += 4)
        {
            VB[i]   = rotY((3.1415f/10.0f)*(rot_time - c_time)/CLOCKS_PER_SEC)*VB[i  ];
            VB[i+1] = rotY((3.1415f/10.0f)*(rot_time - c_time)/CLOCKS_PER_SEC)*VB[i+1];
            VB[i+2] = rotY((3.1415f/10.0f)*(rot_time - c_time)/CLOCKS_PER_SEC)*VB[i+2];
        }
        c_time = clock();
        ThreadVector.clear();
        for(int i = 0; i < HEIGHT; i++)
        {
            ThreadVector.emplace_back([&VB, &LS, &d, &P, &screen](int i)
        {
            float temp;
            for(int j = 0; j < WIDTH; j++)
            {
                temp = calc_ray(VB, LS, (vec3(2.0f*(j-WIDTH/2)/WIDTH, 2.0f/RATIO*(i-HEIGHT/2)/HEIGHT ,0.0f)+d), P, 2, 0.0f);
                screen[(HEIGHT - i - 1)*(WIDTH + 1) + j] = palette[(int)((palette_size -1)*temp)];
            }
        }, i);
            screen[(i+1)*(WIDTH+1) - 1] = '\n';
        }
        for(auto& t: ThreadVector)
        {
            t.join();

        }
        SetConsoleCursorPosition(hConsole, {0,1});
        puts(screen);

    }

    return 0;
}
















