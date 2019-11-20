//
//  ACRColumnSetRenderer
//  ACRColumnSetRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRColumnSetRenderer.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRColumnRenderer.h"
#import "ACRColumnSetView.h"
#import "ACRLongPressGestureRecognizerFactory.h"
#import "ACRRegistration.h"
#import "ACRSeparator.h"
#import "ACRView.h"
#import "Column.h"
#import "ColumnSet.h"
#import "Enums.h"
#import "SharedAdaptiveCard.h"
#import "UtiliOS.h"

@implementation ACRColumnSetRenderer

+ (ACRColumnSetRenderer *)getInstance
{
    static ACRColumnSetRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRColumnSet;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
           rootView:(ACRView *)rootView
             inputs:(NSMutableArray *)inputs
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<ColumnSet> columnSetElem = std::dynamic_pointer_cast<ColumnSet>(elem);

    ACRColumnSetView *columnSetView = [[ACRColumnSetView alloc] initWithStyle:(ACRContainerStyle)columnSetElem->GetStyle()
                                                                  parentStyle:[viewGroup style]
                                                                   hostConfig:acoConfig
                                                                    superview:viewGroup];
    [viewGroup addArrangedSubview:columnSetView];

    configBleed(rootView, elem, columnSetView, acoConfig);

    [columnSetView setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];

    ACRBaseCardElementRenderer *columnRenderer =
        [[ACRRegistration getInstance] getRenderer:[NSNumber numberWithInt:(int)CardElementType::Column]];
    std::vector<std::shared_ptr<Column>> columns = columnSetElem->GetColumns();

    ACRColumnView *prevView = nil, *curView = nil, *stretchView = nil;
    float relativeColumnWidth = 0, prevRelColumnWidth = 0;
    float multiplier = 1.0;
    NSMutableArray *constraints = [[NSMutableArray alloc] init];

    if (columnSetElem->GetMinHeight() > 0) {
        [constraints addObject:
                         [NSLayoutConstraint constraintWithItem:columnSetView
                                                      attribute:NSLayoutAttributeHeight
                                                      relatedBy:NSLayoutRelationGreaterThanOrEqual
                                                         toItem:nil
                                                      attribute:NSLayoutAttributeNotAnAttribute
                                                     multiplier:1
                                                       constant:columnSetElem->GetMinHeight()]];
    }

    ACRColumnRenderer *castedRenderer = (ACRColumnRenderer *)columnRenderer;
    for (std::shared_ptr<Column> column : columns) {
        if (column->GetVerticalContentAlignment() != VerticalContentAlignment::Top) {
            castedRenderer.fillAlignment = YES;
        }
    }

    ACOBaseCardElement *acoColumn = [[ACOBaseCardElement alloc] init];
    auto firstColumn = columns.begin();
    auto prevColumn = columns.empty() ? nullptr : *firstColumn;
    auto lastColumn = columns.empty() ? nullptr : columns.back();
    ACOFeatureRegistration *featureReg = [ACOFeatureRegistration getInstance];
    ACRSeparator *separator = nil;

    for (std::shared_ptr<Column> column : columns) {
        if (*firstColumn != column) {
            separator = [ACRSeparator renderSeparation:column forSuperview:columnSetView withHostConfig:config];
            configSeparatorVisibility(separator, prevColumn);
        }

        [acoColumn setElem:column];

        @try {
            if ([acoElem meetsRequirements:featureReg] == NO) {
                @throw [ACOFallbackException fallbackException];
            }

            if (lastColumn == column) {
                columnSetView.isLastColumn = YES;
            }

            curView = (ACRColumnView *)[columnRenderer render:columnSetView rootView:rootView inputs:inputs baseCardElement:acoColumn hostConfig:acoConfig];
        } @catch (ACOFallbackException *e) {

            handleFallbackException(e, columnSetView, rootView, inputs, column, acoConfig);

            if (separator) {
                [columnSetView removeViewFromContentStackView:separator];
            }

            UIView *fallbackView = [columnSetView getLastSubview];
            if ([fallbackView isKindOfClass:[ACRColumnView class]]) {
                curView = (ACRColumnView *)fallbackView;
            } else {
                // the view added wasn't column view, remove and drop it.
                [columnSetView removeViewFromContentStackView:curView];
                curView = prevView;
            }
        }

        // when stretch, views with stretch properties should have equal width
        if (curView.pixelWidth) {
            [constraints addObject:
                             [NSLayoutConstraint constraintWithItem:curView
                                                          attribute:NSLayoutAttributeWidth
                                                          relatedBy:NSLayoutRelationEqual
                                                             toItem:nil
                                                          attribute:NSLayoutAttributeNotAnAttribute
                                                         multiplier:1
                                                           constant:curView.pixelWidth]];
        } else if ([curView.columnWidth isEqualToString:@"stretch"]) {
            if (stretchView) {
                [constraints addObject:
                                 [NSLayoutConstraint constraintWithItem:curView
                                                              attribute:NSLayoutAttributeWidth
                                                              relatedBy:NSLayoutRelationEqual
                                                                 toItem:stretchView
                                                              attribute:NSLayoutAttributeWidth
                                                             multiplier:1
                                                               constant:0]];
            }
            stretchView = curView;
        } else if (![curView.columnWidth isEqualToString:@"auto"]) {
            try {
                relativeColumnWidth = std::stof(column->GetWidth());
                if (prevRelColumnWidth) {
                    multiplier = relativeColumnWidth / prevRelColumnWidth;
                }

                if (prevView && prevRelColumnWidth) {
                    [constraints addObject:
                                     [NSLayoutConstraint constraintWithItem:curView
                                                                  attribute:NSLayoutAttributeWidth
                                                                  relatedBy:NSLayoutRelationEqual
                                                                     toItem:prevView
                                                                  attribute:NSLayoutAttributeWidth
                                                                 multiplier:multiplier
                                                                   constant:0]];
                    prevRelColumnWidth = relativeColumnWidth;
                }

                prevView = curView;
                prevRelColumnWidth = relativeColumnWidth;
            } catch (...) {
                multiplier = 1;
                relativeColumnWidth = 1;
                NSLog(@"unexpected column width property is given");
            }
        }

        if (curView.hasStretchableView || (columnSetElem->GetHeight() == HeightType::Stretch)) {
            [columnSetView setAlignmentForColumnStretch];
        }

        prevColumn = column;
    }

    castedRenderer.fillAlignment = NO;

    if ([constraints count]) {
        [NSLayoutConstraint activateConstraints:constraints];
    }

    std::shared_ptr<BaseActionElement> selectAction = columnSetElem->GetSelectAction();
    // instantiate and add long press gesture recognizer
    [ACRLongPressGestureRecognizerFactory addLongPressGestureRecognizerToUIView:viewGroup
                                                                       rootView:rootView
                                                                  recipientView:columnSetView
                                                                  actionElement:selectAction
                                                                     hostConfig:acoConfig];
    configVisibility(columnSetView, elem);

    return columnSetView;
}

@end
