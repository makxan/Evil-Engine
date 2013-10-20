
#import "GLTextureManager.h"
#import "GLTexture.h"

static GLTextureManager *instance;

@implementation GLTextureManager
@synthesize textures;

- (GLTexture *) createTextureWithFilename:(NSString *)filename
{
	if ([self.textures objectForKey:filename] == nil) {
		GLTexture *texture = [[GLTexture alloc] initWithFilename:filename];
		if (texture != nil) {
			[textures setObject:texture forKey:filename];
		}
		[texture release];
	}
	return [textures objectForKey:filename];
}

- (GLTexture *) getTextureWithFilename:(NSString *) filename
{
	if ([textures objectForKey:filename] == nil) {
		[self createTextureWithFilename:filename];
	}
	return [textures objectForKey:filename];
}

+ (id) getInstance
{
	if (instance == nil) {
		instance = [[GLTextureManager alloc] init];
	}
	return instance;
}

- (id) init
{
		if ((self = [super init])) {
			NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
			self.textures = dictionary;
			[dictionary release];
		}
	return self;
}

-(NSUInteger) retainCount {
	return UINT_MAX;
}

- (id)retain{
	return self;
}

- (id)autorelease {
	return self;
}

- (void) dealloc
{
	[textures release];
	[super dealloc];
}

@end
