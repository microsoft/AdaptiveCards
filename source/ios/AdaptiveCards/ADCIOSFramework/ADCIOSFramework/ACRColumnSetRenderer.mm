//
//  ACRColumnSetRenderer
//  ACRColumnSetRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRColumnSetRenderer.h"
#import "ACRRegistration.h"
#import "ColumnSet.h"
#import "SharedAdaptiveCard.h"
#import "ACRSeparator.h"

@implementation ACRColumnSetRenderer

+ (ACRColumnSetRenderer* ) getInstance
{
    static ACRColumnSetRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (CardElementType) elemType
{
    return CardElementType::ColumnSet;
}

- (UIView* ) render: (UIStackView*) viewGroup
       withCardElem: (std::shared_ptr<BaseCardElement> const &) elem
      andHostConfig: (std::shared_ptr<HostConfig> const &) config
{ 
    std::shared_ptr<ColumnSet> columnSetElem = std::dynamic_pointer_cast<ColumnSet>(elem);
    UIStackView* columnSetView = [[UIStackView alloc] init];
    columnSetView.axis = UILayoutConstraintAxisHorizontal;
    columnSetView.translatesAutoresizingMaskIntoConstraints = false;
    columnSetView.alignment = UIStackViewAlignmentLeading;

    ACRBaseCardElementRenderer* columRenderer = 
        [[ACRRegistration getInstance] getRenderer:[NSNumber numberWithInt: (int) CardElementType::Column]] ;
    std::vector<std::shared_ptr<Column>> columns = columnSetElem->GetColumns();

    UIStackView* prevView = nil, * curView = nil;
    long relativeColumnWidth = 0, prevRelColumnWidth = 0;
    float multiplier = 1.0;
    NSMutableArray* constraints = [[NSMutableArray alloc] init];
    for(std::shared_ptr<Column> column: columns)
    {
        [ACRSeparator renderSeparation:column forSuperview: columnSetView withHostConfig:config];

        curView = (UIStackView* )[columRenderer render: columnSetView withCardElem: column andHostConfig: config];
        try
        {
            relativeColumnWidth = std::stoul(column->GetSize());
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

    [viewGroup addArrangedSubview:columnSetView];

    [constraints addObject:
     [NSLayoutConstraint constraintWithItem:curView
                                  attribute:NSLayoutAttributeTrailing
                                  relatedBy:NSLayoutRelationEqual
                                     toItem:columnSetView
                                  attribute:NSLayoutAttributeTrailing
                                 multiplier:1.0
                                   constant:0]];
    [constraints addObject:
     [NSLayoutConstraint constraintWithItem:columnSetView
                                  attribute:NSLayoutAttributeLeading
                                  relatedBy:NSLayoutRelationEqual
                                     toItem:viewGroup
                                  attribute:NSLayoutAttributeLeading
                                 multiplier:1.0
                                   constant:0]];

    [constraints addObject:
     [NSLayoutConstraint constraintWithItem:columnSetView
                                  attribute:NSLayoutAttributeTrailing
                                  relatedBy:NSLayoutRelationEqual
                                     toItem:viewGroup
                                  attribute:NSLayoutAttributeTrailing
                                 multiplier:1.0
                                   constant:0]];

    [viewGroup addConstraints:constraints];

    return columnSetView;
}

@end

