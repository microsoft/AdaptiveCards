//
//  ACRToggleInputDataSource
//  ACRToggleInputDataSource.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACOBaseCardElement.h>
#import <AdaptiveCards/ACRColumnSetView.h>
#import <AdaptiveCards/ACRIBaseCardElementRenderer.h>
#import <AdaptiveCards/ACRIBaseInputHandler.h>
#import <AdaptiveCards/HostConfig.h>
#import <AdaptiveCards/ToggleInput.h>

@interface ACRToggleInputDataSource : NSObject <ACRIBaseInputHandler>

@property NSString *id;
@property NSString *valueOn;
@property NSString *valueOff;
@property (weak) UISwitch *toggleSwitch;

- (instancetype)initWithInputToggle:(std::shared_ptr<AdaptiveCards::ToggleInput> const &)toggleInput
                     WithHostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const &)hostConfig;
@end
