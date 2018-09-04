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
#import "ACRView.h"

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
          rootView:(ACRView *)rootView
            inputs:(NSMutableArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<ColumnSet> columnSetElem = std::dynamic_pointer_cast<ColumnSet>(elem);

    ACRColumnSetView *columnSetView = [[ACRColumnSetView alloc] init];
    [columnSetView setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
    [columnSetView setStyle:[viewGroup style]];

    ACRBaseCardElementRenderer *columRenderer =
        [[ACRRegistration getInstance] getRenderer:[NSNumber numberWithInt:(int)CardElementType::Column]] ;
    std::vector<std::shared_ptr<Column>> columns = columnSetElem->GetColumns();

    ACRColumnView *prevView = nil, *curView = nil, *stretchView = nil;
    float relativeColumnWidth = 0, prevRelColumnWidth = 0;
    float multiplier = 1.0;
    NSMutableArray *constraints = [[NSMutableArray alloc] init];

    ACOBaseCardElement *acoColumn = [[ACOBaseCardElement alloc] init];
    for(std::shared_ptr<Column> column:columns)
    {
        [ACRSeparator renderSeparation:column forSuperview:columnSetView withHostConfig:config];
        [acoColumn setElem:column];
        curView = (ACRColumnView *)[columRenderer render:columnSetView rootView:rootView inputs:inputs baseCardElement:acoColumn hostConfig:acoConfig];

        // when stretch, views with stretch properties should have equal width
        if([curView.columnWidth isEqualToString:@"stretch"]){
            if(stretchView){
                [NSLayoutConstraint constraintWithItem:curView
                                    attribute:NSLayoutAttributeWidth
                                    relatedBy:NSLayoutRelationEqual
                                    toItem:stretchView
                                    attribute:NSLayoutAttributeWidth
                                    multiplier:1
                                    constant:0].active = YES;
            }
            stretchView = curView;
        } else if(![curView.columnWidth isEqualToString:@"auto"]){
            try{
                relativeColumnWidth = std::stof(column->GetWidth());
                if(prevRelColumnWidth)
                    multiplier = relativeColumnWidth / prevRelColumnWidth;
            }
            catch(...){
                multiplier = 1;
                relativeColumnWidth = 1;
                NSLog(@"unexpected column width property is given");
            }
        }
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
                                                                   rootView:rootView
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

