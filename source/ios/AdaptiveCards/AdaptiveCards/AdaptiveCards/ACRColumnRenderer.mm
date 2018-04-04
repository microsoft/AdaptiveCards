//
//  ACRColumnRenderer
//  ACRColumnRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRColumnRenderer.h"
#import "ACRColumnView.h"
#import "ACRRendererPrivate.h"
#import "Column.h"
#import "SharedAdaptiveCard.h"
#import "ACRLongPressGestureRecognizerFactory.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"

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
                                                     parentStyle:[viewGroup style] hostConfig:acoConfig];
    [ACRRenderer render:column
               rootView:rootView
                 inputs:inputs
          withCardElems:columnElem->GetItems()
          andHostConfig:acoConfig];

    [viewGroup addArrangedSubview:column];

    [column setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];
    [column setClipsToBounds:TRUE];
    if(columnElem->GetWidth() == "stretch" || columnElem->GetWidth() == "")
    {
        [column setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
    }

    [column adjustHuggingForLastElement];

    std::shared_ptr<BaseActionElement> selectAction = columnElem->GetSelectAction();
    // instantiate and add tap gesture recognizer
    UILongPressGestureRecognizer * gestureRecognizer =
        [ACRLongPressGestureRecognizerFactory getLongPressGestureRecognizer:viewGroup
                                                                   rootView:rootView
                                                                 targetView:column
                                                              actionElement:selectAction
                                                                     inputs:inputs
                                                                 hostConfig:acoConfig];
    if(gestureRecognizer)
    {
        [column addGestureRecognizer:gestureRecognizer];
        column.userInteractionEnabled = YES;
    }

    return column;
}

@end

