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
        [self defineColumnDefinitions:table];
        [self buildRowView:table rootView:rootView inputs:inputs hostConfig:acoConfig];
    }
    return self;
}

- (void)defineColumnDefinitions:(const std::shared_ptr<Table> &)table
{
    CGFloat totalRelativeWidth = 0, totalPixelWidth = 0;
    for (const auto &columnDefinition : table->GetColumns()) {
        auto optionalNumericValue = columnDefinition->GetWidth();
        if (optionalNumericValue.has_value()) {
            totalRelativeWidth += *optionalNumericValue;
        } else if (auto optionalPixelValue = columnDefinition->GetWidth(); optionalPixelValue.has_value()) {
            totalPixelWidth += *optionalPixelValue;
        }
    }

    // if total relative width is zero, dividend will be zero, and setting the value to 1
    // ensures the relative width come out as zero
    totalRelativeWidth = (totalRelativeWidth == 0) ? 1 : totalRelativeWidth;

    for (auto columnDefinition : table->GetColumns()) {
        auto optionalNumericValue = columnDefinition->GetWidth();
        if (optionalNumericValue.has_value()) {
            [_columnDefinitions addObject:[[ACRColumnDefinition alloc] initWithRelativeWidth:*optionalNumericValue / totalRelativeWidth
                                                                             totalPixelWidth:totalPixelWidth]];
        } else if (auto optionalPixelValue = columnDefinition->GetPixelWidth(); optionalPixelValue.has_value()) {
            [_columnDefinitions addObject:[[ACRColumnDefinition alloc] initWithPixelWidth:*optionalPixelValue]];
        } else {
            ACRColumnDefinition *invalidColumnDefintion = [[ACRColumnDefinition alloc] init];
            invalidColumnDefintion.isValid = NO;
            [_columnDefinitions addObject:invalidColumnDefintion];
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
    for (const auto &row : table->GetRows()) {
        [acoRowWrapper setElem:row];
        rowView = [[ACRTableRowView alloc] init:acoRowWrapper
                              columnDefinitions:_columnDefinitions
                                       rootView:rootView
                                         inputs:inputs
                                     hostConfig:acoConfig];
        [self addSubview:rowView];
        [self.widthAnchor constraintEqualToAnchor:rowView.widthAnchor].active = YES;
        [nextTopAnchor constraintEqualToAnchor:rowView.topAnchor].active = YES;
        nextTopAnchor = rowView.bottomAnchor;
    }

    if (rowView) {
        [self.bottomAnchor constraintEqualToAnchor:rowView.bottomAnchor].active = YES;
    }
}

- (CGSize)intrinsicContentSize
{
    CGSize size = CGSizeZero;
    for (UIView *subview in self.subviews) {
        if (!subview.isHidden) {
            CGSize intrinsicContentSize = [subview intrinsicContentSize];
            size.height += intrinsicContentSize.height;
            size.width = MAX(size.width, intrinsicContentSize.width);
        }
    }

    size.width = (size.width == 0) ? UIViewNoIntrinsicMetric : size.width;
    size.height = (size.height == 0) ? UIViewNoIntrinsicMetric : size.height;
    return size;
}

@end
