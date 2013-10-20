//
//  Shader.fsh
//  ES_unmod
//
//  Created by Sonny Karlsson on 2/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
	gl_FragColor = colorVarying;
}
