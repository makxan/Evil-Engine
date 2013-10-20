//
//  WaterGrid.c
//  GL
//
//  Created by Robin Rye on 4/2/11.
//  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
//

#include "WaterGrid.h"
#include <stdlib.h>
#include <math.h>
#include "VectorOps.h"


/*
 * Calculate the index in the grid array for a 
 */
unsigned int vertexToGridIndex(const Vertex2 vert)
{
    int row = ROWS - floor((vert.y + SCREENHEIGHT_2) / CELLHEIGHT);
    int col = floor((vert.x + SCREENWIDTH_2) / CELLWIDTH);
    return row * COLS + col;
}

/*
 * calculate the vertex in the center of a given gridcell
 */
Vertex2 middleOfGridCell(unsigned int index)
{
    div_t res = div(index * CELLWIDTH, 2*SCREENWIDTH_2);
    Vertex2 mid = {res.rem + 0.5f * CELLWIDTH, (res.quot + 0.5f) * CELLHEIGHT};
    return mid;
}

/*
 * Loop the entire grid and disperse the particles in each cell.
 * the force applied to a particle depends on the density of the cell
 * the more particles, the higher the density and thereby more violent dispersion.
 */
int disperseCells(Particle* particles, GridCell* grid)
{
    for(int i = 0; i < NROFPARTICLES; i++)
    {
        //find out what cell particle is in
        Particle p = particles[i];
        int particleIndex = vertexToGridIndex(p.current);
        GridCell cell = grid[particleIndex];
        
        
        //if the density is larger then the limit then apply force to the particle otherwise do nothing to it.
        if(cell.density > DENSITYLIMIT){
            //determine direction
            Vertex2 gridMid = middleOfGridCell(particleIndex);
            Vector2 direction = v2sub(p.current, gridMid);
        
            /*TODO: apply force on particle in direction*/
            direction;
            
            if(cell.density != INFINITY)
                cell.density--;
        }
        
    }
    return 1;
}













