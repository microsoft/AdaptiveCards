//
//  ACRColumnRenderer
//  ACRColumnRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRColumnRenderer.h"
#import "ACRRegistration.h"
#import "Column.h"
#import "SharedAdaptiveCard.h"

@implementation ACRColumnRenderer

+ (ACRColumnRenderer* ) getInstance
{
    static ACRColumnRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (CardElementType) elemType
{
    return CardElementType::Column;
}

- (UIView* ) render: (UIStackView*) viewGroup
       withCardElem: (std::shared_ptr<BaseCardElement> const &) elem
      andHostConfig: (std::shared_ptr<HostConfig> const &) config
{ 
    std::shared_ptr<Column> columnElem = std::dynamic_pointer_cast<Column>(elem);

    UIStackView* column = [[UIStackView alloc] init];
    column.axis = UILayoutConstraintAxisVertical;
    column.alignment = UIStackViewAlignmentFill;//UIStackViewAlignmentCenter;
    column.distribution = UIStackViewDistributionEqualSpacing;
    column.translatesAutoresizingMaskIntoConstraints = false;

    [[ACRRegistration getInstance] render: viewGroup
                          withContentView: column 
                            withCardElems: columnElem->GetItems()
                            andHostConfig: config];

    [column setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];
    column.contentMode = UIViewContentModeScaleAspectFill;
    [column setClipsToBounds:TRUE];
    if(columnElem->GetSize() == "stretch")
    {
        [column setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
    }
    
    return column;
}

@end

