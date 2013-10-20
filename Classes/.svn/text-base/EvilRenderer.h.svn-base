#ifndef __EVIL_RENDERER__
#define __EVIL_RENDERER__

#include "DrawData.h"
#include "ShaderManager.h"
#include "DynamicArray.h"

typedef struct {
    GLVersion     version;
    GLfloat       screenHeight;
    GLfloat       screenWidth;
    DynamicArray  drawArray;
    HashMap       resourceMap;
    ShaderManager shaderMng;
} RenderData;

typedef RenderData EvilRenderData;

RenderData newRenderData();

int initRenderData(RenderData* renderer, 
                   GLVersion version,
                   GLfloat screenHeight,
                   GLfloat screenWidth);

int renderData(RenderData* renderer);

ArrayIndex addRenderable(RenderData* renderer, DrawData* draw);

int delRenderable(RenderData* renderer, ArrayIndex index);

void vacuumRenderData(RenderData* renderer);

void destroyRenderData(RenderData* renderer);

#endif // __EVIL_RENDERER__
