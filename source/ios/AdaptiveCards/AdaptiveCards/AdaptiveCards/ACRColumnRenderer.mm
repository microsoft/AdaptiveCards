//
//  ACRColumnRenderer
//  ACRColumnRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRColumnRenderer.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRColumnSetView.h"
#import "ACRColumnView.h"
#import "ACRRendererPrivate.h"
#import "Column.h"
#import "SharedAdaptiveCard.h"
#import "UtiliOS.h"

@implementation ACRColumnRenderer

+ (ACRColumnRenderer *)getInstance
{
    static ACRColumnRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRColumn;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
           rootView:(ACRView *)rootView
             inputs:(NSMutableArray *)inputs
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<Column> columnElem = std::dynamic_pointer_cast<Column>(elem);

    ACRColumnView *column = [[ACRColumnView alloc] initWithStyle:(ACRContainerStyle)columnElem->GetStyle()
                                                     parentStyle:[viewGroup style]
                                                      hostConfig:acoConfig
                                                       superview:viewGroup];

    [viewGroup addArrangedSubview:column];

    configBleed(rootView, elem, column, acoConfig, viewGroup);

    renderBackgroundImage(columnElem->GetBackgroundImage(), column, rootView);

    column.pixelWidth = columnElem->GetPixelWidth();
    if (columnElem->GetWidth() == "stretch" || columnElem->GetWidth() == "") {
        column.columnWidth = @"stretch";
    } else if (columnElem->GetWidth() == "auto") {
        column.columnWidth = @"auto";
    }

    UIView *leadingBlankSpace = nil, *trailingBlankSpace = nil;
    if (columnElem->GetVerticalContentAlignment() == VerticalContentAlignment::Center || columnElem->GetVerticalContentAlignment() == VerticalContentAlignment::Bottom) {
        leadingBlankSpace = [column addPaddingSpace];
    }

    ACRColumnSetView *columnsetView = (ACRColumnSetView *)viewGroup;
    column.isLastColumn = columnsetView.isLastColumn;

    [ACRRenderer render:column
               rootView:rootView
                 inputs:inputs
          withCardElems:columnElem->GetItems()
          andHostConfig:acoConfig];

    if (columnElem->GetVerticalContentAlignment() == VerticalContentAlignment::Center || (columnElem->GetVerticalContentAlignment() == VerticalContentAlignment::Top && _fillAlignment)) {
        trailingBlankSpace = [column addPaddingSpace];
    }
    
    if (leadingBlankSpace || trailingBlankSpace) {
        column.hasStretchableView = YES;
    }
    
    if (!column.hasStretchableView) {
        [column addPaddingSpace];
    }

    if (columnElem->GetMinHeight() > 0) {
        [NSLayoutConstraint constraintWithItem:column
                                     attribute:NSLayoutAttributeHeight
                                     relatedBy:NSLayoutRelationGreaterThanOrEqual
                                        toItem:nil
                                     attribute:NSLayoutAttributeNotAnAttribute
                                    multiplier:1
                                      constant:columnElem->GetMinHeight()]
            .active = YES;
    }

    [column setClipsToBounds:NO];

    std::shared_ptr<BaseActionElement> selectAction = columnElem->GetSelectAction();
    ACOBaseActionElement *acoSelectAction = [ACOBaseActionElement getACOActionElementFromAdaptiveElement:selectAction];

    [column configureForSelectAction:acoSelectAction rootView:rootView];

    column.shouldGroupAccessibilityChildren = YES;

    if (leadingBlankSpace != nil && trailingBlankSpace != nil) {
        [NSLayoutConstraint constraintWithItem:leadingBlankSpace
                                     attribute:NSLayoutAttributeHeight
                                     relatedBy:NSLayoutRelationEqual
                                        toItem:trailingBlankSpace
                                     attribute:NSLayoutAttributeHeight
                                    multiplier:1.0
                                      constant:0]
            .active = YES;
    }

    configVisibility(column, elem);

    [column hideIfSubviewsAreAllHidden];

    return column;
}

- (void)configUpdateForUIImageView:(ACOBaseCardElement *)acoElem config:(ACOHostConfig *)acoConfig image:(UIImage *)image imageView:(UIImageView *)imageView
{
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<Column> columnElem = std::dynamic_pointer_cast<Column>(elem);
    auto backgroundImageProperties = columnElem->GetBackgroundImage();

    renderBackgroundImage(backgroundImageProperties.get(), imageView, image);
}

@end
