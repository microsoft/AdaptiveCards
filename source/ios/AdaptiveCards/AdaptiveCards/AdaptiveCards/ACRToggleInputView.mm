//
//  ACRToggleInputView.mm
//  ACRToggleInputView
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRToggleInputView.h"
#import "ToggleInput.h"
#import "ACRIBaseCardElementRenderer.h"
#import "HostConfig.h"
#import "ACRUILabel.h"
#import "ACRColumnSetView.h"

using namespace AdaptiveCards;

@implementation ACRToggleInputView
{
    std::shared_ptr<ToggleInput> _toggleInputDataSource;
    std::shared_ptr<HostConfig> _config;
    UISwitch *_toggleSwitch;
}

- (instancetype)initWithInputToggle:(std::shared_ptr<ToggleInput> const&)toggleInput
      WithHostConfig:(std::shared_ptr<HostConfig> const&)hostConfig
{
    NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
    ACRUILabel *lab = [bundle loadNibNamed:@"ACRLabelView" owner:self options:nil][0];
    lab.numberOfLines = 1;
    lab.adjustsFontSizeToFitWidth = YES;
    lab.text = [NSString stringWithCString:toggleInput->GetTitle().c_str()
                                  encoding:NSUTF8StringEncoding];
    _toggleSwitch = [[UISwitch alloc] init];
    NSDictionary<NSString *, NSNumber*> *attributes =
    @{@"spacing":@5, @"alignment":[NSNumber numberWithInt:UIStackViewAlignmentCenter],
      @"distribution":[NSNumber numberWithInt:UIStackViewDistributionFill]};
    
    self = [super initWithFrame:CGRectMake(0, 0, lab.frame.size.width + _toggleSwitch.frame.size.width, MAX(lab.frame.size.height, _toggleSwitch.frame.size.height)) attributes:attributes];
    if(self)
    {
        _toggleInputDataSource = toggleInput;
        _config = hostConfig;
        self.id = [[NSString alloc]initWithCString:_toggleInputDataSource->GetId().c_str()
                                     encoding:NSUTF8StringEncoding];
        lab.translatesAutoresizingMaskIntoConstraints = NO;
        _toggleSwitch.translatesAutoresizingMaskIntoConstraints = NO;
        [self addArrangedSubview:lab];
        [self addArrangedSubview:_toggleSwitch];
        [_toggleSwitch setContentHuggingPriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
        [lab setContentCompressionResistancePriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
        [NSLayoutConstraint constraintWithItem:_toggleSwitch attribute:NSLayoutAttributeRightMargin relatedBy:NSLayoutRelationLessThanOrEqual toItem:self attribute:NSLayoutAttributeRightMargin multiplier:1.0 constant:0].active = YES;
        
        if(_toggleInputDataSource->GetValue() == _toggleInputDataSource->GetValueOn()) {
            _toggleSwitch.on = YES;
        }
        
        self.valueOn  = [[NSString alloc]initWithCString:_toggleInputDataSource->GetValueOn().c_str()
                                           encoding:NSUTF8StringEncoding];
        self.valueOff = [[NSString alloc]initWithCString:_toggleInputDataSource->GetValueOff().c_str()
                                           encoding:NSUTF8StringEncoding];
    }
    return self;
}

- (BOOL)validate:(NSError **)error
{
    // no need to validate
    return YES;
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    dictionary[self.id] = _toggleSwitch.on? self.valueOn : self.valueOff;
}

@end
