//
//  ACRUIImageView.m
//  AdaptiveCards
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACRUIImageView.h"
#import "ACRContentHoldingUIView.h"
#else
#import <AdaptiveCards/ACRUIImageView.h>
#import <AdaptiveCards/ACRContentHoldingUIView.h>
#endif

@implementation ACRUIImageView

- (instancetype)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];
    if (self) {
        self.tag = eACRUIImageTag;
    }
    return self;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        self.tag = eACRUIImageTag;
        self.desiredSize = frame.size;
    }
    return self;
}

@end
