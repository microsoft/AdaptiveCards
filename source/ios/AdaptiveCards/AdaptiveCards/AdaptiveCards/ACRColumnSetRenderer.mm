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
#import "ACRTapGestureRecognizerFactory.h"
#import "SharedAdaptiveCard.h"
#import "ACRSeparator.h"

@implementation ACRColumnSetRenderer

+ (ACRColumnSetRenderer *)getInstance
{
    static ACRColumnSetRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (CardElementType)elemType
{
    return CardElementType::ColumnSet;
}

- (UIView* )render:(UIView<ACRIContentHoldingView> *)viewGroup
            rootViewController:(UIViewController *)vc
            inputs:(NSMutableArray *)inputs
      withCardElem:(std::shared_ptr<BaseCardElement> const &)elem
     andHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    std::shared_ptr<ColumnSet> columnSetElem = std::dynamic_pointer_cast<ColumnSet>(elem);

    ACRColumnSetView *columnSetView = [[ACRColumnSetView alloc] init];

    ACRBaseCardElementRenderer *columRenderer =
        [[ACRRegistration getInstance] getRenderer:[NSNumber numberWithInt:(int)CardElementType::Column]] ;
    std::vector<std::shared_ptr<Column>> columns = columnSetElem->GetColumns();

    UIView *prevView = nil, *curView = nil;
    long relativeColumnWidth = 0, prevRelColumnWidth = 0;
    float multiplier = 1.0;
    NSMutableArray *constraints = [[NSMutableArray alloc] init];
    for(std::shared_ptr<Column> column:columns)
    {
        [ACRSeparator renderSeparation:column forSuperview:columnSetView withHostConfig:config];

        curView = (UIStackView *)[columRenderer render:columnSetView rootViewController: vc inputs:inputs withCardElem:column andHostConfig:config];
        try
        {
            relativeColumnWidth = std::stoul(column->GetWidth());
            if(prevRelColumnWidth)
                multiplier = ((float)relativeColumnWidth) / prevRelColumnWidth;
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
    // instantiate and add tap gesture recognizer
    UITapGestureRecognizer * tapGestureRecognizer =
        [ACRTapGestureRecognizerFactory getTapGestureRecognizer:viewGroup
                                             rootViewController:vc
                                                  actionElement:selectAction
                                                         inputs:inputs
                                                     hostConfig:config];
    if(tapGestureRecognizer)
    {
        [columnSetView addGestureRecognizer:tapGestureRecognizer];
        columnSetView.userInteractionEnabled = YES;
    }
    return columnSetView;
}

@end

