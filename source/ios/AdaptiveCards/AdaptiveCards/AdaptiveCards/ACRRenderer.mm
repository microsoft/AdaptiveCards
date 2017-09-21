//
//  ACRRenderer.mm
//  ACRRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACRRenderer.h"
#import "ACRViewController.h"
#import "ACOAdaptiveCardsInternal.h"

@implementation ACRRenderer

- (instancetype)init
{
    self = [super init];
    return self;
}

+ (ACRRenderResult *)render:(ACOAdaptiveCards *)card config:(ACOHostConfig *)config frame:(CGRect)frame
{
    ACRRenderResult *result = [[ACRRenderResult alloc] init];

    ACRViewController *viewcontroller = [[ACRViewController alloc] init:card
                                                             hostconfig:config
                                                                  frame:frame];

    result.viewcontroller = viewcontroller;
    result.succeeded = YES;
    return result;
}

@end
