//
//  SimulateLiquid.c
//  GL
//
//  Created by Marcus Johansson on 2011-04-03.
//  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
//

#include "SimulateLiquid.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "LinkedList.h"

#define min(a,b) (((a) < (b)) ? (a) : (b))


struct particle {
    float x;
    float y;
    float u;
    float v;
    
    float gu;
    float gv;
    
    float T00;
    float T01;
    float T11;
    float cx;
    float cy;
    
    float px[3];
    float py[3];
    float gx[3];
    float gy[3];
    
    int broken;
};

struct node {
    float m;
    float gx;
    float gy;
    
    float u;
    float v;
    
    float ax;
    float ay;
    
    int active; //Boolean

    int x;
    int y;
};

struct settings{
    float density;
    float stiffness;
    float bulkViscosity;
    float elasticity;
    float viscosity;
    float yieldRate;
    float gravity;
    float smoothing;
};

int mul = 6;

struct particle particles[10000];


// Create Grid
struct node grid[163][102];

struct settings s;

float mul2;

int space;

//LinkedNode element =

void initLiquid()
{
    s.density = 2.0f;
    s.stiffness = 1.0f;
    s.bulkViscosity = 1.0f;
    s.elasticity = 0.0f;
    s.viscosity = 0.1f;
    s.yieldRate = 0.0f;
    s.gravity = 0.05f;
    s.smoothing = 1.0f;
    
    mul2 = 1.0f / (float)sqrtf(s.density);
    
    // Calculate particle positions
    int n = 0; //Particle counter
    
    for(int j = 0; j < 100; j++)
    {
        for(int i = 0; i < 100;i++)
        {
            
            srand(time(NULL));
            particles[n].x = ((i + rand()) * mul2) + 4.0f;
            srand(time(NULL));
            particles[n].y = (float)((j + rand()) * mul2)+4.0f;
            particles[n].u = 0.0f;
            particles[n].v = 0.0f;
        }
    }
}

void simulate()
{
    if(space)
    {
        s.density = MIN(10.0f, s.density+0.05f);
        
    }
    
    for(int n = 0; n<10000;n++)
    {
        
    }
}