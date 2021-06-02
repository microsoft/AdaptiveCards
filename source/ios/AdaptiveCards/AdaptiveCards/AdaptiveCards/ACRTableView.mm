//
//  ACRTableView.m
//  ACRTableView
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACRTableView.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRTableRow.h"
#import "Table.h"
#import "TableCell.h"
#import "TableColumnDefinition.h"
#import "TableRow.h"

@implementation ACRTableView {
    NSMutableArray<ACRColumnDefinition *> *_columnDefinitions;
}

- (instancetype)init:(ACOBaseCardElement *)acoElement
           viewGroup:(UIView<ACRIContentHoldingView> *)viewGroup
            rootView:(ACRView *)rootView
              inputs:(NSMutableArray *)inputs
          hostConfig:(ACOHostConfig *)acoConfig;
{
    self = [super init];
    if (self) {
        std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
        std::shared_ptr<Table> table = std::dynamic_pointer_cast<Table>([acoElement element]);
        [viewGroup addArrangedSubview:self];
        _columnDefinitions = [[NSMutableArray alloc] init];
        _showGridLines = table->GetShowGridLines();
        _gridStyle = [viewGroup style];
        if (const auto style = table->GetGridStyle(); style != ContainerStyle::None) {
            _gridStyle = (ACRContainerStyle)style;
        }
        [self defineColumnDefinitions:table];
        [self buildRowView:table rootView:rootView inputs:inputs hostConfig:acoConfig];
    }
    return self;
}

- (void)defineColumnDefinitions:(const std::shared_ptr<Table> &)table
{
    CGFloat totalPixelWidth = 0, minWidth = CGFLOAT_MAX;
    for (const auto &columnDefinition : table->GetColumns()) {
        auto optionalNumericValue = columnDefinition->GetWidth();
        if (optionalNumericValue.has_value()) {
            minWidth = MIN(minWidth, *optionalNumericValue);
        } else if (auto optionalPixelValue = columnDefinition->GetPixelWidth(); optionalPixelValue.has_value()) {
            totalPixelWidth += *optionalPixelValue;
        }
    }

    // if minWidth width is zero, dividend will be zero, and setting the value to 1
    // ensures the relative width come out as zero
    minWidth = (minWidth == 0) ? 1 : minWidth;

    for (auto columnDefinition : table->GetColumns()) {
        auto optionalNumericValue = columnDefinition->GetWidth();
        ACRColumnDefinition *iOSColumnDefinition = nil;
        if (optionalNumericValue.has_value()) {
            iOSColumnDefinition = [[ACRColumnDefinition alloc] initWithRelativeWidth:*optionalNumericValue / minWidth
                                                                     totalPixelWidth:totalPixelWidth];
        } else if (auto optionalPixelValue = columnDefinition->GetPixelWidth(); optionalPixelValue.has_value()) {
            iOSColumnDefinition = [[ACRColumnDefinition alloc] initWithPixelWidth:*optionalPixelValue];
        } else {
            iOSColumnDefinition = [[ACRColumnDefinition alloc] init];
            iOSColumnDefinition.isValid = NO;
        }

        if (columnDefinition) {
            iOSColumnDefinition.showGridLines = self.showGridLines;
            [_columnDefinitions addObject:iOSColumnDefinition];
        }
    }
}

- (void)buildRowView:(const std::shared_ptr<Table> &)table
            rootView:(ACRView *)rootView
              inputs:(NSMutableArray *)inputs
          hostConfig:(ACOHostConfig *)acoConfig;
{
    ACOBaseCardElement *acoRowWrapper = [[ACOBaseCardElement alloc] init];
    NSLayoutYAxisAnchor *nextTopAnchor = self.topAnchor;
    ACRTableRowView *rowView = nil;
    NSDictionary * (^additionalProperties)(void);
    self.spacing = [acoConfig getHostConfig]->GetTable().cellSpacing;
    CGFloat spacing = 0.0f;
    auto i = 0;
    for (const auto &row : table->GetRows()) {
        [acoRowWrapper setElem:row];

        if (i == 0 && table->GetFirstRowAsHeaders()) {
            additionalProperties = ^NSDictionary *(void)
            {
                return @{@"heading" : @YES};
            };
        }
        [rootView.context pushBaseCardElementContext:acoRowWrapper additionalProperty:additionalProperties];
        rowView = [[ACRTableRowView alloc] init:acoRowWrapper
                              columnDefinitions:_columnDefinitions
                                       rootView:rootView
                                         inputs:inputs
                                     hostConfig:acoConfig
                                      gridStyle:_gridStyle];
        additionalProperties = nil;
        [self addSubview:rowView];
        [self.widthAnchor constraintEqualToAnchor:rowView.widthAnchor].active = YES;
        CGFloat offset = self.showGridLines ? 1 : 0;

        [nextTopAnchor constraintEqualToAnchor:rowView.topAnchor constant:offset - spacing].active = YES;
        nextTopAnchor = rowView.bottomAnchor;
        spacing = self.spacing;
        [rootView.context popBaseCardElementContext:acoRowWrapper];
        i++;
    }

    if (rowView) {
        [self.bottomAnchor constraintEqualToAnchor:rowView.bottomAnchor].active = YES;
    }
}

- (CGSize)intrinsicContentSize
{
    CGSize size = CGSizeZero;
    UIView *lastSubView = [self.subviews lastObject];
    for (UIView *subview in self.subviews) {
        if (!subview.isHidden) {
            CGSize intrinsicContentSize = [subview intrinsicContentSize];
            size.height += intrinsicContentSize.height;
            size.width = MAX(size.width, intrinsicContentSize.width);
            if (subview != lastSubView) {
                size.height += self.spacing;
            }
        }
    }

    size.width = (size.width == 0) ? UIViewNoIntrinsicMetric : size.width;
    size.height = (size.height == 0) ? UIViewNoIntrinsicMetric : size.height;
    return size;
}

@end
