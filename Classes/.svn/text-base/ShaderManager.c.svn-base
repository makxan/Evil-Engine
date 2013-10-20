/*
 *  ShaderManager.c
 *  GL
 *
 *  Created by Sonny Karlsson on 4/29/11.
 *  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
 *
 */

#include "ShaderManager.h"

#include <CoreFoundation/CoreFoundation.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "Shader.h"


ShaderManager newShaderManager() {
    return (ShaderManager){
        .current = NOSHADER,
        .shaders = newArray(3, 0, sizeof(GLuint)),
    };
};

void initShaderManager(ShaderManager* shaderMng) 
{

    char* vertShader = NULL;
    char* fragShader = NULL;

    GLuint colourProgram, textureProgram;

    readShaderSource("colour", GL_VERTEX_SHADER, &vertShader);
    readShaderSource("colour", GL_FRAGMENT_SHADER, &fragShader);

    createProgram(&colourProgram, 
                  vertShader, 
                  fragShader);

    GLint err = glGetError();
    if (err != GL_NO_ERROR) {
        printf("initShaderManager: colShader, OpenGL error, %d (0x%x).\n", 
               err, err);
        exit(0);
    }

    free(vertShader);
    free(fragShader);

    readShaderSource("texture", GL_VERTEX_SHADER, &vertShader);
    readShaderSource("texture", GL_FRAGMENT_SHADER, &fragShader);
        
    createProgram(&textureProgram, 
                  vertShader, 
                  fragShader);    

    err = glGetError();
    if (err != GL_NO_ERROR) {
        printf("initShaderManager: textShader, OpenGL error, %d (0x%x).\n", 
               err, err);
        exit(0);
    }

    free(vertShader);
    free(fragShader);

    arrayForceGrow(&shaderMng->shaders);

    putAtIndex(&shaderMng->shaders, 
               TEXTURESHADER, 
               &textureProgram, 
               sizeof(GLuint));

    putAtIndex(&shaderMng->shaders, 
               COLOURSHADER, 
               &colourProgram, 
               sizeof(GLuint));
}

GLuint currentShader(ShaderManager* shaderMng)
{
    ShaderProgram current = shaderMng->current;
    GLuint program = 0;
    if (current != NOSHADER)
        program = *(GLuint*)(getAtIndex(&shaderMng->shaders, current));
    return program;
}


GLuint loadShader(ShaderManager* shaderMng, ShaderProgram program) 
{
    if (program == NOSHADER) {
        glUseProgram(0);
        shaderMng->current = NOSHADER;
        return 1;
    } else if (shaderMng->current == program)
        return 1;

    const GLuint* sp = getAtIndex(&shaderMng->shaders, program);
    glUseProgram(*sp);

    GLint err = glGetError();
    if (err != GL_NO_ERROR) {
        printf("loadShader: shader %d, OpenGL error, %d (0x%x).\n", 
               program, err, err);
        return 0;
    }
    shaderMng->current = program;
    return *sp;
}

void destroyShaderManager(ShaderManager* shaderMng) 
{
    glUseProgram(0);
    shaderMng->current = NOSHADER;
    
    void deleteProgram(GLuint* program) {
        if (*program == 0)
            return;
        glDeleteProgram(*program);
        *program = 0;
    }
    DynamicArray* shaders = &shaderMng->shaders;
    arrayMap(shaders, &deleteProgram);
    arrayHardEmpty(shaders);
}

int loadFileToMemory(const char *filename, char **result)
{
	int size = 0;
	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		*result = NULL;
		return -1; // Failed to open file.
	}
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	*result = (char *)malloc(size+1);
	if (size != fread(*result, sizeof(char), size, f)) {
		free(*result);
		return -2; // Failed to read file.
	}
	fclose(f);
	(*result)[size] = 0;
	return size;
}	

int readShaderSource(const char* shaderName, 
                     GLenum shaderType,
                     char** shaderSource)
{
    CFStringRef shaderTypeRef;

    if (shaderType == GL_VERTEX_SHADER)
        shaderTypeRef = CFStringCreateWithCString(NULL, "vsh", kCFStringEncodingMacRoman);
    else if (shaderType == GL_FRAGMENT_SHADER)
        shaderTypeRef = CFStringCreateWithCString(NULL, "fsh", kCFStringEncodingMacRoman);
    else {
        printf("readShaderSource: Unknown shader type.\n");
        return -1;
    }

    char shaderPath[1024];

    CFStringRef shaderNameRef = CFStringCreateWithCString(NULL, shaderName, kCFStringEncodingMacRoman);
    CFURLRef    shaderUrl     = CFBundleCopyResourceURL(CFBundleGetMainBundle(), shaderNameRef, shaderTypeRef, NULL);

    CFURLGetFileSystemRepresentation(shaderUrl, true, (UInt8*)shaderPath, sizeof(shaderPath));

    CFRelease(shaderTypeRef);
    CFRelease(shaderNameRef);
    CFRelease(shaderUrl);

    int size = loadFileToMemory(shaderPath, shaderSource);

    if (size == -1) {
        printf("readShaderSource: File not found.\n");
        return -1;
    } else if (size == -2) {
        printf("readShaderSource: File could not be read.\n");
        return -2;
    } else
        return 1;
}
