
#import <Foundation/Foundation.h>
@class GLTexture;

@interface GLTextureManager : NSObject {
	NSMutableDictionary *textures;
}

@property (nonatomic, retain) NSMutableDictionary *textures;

+ (id) getInstance;
- (id) init;
- (GLTexture *) getTextureWithFilename:(NSString *)filename;
- (GLTexture *) createTextureWithFilename:(NSString *)filename;

@end
