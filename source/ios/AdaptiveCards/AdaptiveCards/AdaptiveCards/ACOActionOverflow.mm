//
//  ACOActionOverflow
//  ACOActionOverflow.m
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACOActionOverflow.h"
#import "ACOBaseActionElementPrivate.h"
#import "BaseActionElement.h"
#import <Foundation/Foundation.h>

using namespace AdaptiveCards;

@implementation ACOActionOverflow {
    NSMutableArray<ACOBaseActionElement*>* _menuActions;
}

- (instancetype)init
{
    return [self initWithBaseActionElements:{}];
}

- (instancetype)initWithBaseActionElements:(const std::vector<std::shared_ptr<BaseActionElement>> &)elements
{
    std::shared_ptr<BaseActionElement> fakeElem(new BaseActionElement(ActionType::Overflow));
    self = [super initWithBaseActionElement:fakeElem];
    if (self) {
        super.type = ACRActionType::ACROverflow;
        [self setActions:elements];
    }
    return self;
}

- (NSArray<ACOBaseActionElement*>*)menuActions
{
    return _menuActions;
}

- (void)setMenuActions:(NSArray*)menuActions
{
    _menuActions = [menuActions mutableCopy];
}

- (void)setActions:(const std::vector<std::shared_ptr<BaseActionElement>>&) actions
{
    _menuActions = [[NSMutableArray alloc] init];
    for(auto& action : actions) {
        ACOBaseActionElement *acoElem = [[ACOBaseActionElement alloc] initWithBaseActionElement:action];
        [_menuActions addObject:acoElem];
    }
}

@end
