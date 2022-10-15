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
#import "UtiliOS.h"

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

        if (!row) {
            return self;
        }

        self.spacing = [acoConfig getHostConfig]->GetTable().cellSpacing;
        const auto &cells = row->GetCells();
        const auto endIdx = [columnDefinition count];

        NSLayoutXAxisAnchor *trailingAnchor = self.leadingAnchor;
        UIView *prevView = nil;
        CGFloat spacing = self.spacing, lineOffset = 0.0f;
        NSMutableDictionary<NSNumber *, NSNumber *> *viewToRelativeSize = [[NSMutableDictionary alloc] init];
        NSMutableArray<UIView *> *viewsWithRelativeWidth = [[NSMutableArray alloc] init];

        configBleed(rootView, element, self, acoConfig);

        for (auto idx = 0; idx < endIdx; idx++) {
            ACRColumnDefinition *ithColumnDefinition = columnDefinition[idx];
            if (ithColumnDefinition.isValid) {
                ACRTableCellView *cellView = nil;
                if (idx < cells.size()) {
                    auto cell = cells.at(idx);
                    ACOBaseCardElement *cellElement = [[ACOBaseCardElement alloc] initWithBaseCardElement:cell];
                    cell->SetParentalId(row->GetInternalId());
                    [rootView.context pushBaseCardElementContext:cellElement];

                    ACRTableCellDefinition *cellDefinition = [[ACRTableCellDefinition alloc] init];
                    cellDefinition.style = rootView.context.style;
                    cellDefinition.horizontalAlignment = rootView.context.horizontalContentAlignment;
                    cellDefinition.verticalAlignment = rootView.context.verticalContentAlignment;
                    cellDefinition.cellSpacing = (ithColumnDefinition.showGridLines) || (cell->GetStyle() != ContainerStyle::None) ? [acoConfig getHostConfig]->GetSpacing().paddingSpacing : self.spacing;

                    cellView = [[ACRTableCellView alloc] init:cellElement
                                               cellDefinition:cellDefinition
                                                     rootView:rootView
                                                       inputs:inputs
                                                   hostConfig:acoConfig];
                    [[ACRTableCellRenderer getInstance] render:cellView rootView:rootView inputs:inputs baseCardElement:cellElement hostConfig:acoConfig];
                    [rootView.context popBaseCardElementContext:cellElement];
                } else {
                    // filler view for empty cells
                    cellView = [[ACRTableCellView alloc] init];
                }
                cellView.translatesAutoresizingMaskIntoConstraints = NO;

                if (cellView) {
                    if (ithColumnDefinition.showGridLines) {
                        [self setBorderOnCell:cellView hostConfig:acoConfig style:gridStyle];
                        lineOffset = cellView.layer.borderWidth;
                        spacing = 0;
                    }

                    [self addSubview:cellView];

                    if (idx < cells.size()) {
                        configBleed(rootView, cells.at(idx), cellView, acoConfig);
                    }

                    if (ithColumnDefinition.isPixelWidth) {
                        [cellView.widthAnchor constraintEqualToConstant:ithColumnDefinition.numeric + lineOffset].active = YES;
                    } else {
                        // collect cells with relative width, and build map it with its relative width for
                        // comparison later
                        [viewsWithRelativeWidth addObject:cellView];
                        [viewToRelativeSize setObject:[NSNumber numberWithFloat:ithColumnDefinition.numeric]
                                               forKey:[NSNumber numberWithLong:cellView.hash]];
                    }

                    // This constraint with the low priority will ensure
                    // that the shorter cells get minimum heights instead of getting stretched.
                    [self.heightAnchor constraintEqualToAnchor:cellView.heightAnchor].active = YES;
                    NSLayoutConstraint *heightConstraint = [cellView.heightAnchor constraintGreaterThanOrEqualToConstant:0.0];
                    heightConstraint.priority = UILayoutPriorityDefaultLow;
                    heightConstraint.active = YES;

                    [cellView.centerYAnchor constraintEqualToAnchor:self.centerYAnchor].active = YES;
                    if (prevView) {
                        [cellView.leadingAnchor constraintEqualToAnchor:trailingAnchor constant:spacing - lineOffset].active = YES;
                    } else {
                        [cellView.leadingAnchor constraintEqualToAnchor:trailingAnchor].active = YES;
                    }

                    trailingAnchor = cellView.trailingAnchor;
                    prevView = cellView;
                }
            }
        }

        if (prevView) {
            [prevView.trailingAnchor constraintEqualToAnchor:self.trailingAnchor].active = YES;
        }

        // sort the views with relative width
        NSArray *sortedArray = [viewsWithRelativeWidth sortedArrayUsingComparator:^NSComparisonResult(id a, id b) {
            // retrieve the width from the map
            NSNumber *sizeA = viewToRelativeSize[[NSNumber numberWithLong:((UIView *)a).hash]];
            NSNumber *sizeB = viewToRelativeSize[[NSNumber numberWithLong:((UIView *)b).hash]];
            return [sizeA compare:sizeB];
        }];

        if (sortedArray && [sortedArray count]) {
            UIView *baseView = sortedArray[0];
            // set width constraint to a given view relative to the base view that has the minimum width
            for (UIView *view in sortedArray) {
                if (view != baseView) {
                    [view.widthAnchor constraintEqualToAnchor:baseView.widthAnchor
                                                   multiplier:[viewToRelativeSize[[NSNumber numberWithLong:view.hash]] floatValue]
                                                     constant:lineOffset]
                        .active = YES;
                }
            }
        }
    }
    return self;
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
