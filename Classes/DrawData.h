
#ifndef DRAWDATA
#define DRAWDATA

#include <stdlib.h>
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#include "HashMap.h"
#include "Shader.h"
#include "ShaderManager.h"

// Data used for drawing. 
// TODO: If using VBO for non-static, add dirty flag.
// TODO: Add size argument 
typedef enum DrawType {
    NODRAW = 0,   // Hack for entries overwritten with zeroes.
    COLOURED,     // Coloured vertices.
    COLOUREDBUFF, // Coloured and buffered vertices.
    TEXTURED,     // Textured vertices.
    TEXTUREDBUFF, // Textured and buffered vertices. 
} DrawType;

typedef enum GLVersion {
	ES1,
	ES2
} GLVersion;

typedef struct {
	enum DrawType type;
    GLuint        buffer;
    ShaderProgram program;
	GLenum        primitiveType;
    GLsizei       length;

    const GLfloat* _padding0;
    const GLfloat* _padding1;
    const GLfloat* _padding2;
    const GLfloat* _padding3;
    GLint          _padding4;
    const GLubyte* _padding5;
    GLint          _padding6;
    GLuint         _padding7;
} DrawData;

typedef struct {
    enum DrawType type;
    GLuint        buffer;            // VertexArrayObject buffer.
    ShaderProgram program;           // Shader program to use.
    GLenum        primitiveType;     // Primitive type to draw.
    GLsizei       length;            // Number of vertices.

    const GLfloat* transShapeToBody; // Shape to body matrix.
    const GLfloat* transBodyToWorld; // Body to world matrix.
    const GLfloat* transColours;     // Colour transformation.
    
    const GLfloat* vertices;         // Array of vertices.
    GLint    vsize;                  // Vertex size.

    const GLubyte* colours;          // Array of colours.
    GLint    csize;                  // Colour size.
    GLuint   _padding0;                // Padding.
} DrawColoured;

typedef struct {
    enum DrawType type;
    GLuint        buffer;            // VertexArrayObject buffer.
    ShaderProgram program;           // Shader program to use.
    GLenum        primitiveType;     // Primitive type to draw.
    GLsizei       length;            // Number of vertices.

    const GLfloat* transShapeToBody; // Shape to body matrix.
    const GLfloat* transBodyToWorld; // Body to world matrix.
    const GLfloat* transCoordinates; // Texture coorditate transform.
    
    const GLfloat* vertices;         // Array of vertices.
    GLint          vsize;            // Vertex size.

    const GLfloat* coordinates;      // Array of coordinates.
    GLint          csize;            // Coordinate size.
    GLuint         texture;          // Texture in VRAM.
} DrawTextured;

DrawData* useBuffer(DrawData* drawData);

DrawData* newDrawTextured(DrawData* draw,
                          const GLenum   primitiveType,
                          const GLfloat* vertices,
                          const GLint    size,
                          const GLsizei  length,
                          const GLfloat* transVertToTexcoords,
                          const GLuint   texture);

DrawData* newDrawColoured(DrawData* draw,
                          const GLenum   primitiveType,
                          const GLfloat* vertices,
                          const GLint    verticeSize,
                          const GLsizei  length,
                          const GLubyte* colours,
                          const GLint    colourSize);

int drawSetShapeMatrix(DrawData* drawData, const float* matrix);
int drawSetBodyMatrix(DrawData* drawData, const float* matrix);

void drawData(HashMap* vbotable, ShaderManager* shaderMng, const GLVersion version, DrawData* draw);

DrawType drawType(const DrawData* drawData);

#endif

