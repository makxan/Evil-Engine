
#include "EvilRenderer.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

#include <CoreFoundation/CoreFoundation.h>

#include "Shader.h"
#include "ShaderManager.h"
#include "MatrixOps.h"

RenderData newRenderData()
{
    return (RenderData){
        .version       = ES1,
        .screenWidth   = 320.0f,
        .screenHeight  = 480.0f,
        .resourceMap   = newHashMap(128),
        .shaderMng     = newShaderManager(),
        .drawArray     = newArray(4, 0, sizeof(DrawData)),
    };
}


int initRenderData(RenderData* renderer, 
                   GLVersion version,
                   GLfloat screenHeight,
                   GLfloat screenWidth)
{
    float worldViewMatrix[16];
    squareIdentity(worldViewMatrix, 4);
    scale(worldViewMatrix,
          100.0f/(screenWidth), 
          100.0f/(screenHeight), 
          1.0f, 
          1.0f);

    if (version == ES1) {
        glEnable(GL_TEXTURE_2D);
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(worldViewMatrix);

    } else if (version == ES2) {

        initShaderManager(&renderer->shaderMng);

        GLuint shader = loadShader(&renderer->shaderMng, COLOURSHADER);
        GLint worldViewLoc = glGetUniformLocation(shader, "worldViewMatrix");
        glUniformMatrix4fv(worldViewLoc, 1, GL_FALSE, worldViewMatrix);

        shader = loadShader(&renderer->shaderMng, TEXTURESHADER);
        worldViewLoc = glGetUniformLocation(shader, "worldViewMatrix");
        glUniformMatrix4fv(worldViewLoc, 1, GL_FALSE, worldViewMatrix);
    }

    glFrontFace(GL_CW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ZERO);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    
    GLint err = glGetError();
    if (err != GL_NO_ERROR) {
        printf("initRenderData: OpenGL error, %d (0x%x).\n", err, err);
        return 0;
    }

    renderer->version      = version;
    renderer->screenHeight = screenHeight;
    renderer->screenWidth  = screenWidth;
    return 1;
}

int initRenderFrame(RenderData* renderer)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    GLint err = glGetError();
    if (err != GL_NO_ERROR) {
        printf("renderFrameInit: OpenGL error, %d (0x%x).\n", err, err);
        return 0;
    }
    return 1;
}

/* Draws all drawable elements in renderer.
 */
int renderData(RenderData* renderer)
{
    if (! initRenderFrame(renderer))
        return 0;

    void renderFunc(DrawData* draw) {
        if (drawType(draw) == NODRAW) { 
            printf("renderFunc: found nodraw\n");
            return;
        }
        drawData(&renderer->resourceMap, &renderer->shaderMng, renderer->version
, draw);
    }
    const DynamicArray* drawArray = &renderer->drawArray;
    arrayMap(drawArray, &renderFunc);
    return 1;
}

/* Copies DrawData into renderer.
 * Copies data from draw into renderer->drawArray.
 * Updates index of copied data and returns pointer to first
 * DrawData struct.
 */
ArrayIndex addRenderable(RenderData* renderer, DrawData* draw) 
{
    if (draw == NULL)
        return UINT_MAX;
    //return drawArrayAdd(&renderer->drawArray, draw);
    return addLast(&renderer->drawArray, (void*)draw, sizeof(*draw));
}

/* Delete renderable from renderer.
 * Sets type of renderer to NODRAW, not really deleting any data.
 */ 
int delRenderable(RenderData* renderer, ArrayIndex index) 
{
    DrawData* draw = getAtIndex(&renderer->drawArray, index);
    if (draw != NULL || drawType(draw) == NODRAW) {
        printf("delRenderable: Renderable not in renderer.");
        return 0;
    }
    draw->type = NODRAW;
    return 1;
}

/* Free unused resources of renderer.
 * Call on memory warning.
 * Note: Probably need to update some RigidBody indices.
 */
void vacuumRenderData(RenderData* renderer);

/* Free all resources of renderer.
 * Prepares Renderer for deletion.
 * Todo: Delete all VAO's.
 * Todo: Delete all textures.
 * Note: glDeleteTexture(GLsizei n, GLuint* textureNames);
 */
void destroyRenderData(RenderData* renderer) 
{
    arrayHardEmpty(&renderer->drawArray);

    const int length   = renderer->resourceMap.length;
    const HashMapEntry* entries = renderer->resourceMap.entries;

    for (int i = 0; i < length; i++) {
        if (entries[i].key != 0) {
            const GLuint vbo = (GLuint)(entries[i].value);
            glDeleteBuffers(1, &vbo);
        }
    }    
    deallocHashMap(&renderer->resourceMap);
    destroyShaderManager(&renderer->shaderMng);
}
