//
//  ACRHttpTarget
//  ACRHttpTarget.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRIContentHoldingView.h"
#import "SharedAdaptiveCard.h"
#import "HttpAction.h"

@interface ACRHttpTarget:NSObject

- (instancetype)initWithHttpAction:(std::shared_ptr<AdaptiveCards::HttpAction> const&)data
                            inputs:(NSArray *)inputs
                                vc:(UIViewController *)vc;
- (IBAction)create:(UIButton *)sender;

- (NSString *)replaceMatchInString:(NSString *)string data:(NSDictionary *)data;

@end
