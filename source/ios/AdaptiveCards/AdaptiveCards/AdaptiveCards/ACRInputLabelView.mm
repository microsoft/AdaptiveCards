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
    NSObject<ACRIBaseInputHandler> *inputHandler = [self getInputHandler];
    if (inputHandler) {
        NSError *error = nil;
        if (NO == [inputHandler validate:&error]) {
            if (self.hasErrorMessage) {
                self.errorMessage.hidden = NO;
            }
        } else {
            if (self.hasErrorMessage) {
                self.errorMessage.hidden = YES;
            }
            self.stack.arrangedSubviews[1].layer.borderWidth = 0;
            return YES;
        }
    }
    self.stack.arrangedSubviews[1].layer.borderWidth = 1;
    self.stack.arrangedSubviews[1].layer.cornerRadius = 6.0f;
    self.stack.arrangedSubviews[1].layer.borderColor = UIColor.systemRedColor.CGColor;
    return NO;
}

- (NSObject<ACRIBaseInputHandler>  *)getInputHandler
{
    NSObject<ACRIBaseInputHandler> *inputHandler = nil;
    id inputView = [self getInputView];
    if (inputView) {
        NSObject<ACRIBaseInputHandler> *inputHandler = [inputView conformsToProtocol:@protocol(ACRIBaseInputHandler)] ? inputView : self.dataSource;
        if ([inputHandler conformsToProtocol:@protocol(ACRIBaseInputHandler)]) {
            return inputHandler;
        }
    }
    return inputHandler;
}

- (id)getInputView
{
    if ((_stack.arrangedSubviews.count) == 3) {
        return self.stack.arrangedSubviews[1];
    }
    return nil;
}

- (void)setFocus:(BOOL)shouldBecomeFirstResponder
{
    id inputHandler = [self getInputHandler];
    if (!inputHandler) {
        return;
    }
    if ([inputHandler isKindOfClass:[UITextField class]]) {
        [inputHandler setFocus:shouldBecomeFirstResponder];
    } else {
        UIView<ACRIBaseInputHandler> *inputView = [self getInputView];
        if ([inputView conformsToProtocol:@protocol(ACRIBaseInputHandler)]) {
            [ACRInputLabelView setFocus:shouldBecomeFirstResponder view:inputView];
        }
    }
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    id<ACRIBaseInputHandler> inputHandler = [self getInputHandler];
    if (inputHandler) {
        [inputHandler getInput:dictionary];
    }
}

+ (void)setFocus:(BOOL)shouldBecomeFirstResponder view:(UIView *)view{
    if (shouldBecomeFirstResponder) {
        [view becomeFirstResponder];
    } else {
        [view resignFirstResponder];
    }
}

@end
