//
//  Shader.vsh
//  ES_unmod
//
//  Created by Sonny Karlsson on 2/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

attribute vec4 position;
attribute vec2 textureCoord;

varying vec2 fragTextureCoord;

uniform mat4 worldViewMatrix;
uniform mat4 modelWorldMatrix;
uniform mat4 textureMatrix;

void main()
{
	mat4 modelViewMatrix = (worldViewMatrix * modelWorldMatrix);

	gl_Position = modelViewMatrix * position;

    fragTextureCoord = (textureMatrix * vec4(textureCoord, 0.0, 0.0)).xy;    
}
