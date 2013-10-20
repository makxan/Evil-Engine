//
//  Shader.vsh
//  GL
//
//  Created by Viktor Holmqvist on 2011-02-01.
//  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
//

attribute vec4 position;
attribute vec2 texCoord;
attribute lowp vec4 color;

varying lowp vec4 colorVarying;
varying vec2 fragmentTexCoord;

uniform float translate;
uniform mat3 matrix;
uniform mat3 model2screenMatrix;

void main()
{
    gl_Position = vec4(vec3(position.xy, 1.0) * matrix * model2screenMatrix, 1.0);
    //gl_Position.y += sin(translate) / 2.0;
	
    colorVarying = vec4(color.r, color.g, color.b, 0.0);
	fragmentTexCoord = texCoord;
}
