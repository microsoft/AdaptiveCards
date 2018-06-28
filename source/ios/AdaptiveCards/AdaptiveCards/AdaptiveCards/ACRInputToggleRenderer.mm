//
//  ACRInputToggleRenderer
//  ACRInputToggleRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputToggleRenderer.h"
#import "ACRInputTableView.h"
#import "ACRContentHoldingUIView.h"
#import "ACRSeparator.h"
#import "ToggleInput.h"
#import "ACRColumnSetView.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACRToggleInputDataSource.h"

@implementation ACRInputToggleRenderer

+ (ACRInputToggleRenderer *)getInstance
{
    static ACRInputToggleRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRToggleInput;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
          rootView:(ACRView *)rootView
            inputs:(NSMutableArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<ToggleInput> toggleBlck = std::dynamic_pointer_cast<ToggleInput>(elem);

    ACRInputTableView *inputView = [[ACRInputTableView alloc] initWithSuperview:viewGroup];
    [inputTableView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
    ACRToggleInputDataSource *dataSource = [[ACRToggleInputDataSource alloc] initWithInputToggle:toggleBlck WithHostConfig:config];
    inputTableView.delegate = dataSource;
    inputTableView.dataSource = dataSource;
    [inputs addObject:dataSource];


    [viewGroup addArrangedSubview:inputView];
    }
    [NSLayoutConstraint constraintWithItem:inputTableView
                                 attribute:NSLayoutAttributeLeading
                                 relatedBy:NSLayoutRelationLessThanOrEqual
                                    toItem:viewGroup
                                 attribute:NSLayoutAttributeLeading
                                multiplier:1.0
                                  constant:0].active = YES;
    [NSLayoutConstraint constraintWithItem:inputTableView
                                 attribute:NSLayoutAttributeTrailing
                                 relatedBy:NSLayoutRelationLessThanOrEqual
                                    toItem:viewGroup
                                 attribute:NSLayoutAttributeTrailing
                                multiplier:1.0
                                  constant:0].active = YES;
    return inputTableView;
}

@end
