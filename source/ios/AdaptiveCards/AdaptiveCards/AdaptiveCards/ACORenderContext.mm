//
//  ACORenderContext
//  ACORenderContext.mm
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACORenderContext.h"
#import "ACOAdaptiveCardPrivate.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ActionSet.h"
#import "BaseElement.h"
#import "Column.h"
#import "ColumnSet.h"
#import "Container.h"
#import "Table.h"
#import "TableCell.h"
#import "TableRow.h"
#import "UtiliOS.h"

@implementation ACORenderContext {
    NSMutableDictionary<NSNumber *, NSMutableArray *> *_internalIdContext;
    NSMutableArray<NSNumber *> *_rtlContext;
    NSMutableArray<NSNumber *> *_selectActionContext;
    NSMutableArray<NSNumber *> *_actionIconPlacementContext;
    NSMutableArray<NSNumber *> *_firstRowsAsheadersContext;
}

- (instancetype)init
{
    self = [super init];

    if (self) {
        _internalIdContext = [[NSMutableDictionary alloc] init];
        _rtlContext = [[NSMutableArray alloc] init];
        _selectActionContext = [[NSMutableArray alloc] init];
        _actionIconPlacementContext = [[NSMutableArray alloc] init];
        _firstRowsAsheadersContext = [[NSMutableArray alloc] init];
    }

    return self;
}

- (instancetype)init:(ACOHostConfig *)config
{
    self = [self init];
    if (self) {
        self.hostConfig = config;
    }
    return self;
}

- (ACRRtl)rtl
{
    if (_rtlContext && [_rtlContext count]) {
        NSNumber *number = [_rtlContext lastObject];
        return (ACRRtl)[number intValue];
    }
    return ACRRtlNone;
}

- (BOOL)hasSelectAction
{
    if (_selectActionContext && [_selectActionContext count]) {
        NSNumber *number = [_selectActionContext lastObject];
        return [number boolValue];
    }
    return NO;
}

- (BOOL)allHasActionIcons
{
    if (_actionIconPlacementContext && [_actionIconPlacementContext count]) {
        NSNumber *number = [_actionIconPlacementContext lastObject];
        if (number) {
            return [number boolValue];
        }
    }
    return NO;
}

- (BOOL)isFirstRowAsHeaders
{
    if (_firstRowsAsheadersContext && [_firstRowsAsheadersContext count]) {
        NSNumber *number = [_firstRowsAsheadersContext lastObject];
        if (number) {
            return [number boolValue];
        }
    }
    return NO;
}


- (void)pushBaseActionElementContext:(ACOBaseActionElement *)element
{
    return;
}

- (void)popBaseActionElementContext:(ACOBaseActionElement *)element
{
    return;
}

- (void)addToANewContext:(const std::optional<bool> &)crtl
                     key:(NSNumber *)key
         hasSelectAction:(BOOL)hasSelectAction
           iconPlacement:(NSNumber *)iconPlacement
     isFirstRowAsHeaders:(BOOL)isFirstRowAsHeaders
{
    NSMutableArray<NSMutableArray *> *contexts = [[NSMutableArray alloc] init];
    ACRRtl rtl = ACRRtlNone;
    rtl = getiOSRtl(crtl);
    BOOL shouldPush = NO;
    if (rtl != ACRRtlNone) {
        shouldPush = YES;
        [_rtlContext addObject:[NSNumber numberWithInt:(int)rtl]];
        [contexts addObject:_rtlContext];
    }

    if (hasSelectAction) {
        shouldPush = YES;
        [_selectActionContext addObject:[NSNumber numberWithBool:hasSelectAction]];
        [contexts addObject:_selectActionContext];
    }

    if (iconPlacement) {
        shouldPush = YES;
        [_actionIconPlacementContext addObject:iconPlacement];
        [contexts addObject:_actionIconPlacementContext];
    }

    if (isFirstRowAsHeaders) {
        shouldPush = YES;
        [_firstRowsAsheadersContext addObject:[NSNumber numberWithBool:isFirstRowAsHeaders]];
        [contexts addObject:_firstRowsAsheadersContext];
    }

    if (shouldPush) {
        _internalIdContext[key] = contexts;
    }
}

- (void)pushBaseCardElementContext:(ACOBaseCardElement *)acoElement
{
    [self pushBaseCardElementContext:acoElement additionalProperty:nil];
}

- (void)pushBaseCardElementContext:(ACOBaseCardElement *)acoElement additionalProperty:(NSDictionary * (^)(void))additionalProperty
{
    if (!acoElement || ![acoElement element]) {
        return;
    }

    std::optional<bool> crtl;
    BOOL hasSelectAction = NO;
    BOOL isFirstRowAsHeaders = NO;
    std::shared_ptr<BaseCardElement> element = [acoElement element];
    NSNumber *key = iOSInternalIdHash(element->GetInternalId().Hash());

    if (acoElement.type == ACRTableRow) {
        std::shared_ptr<TableRow> table = std::dynamic_pointer_cast<TableRow>(element);
        if (additionalProperty) {
            id property = additionalProperty();
            if ([property isKindOfClass:[NSDictionary class]]) {
                id heading = ((NSDictionary *)property)[@"heading"];
                if ([heading isKindOfClass:[NSNumber class]]) {
                    isFirstRowAsHeaders = [((NSNumber *)heading) boolValue];
                }
            }
        }
    }

    if (acoElement.type == ACRTableCell) {
        const std::shared_ptr<TableCell> &cell = std::dynamic_pointer_cast<TableCell>(element);
        crtl = cell->GetRtl();
        if (cell->GetSelectAction()) {
            hasSelectAction = YES;
        }
    }

    if (acoElement.type == ACRColumn) {
        std::shared_ptr<Column> column = std::dynamic_pointer_cast<Column>(element);
        crtl = column->GetRtl();
        if (column->GetSelectAction()) {
            hasSelectAction = YES;
        }
    }

    if (acoElement.type == ACRColumnSet) {
        std::shared_ptr<ColumnSet> columnSet = std::dynamic_pointer_cast<ColumnSet>(element);
        if (columnSet->GetSelectAction()) {
            hasSelectAction = YES;
        }
    }

    if (acoElement.type == ACRContainer) {
        std::shared_ptr<Container> container = std::dynamic_pointer_cast<Container>(element);
        crtl = container->GetRtl();
        if (container->GetSelectAction()) {
            hasSelectAction = YES;
        }
    }

    NSNumber *iconPlacement = nil;
    if (acoElement.type == ACRActionSet) {
        iconPlacement = [self.hostConfig getIconPlacement:key];
    }

    std::shared_ptr<BaseElement> baseElement = std::dynamic_pointer_cast<BaseElement>(element);

    [self addToANewContext:crtl
                        key:key
            hasSelectAction:hasSelectAction
              iconPlacement:iconPlacement
        isFirstRowAsHeaders:isFirstRowAsHeaders];
}

- (void)removeContext:(NSNumber *)key
{
    NSMutableArray *contexts = [_internalIdContext objectForKey:key];
    if (contexts) {
        for (NSMutableArray *context in contexts) {
            [context removeLastObject];
        }
        [_internalIdContext removeObjectForKey:key];
    }
}

- (void)popBaseCardElementContext:(ACOBaseCardElement *)element
{
    if (!element || ![element element]) {
        return;
    }

    std::shared_ptr<BaseElement> baseElement = std::dynamic_pointer_cast<BaseElement>([element element]);
    NSNumber *key = [NSNumber numberWithLong:(baseElement->GetInternalId()).Hash()];
    [self removeContext:key];
}

- (void)pushCardContext:(ACOAdaptiveCard *)card
{
    if (!card || ![card card]) {
        return;
    }

    std::shared_ptr<AdaptiveCard> adaptiveCard = [card card];
    auto crtl = adaptiveCard->GetRtl();
    NSNumber *key = [NSNumber numberWithLong:(adaptiveCard->GetInternalId()).Hash()];
    BOOL hasSelectAction = adaptiveCard->GetSelectAction() ? YES : NO;
    NSNumber *iconPlacement = [self.hostConfig getIconPlacement:key];

    [self addToANewContext:crtl
                        key:key
            hasSelectAction:hasSelectAction
              iconPlacement:iconPlacement
        isFirstRowAsHeaders:NO];
}

- (void)popCardContext:(ACOAdaptiveCard *)card
{
    if (!card || ![card card]) {
        return;
    }
    std::shared_ptr<AdaptiveCard> adaptiveCard = [card card];
    NSNumber *key = [NSNumber numberWithLong:(adaptiveCard->GetInternalId()).Hash()];
    [self removeContext:key];
}

@end
