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
    __weak UIViewController *_vc;
}

- (instancetype)initWithDataString:(NSString *)data
                            inputs:(NSArray *)inputs
                                vc:(UIViewController *)vc
{
    self = [super init];
    if(self)
    {
        _data = data;
        _inputs = inputs;
        _vc = vc;
    }
    return self;
}

- (IBAction)submit:(UIButton *)sender
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

@end
