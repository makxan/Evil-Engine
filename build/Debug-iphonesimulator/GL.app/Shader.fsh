//
//  Shader.fsh
//  GL
//
//  Created by Viktor Holmqvist on 2011-02-01.
//  Copyright 2011 Chalmers Tekniska Högskola. All rights reserved.
//

varying lowp vec4 colorVarying;
varying mediump vec2 fragmentTexCoord;

uniform sampler2D texture;
uniform int hasTexture;

void main()
{
	if (hasTexture == 1) {
		gl_FragColor = texture2D(texture, fragmentTexCoord);
	} else {
		gl_FragColor = colorVarying;
	}
}
