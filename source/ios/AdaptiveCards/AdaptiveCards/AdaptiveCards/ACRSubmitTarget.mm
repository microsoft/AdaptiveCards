//
//  ACRSubmitTarget
//  ACRSubmitTarget.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRSubmitTarget.h"
#import "ACRContentHoldingUIView.h"
#import "ACRIBaseInputHandler.h"
#import "ACRViewController.h"

@implementation ACRSubmitTarget
{
    NSString *_data;
    NSArray *_inputs;
    UIColor *_backgroundColor;
    __weak UIViewController *_vc;
    __weak UIView *_targetView;
}

- (instancetype)initWithDataString:(NSString *)data
                            inputs:(NSArray *)inputs
                                vc:(UIViewController *)vc
                        targetView:(UIView *)targetView
{
    self = [super init];
    if(self)
    {
        _data = data;
        _inputs = inputs;
        _vc = vc;
        _targetView = targetView;
    }
    return self;
}

- (instancetype)initWithDataString:(NSString *)data
                            inputs:(NSArray *)inputs
                                vc:(UIViewController *)vc
{
    self = [self initWithDataString:data
                             inputs:inputs
                                 vc:vc
                         targetView:nil];
    return self;
}

- (IBAction)submit:(UIButton *)sender
{
    [self gatherInput];
}

- (IBAction)submitWithRecognizer:(UILongPressGestureRecognizer *) recognizer
{
    [self gatherInput];
    // background color of a UIView object is changed to provide visual cue
    // that the object is activated
    if(recognizer.state == UIGestureRecognizerStateBegan)
    {
        _backgroundColor = _targetView.backgroundColor;
        _targetView.backgroundColor = [UIColor colorWithRed:0xD4/255.0 green:0xD4/255.0 blue:0xD4/255.0 alpha:0x1];
        [self gatherInput];
    }
    else if(recognizer.state == UIGestureRecognizerStateEnded)
    {
        _targetView.backgroundColor = _backgroundColor;
    }
}

- (void)gatherInput
{
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    NSError *err = nil;
    for(id<ACRIBaseInputHandler> input in _inputs)
    {
        if([input validate:&err] == NO)
        {
            NSLog(@"input validation failed %@", err);
        }
        else
        {
            [input getInput:dictionary];
        }
    }

    err = nil;

    NSData *json = [NSJSONSerialization dataWithJSONObject:dictionary options:NSJSONWritingPrettyPrinted error:&err];

    [((ACRViewController *)_vc).acrActionDelegate didFetchUserResponses:json data:_data error:err];
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRequireFailureOfGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer
{
    if([gestureRecognizer isKindOfClass:[UIPanGestureRecognizer class]])
    {
        return YES;
    }
    return NO;
}

@end
