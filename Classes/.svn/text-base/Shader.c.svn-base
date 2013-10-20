
#include "Shader.h"

#include <stdlib.h>
#include <stdio.h>

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

void addAttributes(GLuint *program) {
    glBindAttribLocation(*program, ATTRIB_VERTEX, "position");
    glBindAttribLocation(*program, ATTRIB_COLOR, "color");
    //glBindAttribLocation(*program, ATTRIB_TEXCOORD, "texCoord");
}

int compileShader(GLuint *shader, const GLenum type, const GLchar *file) {
    
    GLint status;
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &file, NULL);
    glCompileShader(*shader);
    
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    return status == GL_TRUE;
}

int createProgram(GLuint *program, const GLchar *vertShaderFile, const GLchar *fragShaderFile) {
    GLuint vertShader;
    GLuint fragShader;
    
    if(!vertShaderFile) {
        printf("Failed to load vertex shader");
        return 0;
    }
    
    if(!fragShaderFile) {
        printf("Failed to load fragment shader");
        return 0;
    }
    
    *program = glCreateProgram();
    
    if(!compileShader(&vertShader, GL_VERTEX_SHADER, vertShaderFile)) {
        printf("Vertex shader compile error\n");
        //return 0;
    }
    
    if(!compileShader(&fragShader, GL_FRAGMENT_SHADER, fragShaderFile)) {
        printf("Fragment shader compile error\n");
        //return 0;
    }

    glAttachShader(*program, vertShader);
    glAttachShader(*program, fragShader);
    
    if(!linkProgram(program)) {
        printf("Link program failed\n");
        return 0;
    }
    
    if (vertShader)
        glDeleteShader(vertShader);
    if (fragShader)
        glDeleteShader(fragShader);
    
    return 1;
}

int linkProgram(GLuint *program) {
    
    GLint status;
    
    addAttributes(program);
    
    glLinkProgram(*program);
    glValidateProgram(*program);
    
    glGetProgramiv(*program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
        return 0;
    
    return 1;
}

const GLchar* defaultVertexShader() {
    static const GLchar* shader =
    "attribute vec4 position;\
    attribute vec2 texCoord;\
    attribute lowp vec4 color;\
    varying lowp vec4 colorVarying;\
    uniform mat4 worldViewMatrix;\
    uniform mat4 modelWorldMatrix;\
    void main()\
    {\
    gl_Position = (worldViewMatrix * modelWorldMatrix) * position;\
    colorVarying = color;\
    }";
    return shader;
}

const GLchar* defaultFragmentShader() {
    static const GLchar* shader = \
    "varying lowp vec4 colorVarying;\
    void main()\
    {\
    gl_FragColor = colorVarying;\
    }";
    return shader;
}

