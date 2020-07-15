//
//  ACRInputLabelView
//  ACRInputLabelView.mm
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import "ACRInputLabelView.h"


@implementation ACRInputLabelView

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    [self commonInit];
    return self;
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];
    [self commonInit];
    return self;
}

- (void)commonInit
{
    NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
    UIView *contentView = [bundle loadNibNamed:@"ACRInputLabelView" owner:self options:nil][0];
    [self addSubview:contentView];
    self.layoutMargins = UIEdgeInsetsMake(0, 0, 0, 0);    
    [self.layoutMarginsGuide.leadingAnchor constraintEqualToAnchor:contentView.leadingAnchor].active = YES;
    [self.layoutMarginsGuide.trailingAnchor constraintEqualToAnchor:contentView.trailingAnchor].active = YES;
    [self.layoutMarginsGuide.topAnchor constraintEqualToAnchor:contentView.topAnchor].active = YES;
    [self.layoutMarginsGuide.bottomAnchor constraintEqualToAnchor:contentView.bottomAnchor].active = YES;    
}

- (BOOL)validate:(NSError **)error
{
    if ((_stack.arrangedSubviews.count) == 3 && [self.stack.arrangedSubviews[1] conformsToProtocol:@protocol(ACRIBaseInputHandler)]) {
        NSError *error = nil;
        if (self.isRequired) {
            // add get value message
        }
        
        if (NO == [self.stack.arrangedSubviews[1] validate:&error]) {
            if (self.hasErrorMessage) {
                self.errorMessage.hidden = NO;
            }
        } else {
            if (self.hasErrorMessage) {
                self.errorMessage.hidden = YES;
            }
            return YES;
        }        
    }
    return NO;
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
}

@end
