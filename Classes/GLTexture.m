
#import "GLTexture.h"


@implementation GLTexture
@synthesize filename;

- (id)initWithFilename:(NSString *)inFilename
{
	if ((self = [super init]))
	{
		self.filename = inFilename;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
		
		NSString *extension = [filename pathExtension];
		NSString *baseFilenameWithExtension = [filename lastPathComponent];
		NSString *baseFilename = [baseFilenameWithExtension substringToIndex:[baseFilenameWithExtension length] - [extension length] - 1];
        
		NSString *path = [[NSBundle mainBundle] pathForResource:baseFilename ofType:extension];
		NSData *texData = [[NSData alloc] initWithContentsOfFile:path];
		
        
        UIImage *image = [[UIImage alloc] initWithData:texData];
        
        // Could possibly cause problems (not tested in runtime)
        [texData release];
        if (image == nil)
            return nil;
        
        GLuint width = CGImageGetWidth(image.CGImage);
        GLuint height = CGImageGetHeight(image.CGImage);
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        void *imageData = malloc( height * width * 4 );
        CGContextRef context = CGBitmapContextCreate( imageData, width, height, 8, 4 * width, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big );
        CGContextTranslateCTM (context, 0, height);
        CGContextScaleCTM (context, 1.0, -1.0);
        CGColorSpaceRelease( colorSpace );
        CGContextClearRect( context, CGRectMake( 0, 0, width, height ) );
        CGContextDrawImage( context, CGRectMake( 0, 0, width, height ), image.CGImage );
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
        CGContextRelease(context);
        
        free(imageData);
        [image release];
		
        
	}
	
	return self;
}

- (void)use
{
	glBindTexture(GL_TEXTURE_2D, texture);
}
- (void)dealloc
{
	glDeleteTextures(1, &texture);
	[filename release];
	[super dealloc];
}

+ (GLuint)loadTexture:(NSString *)filename {
    GLuint tex;
    
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
    
    NSString *extension = [filename pathExtension];
    NSString *baseFilenameWithExtension = [filename lastPathComponent];
    NSString *baseFilename = [baseFilenameWithExtension substringToIndex:[baseFilenameWithExtension length] - [extension length] - 1];
    
    NSString *path = [[NSBundle mainBundle] pathForResource:baseFilename ofType:extension];
    NSData *texData = [[NSData alloc] initWithContentsOfFile:path];
    
    
    UIImage *image = [[UIImage alloc] initWithData:texData];
    
    // Could possibly cause problems (not tested in runtime)
    [texData release];
    if (image == nil)
        return 0;
    
    GLuint width = CGImageGetWidth(image.CGImage);
    GLuint height = CGImageGetHeight(image.CGImage);
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    void *imageData = malloc( height * width * 4 );
    CGContextRef context = CGBitmapContextCreate( imageData, width, height, 8, 4 * width, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big );
    CGContextTranslateCTM (context, 0, height);
    CGContextScaleCTM (context, 1.0, -1.0);
    CGColorSpaceRelease( colorSpace );
    CGContextClearRect( context, CGRectMake( 0, 0, width, height ) );
    CGContextDrawImage( context, CGRectMake( 0, 0, width, height ), image.CGImage );
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    CGContextRelease(context);
    
    free(imageData);
    [image release];
    return tex;
}

@end
