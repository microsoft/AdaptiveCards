//
//  ACRTableCellRenderer
//  ACRTableCellRenderer.mm
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACRTableCellRenderer.h>
#import <AdaptiveCards/ACOBaseCardElementPrivate.h>
#import <AdaptiveCards/ACOHostConfigPrivate.h>
#import <AdaptiveCards/ACRRendererPrivate.h>
#import <AdaptiveCards/ACRTableCellView.h>
#import <AdaptiveCards/TableCell.h>
#import <AdaptiveCards/UtiliOS.h>

@implementation ACRTableCellRenderer

+ (ACRTableCellRenderer *)getInstance
{
    static ACRTableCellRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRTableCell;
}


- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
           rootView:(ACRView *)rootView
             inputs:(NSMutableArray *)inputs
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    auto cellElement = std::dynamic_pointer_cast<TableCell>(elem);

    ACRColumnView *cell = (ACRColumnView *)viewGroup;

    cell.rtl = rootView.context.rtl;

    renderBackgroundImage(cellElement->GetBackgroundImage(), cell, rootView);

    [ACRRenderer render:cell
               rootView:rootView
                 inputs:inputs
          withCardElems:cellElement->GetItems()
          andHostConfig:acoConfig];

    [cell setClipsToBounds:NO];

    std::shared_ptr<BaseActionElement> selectAction = cellElement->GetSelectAction();
    ACOBaseActionElement *acoSelectAction = [ACOBaseActionElement getACOActionElementFromAdaptiveElement:selectAction];
    [cell configureForSelectAction:acoSelectAction rootView:rootView];

    [cell configureLayoutAndVisibility:rootView.context.verticalContentAlignment
                             minHeight:cellElement->GetMinHeight()
                            heightType:GetACRHeight(cellElement->GetHeight())
                                  type:ACRContainer];

    return cell;
}


@end
