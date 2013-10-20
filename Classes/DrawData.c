/*
 *  DrawData.c
 *  GL
 *
 *  Created by Sonny Karlsson on 3/22/11.
 *  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
 *
 */

#include "DrawData.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#include "Shader.h"
#include "MatrixOps.h"

#pragma mark Constructors

DrawData* newDrawTextured(DrawData* draw,
                          const GLenum   primitiveType,
                          const GLfloat* vertices,
                          const GLint    size,
                          const GLsizei  length,
                          const GLfloat* transVertToTexcoords,
                          const GLuint   texture)
{
    assert(sizeof(DrawData) == sizeof(DrawTextured));

    DrawTextured textured = {
        .type             = TEXTURED,
        .buffer           = 0,
        .program          = TEXTURESHADER,
        .primitiveType    = primitiveType,
        .length           = length,
        .transShapeToBody = IDENTITY_MATRIX,
        .transBodyToWorld = IDENTITY_MATRIX,
        .transCoordinates = IDENTITY_MATRIX,
        .vertices         = vertices,
        .vsize            = size,
        .coordinates      = vertices,
        .csize            = size,
        .texture          = texture,
    };
    memcpy(draw, &textured, sizeof(textured));
	return draw;
}

DrawData* newDrawColoured(DrawData* draw,
                          const GLenum   primitiveType,
                          const GLfloat* vertices,
                          const GLint    verticeSize,
                          const GLsizei  length,
                          const GLubyte* colours,
                          const GLint    colourSize)
{
    assert(sizeof(DrawData) == sizeof(DrawColoured));

    DrawColoured coloured = {
        .type             = COLOURED,
        .buffer           = 0,
        .program          = COLOURSHADER,
        .primitiveType    = primitiveType,
        .length           = length,
        .transShapeToBody = IDENTITY_MATRIX,
        .transBodyToWorld = IDENTITY_MATRIX,
        .transColours     = IDENTITY_MATRIX,
        .vertices         = vertices,
        .vsize            = verticeSize,
        .colours          = colours,
        .csize            = colourSize,
    };

    assert(coloured.vertices == vertices);

    memcpy(draw, &coloured, sizeof(coloured));
	return draw;
}

DrawData* useBuffer(DrawData* draw)
{
    switch (drawType(draw)) {
    case TEXTURED:
        draw->type = TEXTUREDBUFF;
        break;
    case COLOURED:
        draw->type = COLOUREDBUFF;
        break;
    default:
        printf("useBuffer: DrawData already buffered or of unknown type.");
    }
    return draw;
}

#pragma mark Manipulators

DrawType drawType(const DrawData* drawData) {
    if (drawData == NULL) {
        printf("drawType: NULL has no type.\n");
        return NODRAW;
    }
	return drawData->type;
}

size_t sizeofDraw(DrawData* draw) {
    switch (drawType(draw)) {
    case TEXTURED:
    case TEXTUREDBUFF:
        return sizeof(DrawTextured);
    case COLOURED:
    case COLOUREDBUFF:
        return sizeof(DrawColoured);
    default:
        printf("sizeofDraw: Unexpected type.\n");
        return 0;
    }
}

int drawSetShapeMatrix(DrawData* drawData, const float* matrix) 
{
	if (drawData == NULL)
		return 0;
	
	switch (drawType(drawData)) {
    case TEXTURED:
    case TEXTUREDBUFF: {
        DrawTextured* textured = (DrawTextured*)drawData;
        textured->transShapeToBody = matrix;
        return 1;
    }
    case COLOURED:
    case COLOUREDBUFF: {
        DrawColoured* coloured = (DrawColoured*)drawData;
        coloured->transShapeToBody = matrix;
        return 1;
    }
    default:
        printf("drawSetShapeMatrix: Unknown type.\n");
        return 0;
    }
}

int drawSetBodyMatrix(DrawData* drawData, const float* matrix) {

	if (drawData == NULL)
		return 0;
	
	switch (drawType(drawData)) {
    case TEXTURED:
    case TEXTUREDBUFF: {
        DrawTextured* textured = (DrawTextured*)drawData;
        textured->transBodyToWorld = matrix;
        return 1;
    }
    case COLOURED:
    case COLOUREDBUFF: {
        DrawTextured* coloured = (DrawTextured*)drawData;
        coloured->transBodyToWorld = matrix;
        return 1;
    }
    default:
        printf("drawSetShapeMatrix: Unknown type.\n");
        return 0;
    }
}

#pragma mark Drawing

void drawBuffer(HashMap* vbotable, ShaderManager* shaderMng, const GLVersion version, DrawData* draw);
void drawUnbuffered(ShaderManager* shaderMng, const GLVersion version, DrawData* draw);

void setupDrawData(HashMap* vbotable, const GLVersion version, DrawData* data);

void loadUniformsES1(DrawData *data);
void loadUniformsES2(DrawData *data, GLuint program);

void drawData(HashMap* vbotable, ShaderManager* shaderMng, const GLVersion version, DrawData* draw) {
	if (draw == NULL)
		return;
	
	switch (draw->type) {
    case COLOURED:
    case TEXTURED:
        drawUnbuffered(shaderMng, version, draw);
        break;
    case COLOUREDBUFF:
    case TEXTUREDBUFF:
        drawBuffer(vbotable, shaderMng, version, draw);
        break;
    default:
        printf("drawData: Unknown type.\n");
        break;
	}
}

void drawBuffer(HashMap* vbotable, ShaderManager* shaderMng, const GLVersion version, DrawData* draw)
{
	if (version == ES2) {
        loadShader(shaderMng, draw->program);
		loadUniformsES2(draw, currentShader(shaderMng));
	} else if (version == ES1)
		loadUniformsES1(draw);

	const GLenum type    = draw->primitiveType;
	const GLsizei length = draw->length;
	assert(length > 0);
	GLuint buffer = draw->buffer;
	if(buffer == 0) {
		glGenVertexArraysOES(1, &buffer);
		glBindVertexArrayOES(buffer);
		setupDrawData(vbotable, version, draw);
		draw->buffer = buffer;
		glBindVertexArrayOES(0);
	}
	
	glBindVertexArrayOES(buffer);	
	glDrawArrays(type, 0, length);
	glBindVertexArrayOES(0);
}

void drawUnbuffered(ShaderManager* shaderMng, const GLVersion version, DrawData* draw)
{
	const GLenum  type   = draw->primitiveType;
	const GLsizei length = draw->length;
	
	if (version == ES2) {
        loadShader(shaderMng, draw->program);
		loadUniformsES2(draw, currentShader(shaderMng));
	} else if (version == ES1)
		loadUniformsES1(draw);
	
	setupDrawData(NULL, version, draw);
	
	glDrawArrays(type, 0, length);	
}

#pragma mark DrawData loading

void setupColoured(HashMap* vbotable, const GLVersion version, const DrawColoured* draw);
void setupTextured(HashMap* vbotable, const GLVersion version, const DrawTextured* draw);

void setupColourVertices(HashMap* vbotable,
                         const GLVersion version,
                         const DrawColoured* draw);

GLuint bindFloatBufferObject(HashMap* vbotable, const GLfloat* array, const GLuint size, const GLsizei length);
GLuint bindUByteBufferObject(HashMap* vbotable, const GLubyte* array, const GLuint size, const GLsizei length);

void setupDrawData(HashMap* vbotable, const GLVersion version, DrawData* draw)
{
	if (draw == NULL)
		return;
	switch (drawType(draw)) {
    case TEXTURED:
    case TEXTUREDBUFF:
        setupTextured(vbotable, version, (DrawTextured*)draw);
        break;
    case COLOURED:
    case COLOUREDBUFF:
        setupColoured(vbotable, version, (DrawColoured*)draw);
        break;
    default:
        printf("setupDrawData: Unexpected type encountered.\n");
        break;
	}
};

void setupColoured(HashMap* vbotable, 
                   const GLVersion version, 
                   const DrawColoured* draw) 
{
    const GLsizei  length   = draw->length;
    const GLfloat* vertices = draw->vertices;
    const GLint    vsize    = draw->vsize;
    const GLubyte* colours  = draw->colours;
    const GLint    csize    = draw->csize;

    assert(length > 0);
    assert(vertices != NULL);
    assert(colours != NULL);
    assert(vsize > 0);
    assert(csize > 0);

    if (version == ES2) {
        if (draw->type == COLOUREDBUFF) {
            bindFloatBufferObject(vbotable, vertices, vsize, length);
            vertices = NULL;
        }
		glVertexAttribPointer(ATTRIB_VERTEX, 
                              vsize, 
                              GL_FLOAT, 
                              GL_FALSE, 
                              0, 
                              vertices);
		glEnableVertexAttribArray(ATTRIB_VERTEX);

        if (draw->type == COLOUREDBUFF) {
            bindUByteBufferObject(vbotable, colours, csize, length);
            colours = NULL;
        }
		glVertexAttribPointer(ATTRIB_COLOR, 
                              csize, 
                              GL_UNSIGNED_BYTE, 
                              GL_TRUE, 
                              0, 
                              colours);
		glEnableVertexAttribArray(ATTRIB_COLOR);
    } else if (version == ES1) {
        if (draw->type == COLOUREDBUFF) {
            bindFloatBufferObject(vbotable, vertices, vsize, length);
            vertices = NULL;
        }
		glVertexPointer(vsize, GL_FLOAT, 0, vertices);
		glEnableClientState(GL_VERTEX_ARRAY);

        if (draw->type == COLOUREDBUFF) {
            bindUByteBufferObject(vbotable, colours, csize, length);
            colours = NULL;
        }
		glColorPointer(csize, GL_UNSIGNED_BYTE, 0, colours);
		glEnableClientState(GL_COLOR_ARRAY);
    }
}

void setupTextured(HashMap* vbotable, 
                   const GLVersion version, 
                   const DrawTextured* draw)
{
    const GLsizei  length      = draw->length;
    const GLfloat* vertices    = draw->vertices;
    const GLint    vsize       = draw->vsize;
    const GLfloat* coordinates = draw->coordinates;
    const GLint    csize       = draw->csize;

    if (version == ES2) {
        if (draw->type == TEXTUREDBUFF) {
            bindFloatBufferObject(vbotable, vertices, vsize, length);
            vertices = NULL;
        }
		glVertexAttribPointer(ATTRIB_VERTEX, 
                              vsize, 
                              GL_FLOAT, 
                              GL_FALSE, 
                              0, 
                              vertices);
		glEnableVertexAttribArray(ATTRIB_VERTEX);

        if (draw->type == TEXTUREDBUFF) {
            bindFloatBufferObject(vbotable, coordinates, csize, length);
            coordinates = NULL;
        }
		glVertexAttribPointer(ATTRIB_TEXCOORD, 
                              csize, 
                              GL_FLOAT, 
                              GL_FALSE, 
                              0, 
                              coordinates);
		glEnableVertexAttribArray(ATTRIB_TEXCOORD);
    } else if (version == ES1) {
        if (draw->type == TEXTUREDBUFF) {
            bindFloatBufferObject(vbotable, vertices, vsize, length);
            vertices = NULL;
        }
		glVertexPointer(vsize, GL_FLOAT, 0, vertices);
        glEnableClientState(GL_VERTEX_ARRAY);

        if (draw->type == TEXTUREDBUFF) {
            bindFloatBufferObject(vbotable, coordinates, csize, length);
            coordinates = NULL;
        }
		glTexCoordPointer(csize, GL_FLOAT, 0, coordinates);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    }
}

GLuint bindFloatBufferObject(HashMap* vbotable, 
							 const GLfloat* array, 
							 const GLuint size, 
							 const GLsizei length)
{
	GLuint vbo = (GLuint)lookupEntry(vbotable, (int)array);
	if (vbo == 0) {
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, length * size * sizeof(GLfloat), array, GL_STATIC_DRAW);
		insertEntry(vbotable, (int)array, (void*)vbo);
	} else {
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
	}
	return vbo;
};

GLuint bindUByteBufferObject(HashMap* vbotable, 
							 const GLubyte* array, 
							 const GLuint size, 
							 const GLsizei length)
{
	GLuint vbo = (GLuint)lookupEntry(vbotable, (int)array);
	if (vbo == 0) {
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, length * size * sizeof(GLubyte), array, GL_STATIC_DRAW);
		insertEntry(vbotable, (int)array, (void*)vbo);
	} else {
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
	}
	return vbo;
};

#pragma mark Uniform loading

void loadUniformsES1(DrawData *draw) 
{
	if (draw == NULL)
		return;
	switch(drawType(draw)) {
    case COLOURED:
    case COLOUREDBUFF: {
        DrawColoured* coloured = (DrawColoured*)draw;
        const float* shapeToBody = coloured->transShapeToBody;
        const float* bodyToWorld = coloured->transBodyToWorld;
        static float matrix[16];
        multm4x4(matrix, shapeToBody, bodyToWorld);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(matrix);
        break;
    }
    case TEXTURED:
    case TEXTUREDBUFF: {
        DrawTextured* textured = (DrawTextured*)draw;
        const float* shapeToBody = textured->transShapeToBody;
        const float* bodyToWorld = textured->transBodyToWorld;
        const GLuint texture     = textured->texture;
        float matrix[16];
        multm4x4(matrix, shapeToBody, bodyToWorld);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(matrix);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        break;
    }
    default:
        break;
    }
}

void loadUniformsES2(DrawData *draw, GLuint program) 
{
	if (draw == NULL)
		return;
	switch(drawType(draw)) {
    case COLOURED:
    case COLOUREDBUFF: {
        DrawColoured* coloured = (DrawColoured*)draw;
        const float* shapeToBody = coloured->transShapeToBody;
        const float* bodyToWorld = coloured->transBodyToWorld;

        float modelWorldMatrix[16];
        multm4x4(modelWorldMatrix, shapeToBody, bodyToWorld);

        glUniformMatrix4fv(glGetUniformLocation(program, "modelWorldMatrix"), 
                           1, 
                           GL_FALSE,
                           modelWorldMatrix);
        break;
    }
    case TEXTURED:
    case TEXTUREDBUFF: {
        DrawTextured* textured = (DrawTextured*)draw;
        const float* shapeToBody   = textured->transShapeToBody;
        const float* bodyToWorld   = textured->transBodyToWorld;
        const float* textureMatrix = textured->transCoordinates;
        const GLuint texture       = textured->texture;

        float modelWorldMatrix[16];
        multm4x4(modelWorldMatrix, shapeToBody, bodyToWorld);

        glUniformMatrix4fv(glGetUniformLocation(program, "modelWorldMatrix"), 
                           1, 
                           GL_FALSE,
                           modelWorldMatrix);

        glUniform1i(glGetUniformLocation(program, "texture"), 0);
        glUniformMatrix4fv(glGetUniformLocation(program, "textureMatrix"), 
                           1, 
                           GL_FALSE, 
                           textureMatrix);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        break;
    }
    default:
        break;
    }
}
