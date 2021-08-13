//
//  MockACRView.m
//  AdaptiveCardsTests
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "MockACRView.h"
#import "MockContext.h"
#import <Foundation/Foundation.h>

@implementation MockACRView

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    return self;
}

- (void)setMockContext:(MockContext *)context
{
    if (context) {
        [self setContext:context];
        _mockContext = context;
    }
}

@end
