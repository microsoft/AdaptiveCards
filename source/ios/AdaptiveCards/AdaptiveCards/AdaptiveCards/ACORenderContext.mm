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


@interface ACOContextProperties : NSObject
@property std::optional<bool> crtl;
@property std::optional<HorizontalAlignment> horizontalAlignment;
@property std::optional<VerticalContentAlignment> verticalAlignment;
@property NSNumber *key;
@property NSNumber *iconPlacement;
@property BOOL hasSelectAction;
@property BOOL isFirstRowAsHeaders;
@property ContainerStyle style;
@end

@implementation ACOContextProperties
@end

@implementation ACORenderContext {
    NSMutableDictionary<NSNumber *, NSMutableArray *> *_internalIdContext;
    NSMutableArray<NSNumber *> *_rtlContext;
    NSMutableArray<NSNumber *> *_selectActionContext;
    NSMutableArray<NSNumber *> *_actionIconPlacementContext;
    NSMutableArray<NSNumber *> *_firstRowsAsheadersContext;
    NSMutableArray<NSNumber *> *_verticalAlignmentContext;
    NSMutableArray<NSNumber *> *_horizontalAlignmentContext;
    NSMutableArray<NSNumber *> *_styleContext;
    NSMapTable<NSNumber *, NSObject<ACOIVisibilityManagerFacade> *> *_visibilityMap;
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
        _verticalAlignmentContext = [[NSMutableArray alloc] init];
        _horizontalAlignmentContext = [[NSMutableArray alloc] init];
        _styleContext = [[NSMutableArray alloc] init];
        _visibilityMap = [NSMapTable mapTableWithKeyOptions:NSMapTableStrongMemory valueOptions:NSMapTableWeakMemory];
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

- (ACRVerticalContentAlignment)verticalContentAlignment
{
    if (_verticalAlignmentContext && [_verticalAlignmentContext count]) {
        NSNumber *number = [_verticalAlignmentContext lastObject];
        if (number) {
            return (ACRVerticalContentAlignment)[number intValue];
        }
    }
    return ACRVerticalContentAlignmentTop;
}

- (ACRHorizontalAlignment)horizontalContentAlignment
{
    if (_horizontalAlignmentContext && [_horizontalAlignmentContext count]) {
        NSNumber *number = [_horizontalAlignmentContext lastObject];
        if (number) {
            return (ACRHorizontalAlignment)[number intValue];
        }
    }
    return ACRLeft;
}

- (ACRContainerStyle)style
{
    if (_styleContext && [_styleContext count]) {
        NSNumber *number = [_styleContext lastObject];
        if (number) {
            return (ACRContainerStyle)[number intValue];
        }
    }
    return ACRNone;
}

- (void)pushBaseActionElementContext:(ACOBaseActionElement *)element
{
    return;
}

- (void)popBaseActionElementContext:(ACOBaseActionElement *)element
{
    return;
}

- (void)addToANewContext:(ACOContextProperties *)properties key:(NSNumber *)key
{
    NSMutableArray<NSMutableArray *> *contexts = [[NSMutableArray alloc] init];
    ACRRtl rtl = ACRRtlNone;
    rtl = getiOSRtl(properties.crtl);
    BOOL shouldPush = NO;
    if (rtl != ACRRtlNone) {
        shouldPush = YES;
        [_rtlContext addObject:[NSNumber numberWithInt:(int)rtl]];
        [contexts addObject:_rtlContext];
    }

    if (properties.hasSelectAction) {
        shouldPush = YES;
        [_selectActionContext addObject:[NSNumber numberWithBool:properties.hasSelectAction]];
        [contexts addObject:_selectActionContext];
    }

    if (properties.iconPlacement) {
        shouldPush = YES;
        [_actionIconPlacementContext addObject:properties.iconPlacement];
        [contexts addObject:_actionIconPlacementContext];
    }

    if (properties.isFirstRowAsHeaders) {
        shouldPush = YES;
        [_firstRowsAsheadersContext addObject:[NSNumber numberWithBool:properties.isFirstRowAsHeaders]];
        [contexts addObject:_firstRowsAsheadersContext];
    }

    if (properties.horizontalAlignment.has_value()) {
        shouldPush = YES;
        [_horizontalAlignmentContext addObject:[NSNumber numberWithInt:(int)(*properties.horizontalAlignment)]];
        [contexts addObject:_horizontalAlignmentContext];
    }

    if (properties.verticalAlignment.has_value()) {
        shouldPush = YES;
        [_verticalAlignmentContext addObject:[NSNumber numberWithInt:(int)(*properties.verticalAlignment)]];
        [contexts addObject:_verticalAlignmentContext];
    }
    
    if (properties.style != ContainerStyle::None) {
        shouldPush = YES;
        [_styleContext addObject:[NSNumber numberWithInt:(int)(properties.style)]];
        [contexts addObject:_styleContext];
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

    ACOContextProperties *properties = [[ACOContextProperties alloc] init];
    std::shared_ptr<BaseCardElement> element = [acoElement element];
    NSNumber *key = iOSInternalIdHash(element->GetInternalId().Hash());

    if (acoElement.type == ACRTable) {
        std::shared_ptr<Table> table = std::dynamic_pointer_cast<Table>(element);
        if (table) {
            properties.horizontalAlignment = table->GetHorizontalCellContentAlignment();
            properties.verticalAlignment = table->GetVerticalCellContentAlignment();
            properties.style = table->GetGridStyle();
        }
    }

    if (acoElement.type == ACRTableRow) {
        std::shared_ptr<TableRow> row = std::dynamic_pointer_cast<TableRow>(element);
        if (additionalProperty) {
            id property = additionalProperty();
            if ([property isKindOfClass:[NSDictionary class]]) {
                id heading = ((NSDictionary *)property)[@"heading"];
                if ([heading isKindOfClass:[NSNumber class]]) {
                    properties.isFirstRowAsHeaders = [((NSNumber *)heading) boolValue];
                }
            }
        }

        if (row) {
            properties.horizontalAlignment = row->GetHorizontalCellContentAlignment();
            properties.verticalAlignment = row->GetVerticalCellContentAlignment();
            properties.style = row->GetStyle();
        }
    }

    if (acoElement.type == ACRTableCell) {
        const std::shared_ptr<TableCell> &cell = std::dynamic_pointer_cast<TableCell>(element);
        properties.crtl = cell->GetRtl();
        if (cell) {
            if (cell->GetSelectAction()) {
                properties.hasSelectAction = YES;
            }
            
            properties.verticalAlignment = cell->GetVerticalContentAlignment();
            properties.style = cell->GetStyle();
        }
    }

    if (acoElement.type == ACRColumn) {
        std::shared_ptr<Column> column = std::dynamic_pointer_cast<Column>(element);
        properties.crtl = column->GetRtl();
        if (column->GetSelectAction()) {
            properties.hasSelectAction = YES;
        }
    }

    if (acoElement.type == ACRColumnSet) {
        std::shared_ptr<ColumnSet> columnSet = std::dynamic_pointer_cast<ColumnSet>(element);
        if (columnSet->GetSelectAction()) {
            properties.hasSelectAction = YES;
        }
    }

    if (acoElement.type == ACRContainer) {
        std::shared_ptr<Container> container = std::dynamic_pointer_cast<Container>(element);
        properties.crtl = container->GetRtl();
        if (container->GetSelectAction()) {
            properties.hasSelectAction = YES;
        }
    }

    if (acoElement.type == ACRActionSet) {
        properties.iconPlacement = [self.hostConfig getIconPlacement:key];
    }

    std::shared_ptr<BaseElement> baseElement = std::dynamic_pointer_cast<BaseElement>(element);

    [self addToANewContext:properties key:key];
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
    NSNumber *key = [NSNumber numberWithLong:(adaptiveCard->GetInternalId()).Hash()];
    ACOContextProperties *properties = [[ACOContextProperties alloc] init];
    properties.crtl = adaptiveCard->GetRtl();
    properties.hasSelectAction = adaptiveCard->GetSelectAction() ? YES : NO;
    properties.iconPlacement = [self.hostConfig getIconPlacement:key];
    [self addToANewContext:properties
                       key:key];
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

- (void)registerVisibilityManager:(NSObject<ACOIVisibilityManagerFacade> *)manager targetViewTag:(NSUInteger)viewTag
{
    if (manager) {
        [_visibilityMap setObject:manager forKey:[NSNumber numberWithLong:viewTag]];
    }
}

- (NSObject<ACOIVisibilityManagerFacade> *)retrieveVisiblityManagerWithTag:(NSUInteger)viewTag
{
    return [_visibilityMap objectForKey:[NSNumber numberWithLong:viewTag]];
}

@end
