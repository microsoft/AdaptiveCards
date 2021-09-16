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

    [rootView.context pushBaseCardElementContext:acoElem];

    ACRColumnView *column = [[ACRColumnView alloc] initWithStyle:(ACRContainerStyle)columnElem->GetStyle()
                                                     parentStyle:[viewGroup style]
                                                      hostConfig:acoConfig
                                                       superview:viewGroup];

    column.rtl = rootView.context.rtl;

    column.pixelWidth = columnElem->GetPixelWidth();
    auto width = columnElem->GetWidth();
    if (width.empty() || width == "stretch") {
        column.columnWidth = @"stretch";
    } else if (width == "auto") {
        column.columnWidth = @"auto";
    } else {
        try {
            column.relativeWidth = std::stof(width);
            column.hasMoreThanOneRelativeWidth = ((ACRColumnSetView *)viewGroup).hasMoreThanOneColumnWithRelatvieWidth;
        } catch (...) {
            [rootView addWarnings:ACRInvalidValue mesage:@"Invalid column width is given"];
            column.columnWidth = @"stretch";
        }
    }

    ACRColumnSetView *columnsetView = (ACRColumnSetView *)viewGroup;
    column.isLastColumn = columnsetView.isLastColumn;
    column.columnsetView = columnsetView;

    [ACRRenderer render:column
               rootView:rootView
                 inputs:inputs
          withCardElems:columnElem->GetItems()
          andHostConfig:acoConfig];

    [column configureLayoutAndVisibility:GetACRVerticalContentAlignment(columnElem->GetVerticalContentAlignment().value_or(VerticalContentAlignment::Top))
                               minHeight:columnElem->GetMinHeight()
                              heightType:GetACRHeight(columnElem->GetHeight())
                                    type:ACRColumn];

    [column setClipsToBounds:NO];

    std::shared_ptr<BaseActionElement> selectAction = columnElem->GetSelectAction();
    ACOBaseActionElement *acoSelectAction = [ACOBaseActionElement getACOActionElementFromAdaptiveElement:selectAction];

    [column configureForSelectAction:acoSelectAction rootView:rootView];

    column.shouldGroupAccessibilityChildren = YES;

    [viewGroup addArrangedSubview:column];

    // viewGroup and column has to be in view hierarchy before configBleed is called
    configBleed(rootView, elem, column, acoConfig, viewGroup);

    renderBackgroundImage(columnElem->GetBackgroundImage(), column, rootView);

    [rootView.context popBaseCardElementContext:acoElem];

    column.accessibilityElements = [column getArrangedSubviews];

    return column;
}

- (void)configUpdateForUIImageView:(ACRView *)rootView acoElem:(ACOBaseCardElement *)acoElem config:(ACOHostConfig *)acoConfig image:(UIImage *)image imageView:(UIImageView *)imageView
{
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<Column> columnElem = std::dynamic_pointer_cast<Column>(elem);
    auto backgroundImageProperties = columnElem->GetBackgroundImage();

    renderBackgroundImage(rootView, backgroundImageProperties.get(), imageView, image);
}

@end
