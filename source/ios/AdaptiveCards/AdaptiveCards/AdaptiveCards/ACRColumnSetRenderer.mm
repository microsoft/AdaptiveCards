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
#import "Column.h"
#import "ACRColumnRenderer.h"
#import "Enums.h"

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

    ACRColumnSetView *columnSetView = [[ACRColumnSetView alloc] initWithFrame:viewGroup.frame];
    [columnSetView setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
    [columnSetView setStyle:[viewGroup style]];

    ACRBaseCardElementRenderer *columnRenderer =
        [[ACRRegistration getInstance] getRenderer:[NSNumber numberWithInt:(int)CardElementType::Column]] ;
    std::vector<std::shared_ptr<Column>> columns = columnSetElem->GetColumns();

    ACRColumnView *prevView = nil, *curView = nil, *stretchView = nil;
    float relativeColumnWidth = 0, prevRelColumnWidth = 0;
    float multiplier = 1.0;
    NSMutableArray *constraints = [[NSMutableArray alloc] init];
    
    ACRColumnRenderer *castedRenderer = (ACRColumnRenderer *)columnRenderer;
    for(std::shared_ptr<Column> column:columns)
    {
        if(column->GetVerticalContentAlignment() != VerticalContentAlignment::Top) {
            castedRenderer.fillAlignment = YES;
        }
    }
    
    ACOBaseCardElement *acoColumn = [[ACOBaseCardElement alloc] init];
    auto firstColumn = columns.begin();
    for(std::shared_ptr<Column> column:columns)
    {
        if(*firstColumn != column) {
            [ACRSeparator renderSeparation:column forSuperview:columnSetView withHostConfig:config];
        }
        [acoColumn setElem:column];
        curView = (ACRColumnView *)[columnRenderer render:columnSetView rootView:rootView inputs:inputs baseCardElement:acoColumn hostConfig:acoConfig];

        // when stretch, views with stretch properties should have equal width
        if(curView.pixelWidth){
            [constraints addObject:
             [NSLayoutConstraint constraintWithItem:curView
                                          attribute:NSLayoutAttributeWidth
                                          relatedBy:NSLayoutRelationEqual
                                             toItem:nil
                                          attribute:NSLayoutAttributeNotAnAttribute
                                         multiplier:1
                                           constant:curView.pixelWidth]];
        } else if([curView.columnWidth isEqualToString:@"stretch"]){
            if(stretchView){
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
        } else if(![curView.columnWidth isEqualToString:@"auto"]){
            try{
                relativeColumnWidth = std::stof(column->GetWidth());
                if(prevRelColumnWidth)
                    multiplier = relativeColumnWidth / prevRelColumnWidth;

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

                if(curView.hasStretchableView || (columnSetElem->GetHeight() == HeightType::Stretch)){
                    [columnSetView setAlignmentForColumnStretch];
                }

                prevView = curView;
                prevRelColumnWidth = relativeColumnWidth;
            }
            catch(...){
                multiplier = 1;
                relativeColumnWidth = 1;
                NSLog(@"unexpected column width property is given");
            }
        }
    }

    castedRenderer.fillAlignment = NO;
    
    if([constraints count]) {
        [columnSetView addConstraints:constraints];
    }
    [viewGroup addArrangedSubview:columnSetView];

    std::shared_ptr<BaseActionElement> selectAction = columnSetElem->GetSelectAction();
    // instantiate and add long press gesture recognizer
    [ACRLongPressGestureRecognizerFactory addLongPressGestureRecognizerToUIView:viewGroup
                                                                       rootView:rootView
                                                                  recipientView:columnSetView
                                                                  actionElement:selectAction
                                                                     hostConfig:acoConfig];
    return columnSetView;
}

@end

