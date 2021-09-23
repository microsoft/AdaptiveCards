//
//  ACRMockViews.mm
//  AdaptiveCardsTests
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACRMockViews.h"
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

@implementation ACRMockContentStackView

- (instancetype)init
{
    return [super initWithFrame:CGRectMake(0, 0, 100, 100) attributes:nil];
}

- (ACOVisibilityManager *)getVisibilityManager
{
    return _visibilityManager;
}

- (ACOFillerSpaceManager *)getFillerSpaceManager
{
    return _paddingHandler;
}


@end
