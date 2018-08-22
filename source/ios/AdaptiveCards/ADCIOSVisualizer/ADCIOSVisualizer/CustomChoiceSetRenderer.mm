//
//  ACRInputChoiceSetRenderer
//  ACRInputChoiceSetRenderer.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "CustomChoiceSetRenderer.h"
#import <AdaptiveCards/ACRInputTableView.h>
#import <AdaptiveCards/ChoiceSetInput.h>
#import <AdaptiveCards/ACRChoiceSetViewDataSource.h>
#import <AdaptiveCards/ACRChoiceSetViewDataSourceCompactStyle.h>
#import <AdaptiveCards/ACOHostConfigPrivate.h>
#import <AdaptiveCards/ACOBaseCardElementPrivate.h>

@implementation CustomChoiceSetRenderer

+ (CustomChoiceSetRenderer *) getInstance
{
    static CustomChoiceSetRenderer *sharedInstance = nil;
    static dispatch_once_t onceToken = 0;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[self alloc] init];
    });
    return sharedInstance;
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
    NSObject<UITableViewDelegate, UITableViewDataSource> *dataSource = nil;
    
    if(choiceSet->GetChoiceSetStyle() == ChoiceSetStyle::Compact && choiceSet->GetIsMultiSelect() == false) {
        dataSource = [[ACRChoiceSetViewDataSourceCompactStyle alloc] initWithInputChoiceSet:choiceSet rootView:rootView];
        [choiceSetView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
    } else {
        dataSource = [[ACRChoiceSetViewDataSource alloc] initWithInputChoiceSet:choiceSet];
        ACRChoiceSetViewDataSource *dataSourceTypeCasted = (ACRChoiceSetViewDataSource*) dataSource;
        dataSourceTypeCasted.acrChoiceSetResourceDelegate = self;
        [choiceSetView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
    }
    
    choiceSetView.delegate = dataSource;
    choiceSetView.dataSource = dataSource;
    [inputs addObject:dataSource];
    
    if(elem->GetHeight() == HeightType::Stretch){
        ACRColumnView *textInputContainer = [[ACRColumnView alloc] init];
        [textInputContainer addArrangedSubview:choiceSetView];
        
        // Add a blank view so the input field doesnt grow as large as it can and so it keeps the same behavior as Android and UWP
        UIView *blankTrailingSpace = [[UIView alloc] init];
        [textInputContainer addArrangedSubview:blankTrailingSpace];
        [textInputContainer adjustHuggingForLastElement];
        
        [viewGroup addArrangedSubview:textInputContainer];
    } else {
        [viewGroup addArrangedSubview:choiceSetView];
    }
    
    [NSLayoutConstraint constraintWithItem:choiceSetView
                                 attribute:NSLayoutAttributeLeading
                                 relatedBy:NSLayoutRelationLessThanOrEqual
                                    toItem:viewGroup
                                 attribute:NSLayoutAttributeLeading
                                multiplier:1.0
                                  constant:0].active = YES;
    
    [NSLayoutConstraint constraintWithItem:choiceSetView
                                 attribute:NSLayoutAttributeTrailing
                                 relatedBy:NSLayoutRelationLessThanOrEqual
                                    toItem:viewGroup
                                 attribute:NSLayoutAttributeTrailing
                                multiplier:1.0
                                  constant:0].active = YES;
    
    return choiceSetView;
}

- (UIImage*) getRadioButtonForSelectedState{
        return [UIImage imageNamed:@"unchecked.png" inBundle:[NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"] compatibleWithTraitCollection:nil];
}

- (UIImage*) getRadioButtonForUnselectedState{
        return [UIImage imageNamed:@"checked.png" inBundle:[NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"] compatibleWithTraitCollection:nil];
}

- (UIImage*) getCheckBoxButtonSelectedState{
       return [UIImage imageNamed:@"unchecked-checkbox-24.png" inBundle:[NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"] compatibleWithTraitCollection:nil];
}

- (UIImage*) getCheckBoxButtonUnselectedState{
       return [UIImage imageNamed:@"checked-checkbox-24.png" inBundle:[NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"] compatibleWithTraitCollection:nil];
}

@end
