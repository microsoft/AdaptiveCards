//
//  ACOBaseActionElement
//  ACOBaseActionElement.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "ACOBaseActionElement.h"
#import "BaseActionElement.h"

using namespace AdaptiveCards;

@implementation ACOBaseActionElement
{
    std::shared_ptr<BaseActionElement> _elem;
}

- (instancetype)init
{
    self = [super init];
    return self;
}

- (std::shared_ptr<BaseActionElement>)getElem
{
    return _elem;
}

- (void)setElem:(std::shared_ptr<BaseActionElement> const &)elem
{
    _elem = elem;
}

@end
