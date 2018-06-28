//
//  ACRInputChoiceSetRenderer
//  ACRInputChoiceSetRenderer.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRInputChoiceSetRenderer.h"
#import "ACRInputTableView.h"
#import "ChoiceSetInput.h"
#import "ACRChoiceSetViewDataSource.h"
#import "ACRChoiceSetViewDataSourceCompactStyle.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"

@implementation ACRInputChoiceSetRenderer

+ (ACRInputChoiceSetRenderer *)getInstance
{
    static ACRInputChoiceSetRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRChoiceSetInput;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
          rootView:(ACRView *)rootView
            inputs:(NSMutableArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<ChoiceSetInput> choiceSet = std::dynamic_pointer_cast<ChoiceSetInput>(elem);
    // creates a tableview with pre-defined style
    ACRInputTableView *choiceSetView = [[ACRInputTableView alloc] initWithSuperview:viewGroup];
    choiceSetView.contentInset = UIEdgeInsetsMake(-35, 0, 0, 0);
    NSObject<UITableViewDelegate, UITableViewDataSource> *dataSource = nil;

    if(choiceSet->GetChoiceSetStyle() == ChoiceSetStyle::Compact) {
        dataSource = [[ACRChoiceSetViewDataSourceCompactStyle alloc] initWithInputChoiceSet:choiceSet rootView:rootView];
        [choiceSetView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
    } else {
        dataSource = [[ACRChoiceSetViewDataSource alloc] initWithInputChoiceSet:choiceSet];
        [choiceSetView setSeparatorStyle:UITableViewCellSeparatorStyleSingleLineEtched];
    }
    choiceSetView.delegate = dataSource;
    choiceSetView.dataSource = dataSource;
    [inputs addObject:dataSource];    
    
    [viewGroup addArrangedSubview:choiceSetView];

    [viewGroup addConstraint:
     [NSLayoutConstraint constraintWithItem:choiceSetView
                                  attribute:NSLayoutAttributeLeading
                                  relatedBy:NSLayoutRelationLessThanOrEqual
                                     toItem:viewGroup
                                  attribute:NSLayoutAttributeLeading
                                 multiplier:1.0
                                   constant:0]];
    [viewGroup addConstraint:
     [NSLayoutConstraint constraintWithItem:choiceSetView
                                  attribute:NSLayoutAttributeTrailing
                                  relatedBy:NSLayoutRelationLessThanOrEqual
                                     toItem:viewGroup
                                  attribute:NSLayoutAttributeTrailing
                                 multiplier:1.0
                                   constant:0]];

    return choiceSetView;
}

@end
