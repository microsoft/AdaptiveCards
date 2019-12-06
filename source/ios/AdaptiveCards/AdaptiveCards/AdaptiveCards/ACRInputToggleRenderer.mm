//
//  ACRInputToggleRenderer
//  ACRInputToggleRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputToggleRenderer.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRColumnSetView.h"
#import "ACRContentHoldingUIView.h"
#import "ACRInputTableView.h"
#import "ACRSeparator.h"
#import "ACRToggleInputDataSource.h"
#import "ToggleInput.h"
#import "UtiliOS.h"

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

    NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
    if (!bundle) { // https://github.com/Microsoft/AdaptiveCards/issues/1834
        return nil;
    }
    ACRInputTableView *inputTableView = [bundle loadNibNamed:@"ACRInputTableView" owner:self options:nil][0];
    inputTableView.frame = CGRectMake(0, 0, viewGroup.frame.size.width, viewGroup.frame.size.height);
    [inputTableView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
    ACRToggleInputDataSource *dataSource = [[ACRToggleInputDataSource alloc] initWithInputToggle:toggleBlck WithHostConfig:config];
    dataSource.parentStyle = viewGroup.style;
    inputTableView.delegate = dataSource;
    inputTableView.dataSource = dataSource;

    [inputs addObject:dataSource];

    if (elem->GetHeight() == HeightType::Stretch) {
        ACRColumnView *textInputContainer = [[ACRColumnView alloc] init];
        [textInputContainer addArrangedSubview:inputTableView];
        // Add a blank view so the input field doesnt grow as large as it can and so it keeps the same behavior as Android and UWP
        UIView *blankTrailingSpace = [[UIView alloc] init];
        [textInputContainer addArrangedSubview:blankTrailingSpace];
        [textInputContainer adjustHuggingForLastElement];

        [viewGroup addArrangedSubview:textInputContainer];
    } else {
        [viewGroup addArrangedSubview:inputTableView];
    }

    configVisibility(inputTableView, elem);

    return inputTableView;
}

@end
