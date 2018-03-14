//
//  ACRColumnSetRenderer
//  ACRColumnSetRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRColumnSetRenderer.h"
#import "ACRColumnSetView.h"
#import "ACRRegistration.h"
#import "ColumnSet.h"
#import "ACRLongPressGestureRecognizerFactory.h"
#import "SharedAdaptiveCard.h"
#import "ACRSeparator.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"

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

- (UIView* )render:(UIView<ACRIContentHoldingView> *)viewGroup
            rootViewController:(UIViewController *)vc
            inputs:(NSMutableArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<ColumnSet> columnSetElem = std::dynamic_pointer_cast<ColumnSet>(elem);

    ACRColumnSetView *columnSetView = [[ACRColumnSetView alloc] init];
    [columnSetView setStyle:[viewGroup style]];

    ACRBaseCardElementRenderer *columRenderer =
        [[ACRRegistration getInstance] getRenderer:[NSNumber numberWithInt:(int)CardElementType::Column]] ;
    std::vector<std::shared_ptr<Column>> columns = columnSetElem->GetColumns();

    UIView *prevView = nil, *curView = nil;
    float relativeColumnWidth = 0, prevRelColumnWidth = 0;
    float multiplier = 1.0;
    NSMutableArray *constraints = [[NSMutableArray alloc] init];

    ACOBaseCardElement *acoColumn = [[ACOBaseCardElement alloc] init];
    for(std::shared_ptr<Column> column:columns)
    {
        [ACRSeparator renderSeparation:column forSuperview:columnSetView withHostConfig:config];
        [acoColumn setElem:column];
        curView = (UIStackView *)[columRenderer render:columnSetView rootViewController:vc inputs:inputs baseCardElement:acoColumn hostConfig:acoConfig];
        try
        {
            relativeColumnWidth = std::stof(column->GetWidth());
            if(prevRelColumnWidth)
                multiplier = relativeColumnWidth / prevRelColumnWidth;
        }
        catch(...){ ;}

        if(prevView && prevRelColumnWidth)
        {

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
        else if(!prevView)
        {
            [constraints addObject:
             [NSLayoutConstraint constraintWithItem:curView
                                          attribute:NSLayoutAttributeLeading
                                          relatedBy:NSLayoutRelationEqual
                                             toItem:columnSetView
                                          attribute:NSLayoutAttributeLeading
                                         multiplier:1.0
                                           constant:0]];
        }

        prevView = curView;
        prevRelColumnWidth = relativeColumnWidth;
    }

    if([constraints count]) [columnSetView addConstraints:constraints];

    [columnSetView adjustHuggingForLastElement];

    [viewGroup addArrangedSubview:columnSetView];

    std::shared_ptr<BaseActionElement> selectAction = columnSetElem->GetSelectAction();
    // instantiate and add long press gesture recognizer
    UILongPressGestureRecognizer * gestureRecognizer =
        [ACRLongPressGestureRecognizerFactory getLongPressGestureRecognizer:viewGroup
                                                         rootViewController:vc
                                                                 targetView:columnSetView
                                                              actionElement:selectAction
                                                                     inputs:inputs
                                                                 hostConfig:acoConfig];
    if(gestureRecognizer)
    {
        [columnSetView addGestureRecognizer:gestureRecognizer];
        columnSetView.userInteractionEnabled = YES;
    }
    return columnSetView;
}

@end

