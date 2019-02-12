//
//  ACRColumnRenderer
//  ACRColumnRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRColumnRenderer.h"
#import "ACRColumnView.h"
#import "ACRRendererPrivate.h"
#import "ACRViewPrivate.h"
#import "Column.h"
#import "SharedAdaptiveCard.h"
#import "ACRLongPressGestureRecognizerFactory.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"
#import "Util.h"

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

    ACRColumnView* column = [[ACRColumnView alloc] initWithStyle:(ACRContainerStyle)columnElem->GetStyle()
                                                     parentStyle:[viewGroup style] hostConfig:acoConfig superview:viewGroup];

    [ACRView renderBackgroundImageView:columnElem->GetBackgroundImage().get() containerView:column rootView:rootView];
    
    column.pixelWidth = columnElem->GetPixelWidth();
    if(columnElem->GetWidth() == "stretch" || columnElem->GetWidth() == "") {
        column.columnWidth = @"stretch";
    } else if(columnElem->GetWidth() == "auto"){
        column.columnWidth = @"auto";
    }

    UIView *leadingBlankSpace = nil, *trailingBlankSpace = nil;
    if(columnElem->GetVerticalContentAlignment() == VerticalContentAlignment::Center || columnElem->GetVerticalContentAlignment() == VerticalContentAlignment::Bottom){
        leadingBlankSpace = [column addPaddingSpace];
    }

    [ACRRenderer render:column
               rootView:rootView
                 inputs:inputs
          withCardElems:columnElem->GetItems()
          andHostConfig:acoConfig];

    if(columnElem->GetVerticalContentAlignment() == VerticalContentAlignment::Center || (columnElem->GetVerticalContentAlignment() == VerticalContentAlignment::Top && _fillAlignment)){
        trailingBlankSpace = [column addPaddingSpace];
    }

    [viewGroup addArrangedSubview:column];

    [column setClipsToBounds:TRUE];

    std::shared_ptr<BaseActionElement> selectAction = columnElem->GetSelectAction();
    // instantiate and add tap gesture recognizer
    [ACRLongPressGestureRecognizerFactory addLongPressGestureRecognizerToUIView:viewGroup
                                                                       rootView:rootView
                                                                  recipientView:column
                                                                  actionElement:selectAction
                                                                     hostConfig:acoConfig];

    if(leadingBlankSpace != nil && trailingBlankSpace != nil){
        [NSLayoutConstraint constraintWithItem:leadingBlankSpace
                                     attribute:NSLayoutAttributeHeight
                                     relatedBy:NSLayoutRelationEqual
                                        toItem:trailingBlankSpace
                                     attribute:NSLayoutAttributeHeight
                                    multiplier:1.0
                                      constant:0].active = YES;
    }

    configVisibility(column, elem);

    return column;
}

@end
