//
//  Liquid.m
//  Water
//
//  Created by Marcus Johansson on 2011-05-06.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Liquid.h"
#import <math.h>

@implementation Liquid

@synthesize active;

- (id)init
{
    self = [super init];
    if (self) {
        gSizeX = 163;
        gSizeY = 102;
        
        mul=6;
        
        settings[0]= 2.0f;
        settings[1]= 1.0f;
        settings[2]= 1.0f;
        settings[3]= 0.0f;
        settings[4]= 0.1f;
        settings[5]= 0.0f;
        settings[6]= 0.05f;
        settings[7]= 0.0f;
        
        for(int i = 0; i<gSizeX;i++)
        {
            for(int j = 0; j<gSizeY;j++)
            {
                grid[i][j] = [[Node alloc] init];  
            }
        }
        
        float mul2 = 1.0f / (float)sqrt(settings[0]);
        
        if (mul2>0.72) {
            mul2 =0.72f;
        }
        
        int n; //Particles counter
        
        //create new particles and calculate position
        for (int j = 0; j<10; j++) {
            for (int i = 0; i<10; i++) {
                
               float posX=((i+((arc4random()%100)/100))*mul2)+4.0f;
               float posY=((i+((arc4random()%100)/100))*mul2)+4.0f;
                
                Particle *p = [[Particle alloc] initWithPositionX:&posX andY:&posY horizontalVelocity:0.0f andVerticalVelocity:0.0f];
                
                particles[n++]=p; //Add particle to list
            }
        }
    }
    
    return self;
}

-(void)simulate{
    if(space){
        settings[0] = fminf(10.0f, settings[0]+0.05f);
    }
    
    for(Node *n in self.active){
        n.m = (n.gx = n.gy = n.u = n.v = n.ax = n.ay = 0.0f);
        n.active = false;
    }
    
    //for(Particle *p in particles){
      
    for (int i = 0; i < 1000; i++) {
        Particle *p = particles[i];
        
        p.cx = (int)(p.x-0.5f);     //Dunno what this mean, all particles go like hell if variables is changed with +1
        p.cy = (int)(p.y-0.5f);
    
        float x = p.cx-p.x;
        
        p.px[0] = (0.5f * x * x + 1.5f * x + 1.125f);
        p.gx[0] = (x + 1.5f);
        
        x += 1.0f;
        
        p.px[1] = (-x * x +0.75f);
        p.gx[1] = (-2.0f * x);
        
        x += 1.0f;
        
        p.px[2] = (0.5f * x * x - 1.5f * x + 1.125f);
        p.gx[2] = (x - 1.5f);
        
        float y = p.cy-p.y;
        
        p.py[0] = (0.5f * y * y + 1.5f * y +1.125f);
        p.gy[0] = (y - 1.5f);
        
        y += 1.0f;
        
        p.py[1] = (-y * y + 0.75f);
        p.gy[1] = (-2.0f * y);
        
        p.py[2] = (0.5f * y * y - 1.5f * y + 1.125f);
        p.gy[2] = (y - 1.5f);
        
        for (int i = 0; i<3; i++) {
            for (int j = 0; j<3; j++) {
                int cxi = p.cx + i;
                int cyj = p.cy + j;
                
                Node *n = grid[cxi][cyj];
                if(!n.active){
                    [active addObject:n];
                    n.active=true;
                }
                
                float phi = p.px[i] * p.py[j];
                n.m += phi;
                
                float dx = p.gx[i] * p.py[j];
                float dy = p.px[i] * p.gy[j];
                
                n.gx += dx;
                n.gy += dy;
                
                n.u += phi * p.u;
                n.v += phi * p.v;
                
            }
        }
    
    
    }
    
    for(Node *n in active)
    {
        if (n.m>0.0f) {
            n.u /= n.m;
            n.v /=n.m;
        }
      
        
        //for(Particle *p in particles)
        for (int i = 0; i < 1000; i++) {
            Particle *p = particles[i];
            float dudx = 0.0f;
            float dudy = 0.0f;
            float dvdx = 0.0f;
            float dvdy = 0.0f;
            
            
            
            for (int i = 0; i<3; i++) {
                for (int j = 0; j<3; j++) {
                    Node *n = grid[p.cx + i][p.cy + j];
                    
                    float gx = p.gx[i] * p.py[j];
                    float gy = p.px[i] * p.gy[j];
                    
                    dudx += n.u * gx;
                    dudy += n.u * gy;
                    dvdx += n.v * gx;
                    dvdy += n.v * gy;
                }
            }
            
            float w1 = dudy - dvdx;
            float wT0 = w1 * p.T01;
            float wT1 = 0.5f * w1 * (p.T00 - p.T11);
            
            float D00 = dudx;
            float D01 = 0.5f * (dudy - dvdx);
            float D11 = dvdy;
            
            float trace = 0.5f * (D00 + D11);
            
            D00 -= trace;
            D11 -= trace;
            
            p.T00 += -wT0 + D00 - settings[5] * p.T00;
            p.T01 += wT1 + D01 - settings[5] * p.T01;
            p.T11 += wT0 + D11 - settings[5] * p.T11;
            
          //  float norm = p.T00 * p.T00 + 2.0f * p.T01 * p.T01 + p.T11 * p.T11;
            
           /* if((mode > -1) || (norm > 5.0f))
            {
                p.T00 = (p.T01 = p.T11 = 0.0f);
            }*/
            
            int cx = (int)p.x;
            int cy = (int)p.y;
            
            int cxi = cx + 1;
            int cyi = cy + 1;
            
            float p00 = grid[cx][cy].m;
            float x00 = grid[cx][cy].gx;
            float y00 = grid[cx][cy].gy;
            float p01 = grid[cx][cyi].m;
            float x01 = grid[cx][cyi].gx;
            float y01 = grid[cx][cyi].gy;
            float p10 = grid[cxi][cy].m;
            float x10 = grid[cxi][cy].gx;
            float y10 = grid[cxi][cy].gy;
            float p11 = grid[cxi][cyi].m;
            float x11 = grid[cxi][cyi].gx;
            float y11 = grid[cxi][cyi].gy;
            
            float pdx = p10 - p00;
            float pdy = p01 - p00;
            
            float C20 = 3.0f * pdx - x10 + x00;
            float C02 = 3.0f * pdy - y01 - 2.0f * y00;
            float C30 = -2.0f * pdx + x10 + x00;
            float C03 = -2.0f * pdy + y01 + y00;
            
            float csum1 = p00 + y00 + C02 + C03;
            float csum2 = p00 + x00 + C20 + C30;
            
            float C21 = 3.0f * p11 - 2.0f * x01 - x11 - 3.0f * csum1 - C20;
            float C31 = -2.0f * p11 + x01 + x11 + 2.0f * csum1 - C30;
            float C12 = 3.0F * p11 - 2.0F * y10 - y11 - 3.0F * csum2 - C02;
            float C13 = -2.0F * p11 + y10 + y11 + 2.0F * csum2 - C03;
            float C11 = x01 - C13 - C12 - x00;
            
            float u = p.x - cx;
            float u2 = u * u;
            float u3 = u * u2;
            
            float v = p.y - cy;
            float v2 = v * v;
            float v3 = v * v3;
            
            float density = p00 + x00 * u + y00 * v + C20 * u2 + C02 * v2 +
                            C30 * u3 + C03 * v3 + C21 * u2 * v + C31 * u3 * v +
                            C12 * u * v2 + C13 * u * v3 + C11 * u *v;
            
            // Calculate pressure through density: stiffness/(densitySetting*deltaDensity)
            float pressure = settings[1] / MAX(1.0f, settings[0]) *
            (density - settings[0]);
            
            if (pressure > 2.0f) {
                pressure = 2.0f;
            }
            
            float fx = 0.0f;
            float fy = 0.0f;
            
            if(p.x < 3.0f){
                fx += 3.0f - p.x;
            }
            else if(p.x>gSizeX - 4){
                fx += gSizeX - 4 - p.x;
            }
            
            if(p.y < 3.0f){
                fy += 3.0f - p.y;
            }
            else if(p.y > gSizeY - 4){
                fy += gSizeY - 4 - p.y;
            }
            
            trace *= settings[1]; //Trace is trace*stiffness
            float T00 = settings[3] * p.T00 + settings[4] * D00 + pressure + settings[2] * trace;;
            float T01 = settings[3] * p.T01 + settings[4] * D01;
            float T11 = settings[3] * p.T11 + settings[4] * D11 + pressure + settings[2] * trace;
            
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    Node *n = grid[p.cx + i][p.cy + j];
                    
                    float phi = p.px[i] * p.py[j];
                    float dx = p.gx[i] * p.py[j];
                    float dy = p.px[i] * p.gy[j];
                    
                    n.ax += -(dx * T00 + dy * T01) + fx * phi;
                    n.ay += -(dx * T01 + dy * T11) + fy * phi;
                }
            }
        }
        
        for(Node *n in active){
            if(n.m > 0.0f){
                n.ax /= n.m;
                n.ay /= n.m;
                n.u = 0.0f;
                n.v = 0.0f;
            }
        }
        
       // for(Particle p in particles){
         
        for (int i = 0; i < 1000; i++) {
            Particle *p = particles[i];
            
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    Node *n = grid[p.cx +i][p.cy+j];
                    
                    float phi = p.px[i]*p.py[j];
                   
                    p.u += phi * n.ax;
                    p.v += phi * n.ay;
                }
            }
            p.v += settings[6];
            
            //Mouse drag row 368
            
            float x = p.x + p.u;
            float y = p.y + p.v;
            
            if(x < 2.0f){
                p.u += 2.0f - x + (float)((arc4random()%100)/100) * 0.01f;
            }
            else if(x > gSizeX - 3){
                p.u += gSizeX - 3 - x - (float)((arc4random()%100)/100)*0.01f;
            }
            
            if(y < 2.0f){
                p.v += 2.0f - y + (float)((arc4random()%100)/100)* 0.01f;
            }
            else if(y > gSizeY - 3){
                p.v += gSizeY - 3 - y - (float)((arc4random()%100)/100) * 0.01f;
            }
            
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    Node *n = grid[p.cx + i][p.cy + j];
                    float phi = p.px[i] * p.py[j];
                    n.u += phi * p.u;
                    n.v += phi * p.v;
                }
            }
        }
        
        for(Node *n in active){
            if(n.m > 0.0f)
            {
                n.u /= n.m;
                n.v /= n.m;
            }
        }
        
        //for(Particle p in particles)
        //{
        for (int i = 0; i < 1000; i++) {
            Particle *p = particles[i];
            
            float gu = 0.0f;
            float gv = 0.0f;
            
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    Node *n = grid[p.cx + i][p.cy + j];
                    float phi = p.px[i] * p.py[j];
                    gu += phi * n.u;
                    gv += phi * n.v;
                }
            }
            
            p.gu = gu;
            p.gv = gv;
            
            p.x += gu;
            p.y += gv;
            
            p.u += settings[7] * (gu - p.u);
            p.v += settings[7] * (gv - p.v);
        }
    }
    
}

- (void)dealloc
{
    [super dealloc];
}

@end
