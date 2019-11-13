//
//  ACRToggleInputDataSource
//  ACRToggleInputDataSource.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACOBaseCardElement.h"
#import "ACRColumnSetView.h"
#import "ACRIBaseCardElementRenderer.h"
#import "ACRIBaseInputHandler.h"
#import "HostConfig.h"
#import "ToggleInput.h"

@interface ACRToggleInputDataSource : NSObject <UITableViewDataSource, UITableViewDelegate, ACRIBaseInputHandler>

@property ACRContainerStyle parentStyle;
@property NSString *id;
@property NSString *valueOn;
@property NSString *valueOff;
@property UISwitch *toggleSwitch;

- (instancetype)initWithInputToggle:(std::shared_ptr<AdaptiveCards::ToggleInput> const &)toggleInput
                     WithHostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const &)hostConfig;
@end
