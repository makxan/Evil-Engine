//
//  Shader.vsh
//  ES_unmod
//
//  Created by Sonny Karlsson on 2/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

attribute vec4 position;
attribute lowp vec4 color;
varying lowp vec4 colorVarying;

uniform mat4 worldViewMatrix;
uniform mat4 modelWorldMatrix;

void main()
{
	mat4 modelViewMatrix = (worldViewMatrix * modelWorldMatrix);

    colorVarying = color;
	gl_Position = modelViewMatrix * position;
}
