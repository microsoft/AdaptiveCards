//
//  ACOActionOverflow
//  ACOActionOverflow.m
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACOActionOverflow.h"
#import "ACOAdaptiveCardPrivate.h"
#import "ACOBaseActionElementPrivate.h"
#import "BaseActionElement.h"
#import <Foundation/Foundation.h>

using namespace AdaptiveCards;

@implementation ACOActionOverflow {
    NSMutableArray<ACOBaseActionElement *> *_menuActions;
}

- (instancetype)init
{
    return [self initWithBaseActionElements:{} atCard:nil];
}

- (instancetype)initWithBaseActionElements:(const std::vector<std::shared_ptr<BaseActionElement>> &)elements
                                    atCard:(ACOAdaptiveCard *)card
{
    auto fakeElem = std::make_shared<BaseActionElement>(ActionType::Overflow);
    self = [super initWithBaseActionElement:fakeElem];
    if (self) {
        super.type = ACRActionType::ACROverflow;
        [self setActions:elements];
        _isAtRootLevel = [self updateIsAtRootLevel:card];
    }
    return self;
}

- (NSArray<ACOBaseActionElement *> *)menuActions
{
    return _menuActions;
}

- (void)setMenuActions:(NSArray *)menuActions
{
    _menuActions = [menuActions mutableCopy];
}

- (void)setActions:(const std::vector<std::shared_ptr<BaseActionElement>> &)actions
{
    _menuActions = [[NSMutableArray alloc] init];
    for (auto &action : actions) {
        ACOBaseActionElement *acoElem = [ACOBaseActionElement getACOActionElementFromAdaptiveElement:action];
        [_menuActions addObject:acoElem];
    }
}

- (BOOL)updateIsAtRootLevel:(ACOAdaptiveCard *)card
{
    auto &rootActions = card.card->GetActions();
    for (ACOBaseActionElement *action in self.menuActions) {
        auto it = std::find(std::begin(rootActions),
                            std::end(rootActions),
                            action.element);
        if (it != std::end(rootActions)) {
            return YES;
        }
    }
    return NO;
}

@end
