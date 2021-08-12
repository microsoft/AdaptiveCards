//
//  MockContext.m
//  AdaptiveCardsTests
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "MockContext.h"

@implementation MockContext {
    BOOL _mockValueForAllHasActionIcons;
}

- (void)setMockValueForAllHasActionIcons:(BOOL)value
{
    _mockValueForAllHasActionIcons = value;
}

- (BOOL)allHasActionIcons
{
    return _mockValueForAllHasActionIcons;
}

@end
