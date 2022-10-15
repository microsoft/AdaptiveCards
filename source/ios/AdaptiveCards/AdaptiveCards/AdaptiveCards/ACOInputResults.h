//
//  ACOInputResults.h
//  ACOInputResults
//
//  Copyright © 2020 Microsoft. All rights reserved.
//
//

#import "ACRIBaseInputHandler.h"
#import "ACRView.h"
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface ACOInputResults : NSObject

@property (weak) id<ACRIBaseInputHandler> firstFailedInput;
@property NSMutableArray<ACRIBaseInputHandler> *gatheredInputs;
@property BOOL hasValidationPassed;
@property BOOL hasViewChangedForAnyViews;

- (instancetype)init:(ACRView *)rootView parent:(ACRColumnView *)parent;
- (void)validateInput;
- (BOOL)isInputValid:(id<ACRIBaseInputHandler>)input;

@end
