//
//  ACOIResourceResolver.h
//  ACOIResourceResolver
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol ACOIResourceResolver

// only one IF per scheme is supported
@optional
- (UIImage *)resolveImageResource:(NSURL *)url;

- (UIImageView *)resolveImageViewResource:(NSURL *)url;

- (UIImageView *)resolveBackgroundImageViewResource:(NSURL *)url hasStretch:(BOOL)hasStretch;

@end
