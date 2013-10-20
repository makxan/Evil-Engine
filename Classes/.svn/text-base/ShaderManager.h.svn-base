/*
 *  ShaderManager.h
 *  GL
 *
 *  Created by Sonny Karlsson on 4/29/11.
 *  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
 *
 */

#ifndef __SHADER_MANAGER__
#define __SHADER_MANAGER__

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#include "DynamicArray.h"

typedef enum {
	NOSHADER      = 0,
	TEXTURESHADER = 1,
	COLOURSHADER  = 2,
    DEFAULTSHADER = 3,
} ShaderProgram;

typedef struct {
	ShaderProgram current;
	DynamicArray  shaders;
} ShaderManager;

ShaderManager newShaderManager();

void initShaderManager(ShaderManager* shaderMng);

GLuint currentShader(ShaderManager* shaderMng);

GLuint loadShader(ShaderManager* shaderMng, ShaderProgram program);

void destroyShaderManager(ShaderManager* shaderMng);

int readShaderSource(const char* shaderName, 
                     GLenum shaderType,
                     char** shaderSource);

int loadFileToMemory(const char *filename, char **result);

#endif // __SHADER_MANAGER__
