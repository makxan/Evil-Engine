//
//  WaterGrid.h
//  GL
//
//  Created by Robin Rye on 4/2/11.
//  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
//

#ifndef WATERGRID
#define WATERGRID

#include "VectorTypes.h"

#define ROWS 5
#define COLS 10
/*TODO fix to be general for iphone ipad and so on*/
#define SCREENWIDTH_2 3.6f
#define SCREENHEIGHT_2 4.8f

#define CELLWIDTH 2*SCREENWIDTH_2/COLS
#define CELLHEIGHT 2*SCREENHEIGHT_2/ROWS

#define NROFPARTICLES 100
#define DENSITYLIMIT 10

typedef struct {
    unsigned int density;
} GridCell;

typedef struct{
    Vertex2 current;
    Vertex2 previous;
} Particle;


unsigned int vertexToGridIndex(const Vertex2 vert);
Vertex2 middleOfGridCell(unsigned int index);

int disperseParticles(Particle* particles, GridCell* grid);



#endif