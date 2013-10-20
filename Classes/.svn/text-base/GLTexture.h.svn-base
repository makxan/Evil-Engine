
#import <Foundation/Foundation.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

@interface GLTexture : NSObject {
	GLuint		texture;  
	NSString	*filename;
}
@property (nonatomic, retain) NSString *filename;
- (id)initWithFilename:(NSString *)filename;
- (void)use;
+ (GLuint)loadTexture:(NSString *)filename;
@end
