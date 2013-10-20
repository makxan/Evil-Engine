
#ifndef SHADER
#define SHADER

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

// Attributes in the shader.
enum ShaderAttrib {
    ATTRIB_VERTEX,
    ATTRIB_COLOR,
    ATTRIB_TEXCOORD,
};

// Functions to compile the shaders, create and link the program.

int compileShader(GLuint *shader, const GLenum type, const GLchar *file);
int createProgram(GLuint *shader, const GLchar *vertShaderFile, const GLchar *fragShaderFile);
int linkProgram(GLuint *program);
void addAttributes(GLuint *program);

// Shaders.

const GLchar* defaultVertexShader();
const GLchar* defaultFragmentShader();

#endif
