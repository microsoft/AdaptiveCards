//
//  ACRTableRow.m
//  ACRTableRow
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACRTableRow.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRRegistration.h"
#import "ACRTableCellRenderer.h"
#import "ACRTableCellView.h"
#import "TableRow.h"

@implementation ACRColumnDefinition

- (instancetype)init
{
    self = [super init];
    if (self) {
        _numeric = 0;
        _isValid = YES;
        _isPixelWidth = YES;
    }

    return self;
}

- (instancetype)initWithPixelWidth:(CGFloat)numeric
{
    self = [self init];
    if (self) {
        _numeric = numeric;
    }
    return self;
}

- (instancetype)initWithRelativeWidth:(CGFloat)numeric
                      totalPixelWidth:(CGFloat)totalPixelWidth
{
    self = [self init];
    if (self) {
        _numeric = numeric;
        _totalPixelWidth = totalPixelWidth;
        _isPixelWidth = NO;
    }
    return self;
}

@end

@implementation ACRTableRowView

- (instancetype)init:(ACOBaseCardElement *)acoElem
    columnDefinitions:(NSArray<ACRColumnDefinition *> *)columnDefinition
             rootView:(ACRView *)rootView
               inputs:(NSMutableArray *)inputs
           hostConfig:(ACOHostConfig *)acoConfig
            gridStyle:(ACRContainerStyle)gridStyle
{
    self = [super init];
    if (self) {
        self.translatesAutoresizingMaskIntoConstraints = NO;
        const auto element = [acoElem element];
        const auto row = std::dynamic_pointer_cast<TableRow>(element);
        self.backgroundColor = [acoConfig getBackgroundColorForContainerStyle:(ACRContainerStyle)row->GetStyle()];
        self.spacing = [acoConfig getHostConfig]->GetTable().cellSpacing;
        
        if (!row) {
            return self;
        }

        const auto &cells = row->GetCells();
        const auto endIdx = [columnDefinition count];

        NSLayoutXAxisAnchor *trailingAnchor = self.leadingAnchor;
        UIView *prevView = nil;
        CGFloat lineOffset = 0;
        
        for (auto idx = 0; idx < endIdx; idx++) {
            ACRColumnDefinition *ithColumnDefinition = columnDefinition[idx];
            if (ithColumnDefinition.isValid) {
                ACRTableCellView *cellView = nil;
                if (idx < cells.size()) {
                    auto cell = cells.at(idx);
                    ACRTableCellDefinition *cellDefinition = [[ACRTableCellDefinition alloc] init];
                    auto style = row->GetStyle();
                    if (style == ContainerStyle::None) {
                        style = cell->GetStyle();
                    }
                    cellDefinition.style = (ACRContainerStyle)style;
                    cellDefinition.horizontalAlignment = (ACRHorizontalAlignment)row->GetHorizontalCellContentAlignment().value_or(HorizontalAlignment::Left);
                    cellDefinition.verticalAlignment =
                        (ACRVerticalAlignment)cell->GetVerticalContentAlignment().value_or(row->GetVerticalCellContentAlignment().value_or(VerticalContentAlignment::Top));
                    cellView = [[ACRTableCellView alloc] init:[[ACOBaseCardElement alloc] initWithBaseCardElement:cell]
                                               cellDefinition:cellDefinition
                                                     rootView:rootView
                                                       inputs:inputs
                                                   hostConfig:acoConfig];
                } else {
                    // filler view for empty cells
                    cellView = [[ACRTableCellView alloc] init];
                }
                cellView.translatesAutoresizingMaskIntoConstraints = NO;
                
                if (cellView) {
                    if (ithColumnDefinition.showGridLines) {
                        [self setBorderOnCell:cellView hostConfig:acoConfig style:gridStyle];
                        lineOffset = cellView.layer.borderWidth;
                    }
                    
                    [self addSubview:cellView];
                    if (ithColumnDefinition.isPixelWidth) {
                        [cellView.widthAnchor constraintEqualToConstant:ithColumnDefinition.numeric + lineOffset].active = YES;
                    } else {
                        [cellView.widthAnchor constraintEqualToAnchor:self.widthAnchor
                                                           multiplier:ithColumnDefinition.numeric
                                                             constant:-ithColumnDefinition.totalPixelWidth + lineOffset]
                            .active = YES;
                    }

                    // This constraint with the low priority will ensure
                    // that the shorter cells get minimum heights instead of getting stretched.
                    [self.heightAnchor constraintEqualToAnchor:cellView.heightAnchor].active = YES;
                    NSLayoutConstraint *heightConstraint = [cellView.heightAnchor constraintGreaterThanOrEqualToConstant:0.0];
                    heightConstraint.priority = UILayoutPriorityDefaultLow;
                    heightConstraint.active = YES;
                    
                    [cellView.centerYAnchor constraintEqualToAnchor:self.centerYAnchor].active = YES;
                    if (prevView) {
                        [cellView.leadingAnchor constraintEqualToAnchor:trailingAnchor constant:-lineOffset].active = YES;
                    } else {
                        [cellView.leadingAnchor constraintEqualToAnchor:trailingAnchor].active = YES;
                    }
                    trailingAnchor = cellView.trailingAnchor;
                    prevView = cellView;
                }
            }
        }
    }
    return self;
}

- (void)addArrangedSubview:(UIView *)view
{
    [self addSubview:view];
}

- (CGSize)intrinsicContentSize
{
    CGSize size = CGSizeZero;
    UIView *lastSubView = [self.subviews lastObject];
    for (UIView *subview in self.subviews) {
        if (!subview.isHidden) {
            CGSize intrinsicContentSize = [subview intrinsicContentSize];
            size.width += intrinsicContentSize.width;
            size.height = MAX(size.height, intrinsicContentSize.height);
            if (subview != lastSubView) {
                size.width += self.spacing;
            }
        }
    }

    size.width = (size.width == 0) ? UIViewNoIntrinsicMetric : size.width;
    size.height = (size.height == 0) ? UIViewNoIntrinsicMetric : size.height;
    return size;
}

- (void)setBorderOnCell:(UIView *)cell hostConfig:(ACOHostConfig *)hostConfig style:(ACRContainerStyle)style
{
    if (style != ACRNone) {
        auto config = [hostConfig getHostConfig];
        auto borderColor = config->GetBorderColor([ACOHostConfig getSharedContainerStyle:style]);
        UIColor *color = [ACOHostConfig convertHexColorCodeToUIColor:borderColor];
        cell.layer.borderColor = [color CGColor];
        cell.layer.borderWidth = 1.0;
    }
}

@end
