//
//  ACOInputResults.mm
//  ACOInputResults
//
//  Copyright © 2020 Microsoft. All rights reserved.
//
//

#import "ACOInputResults.h"
#import "ACRViewPrivate.h"

@implementation ACOInputResults {
    __weak ACRView *_view;
    __weak ACRColumnView *_currentShowcard;
    NSHashTable *_set;
}

- (instancetype)init:(ACRView *)rootView parent:(ACRColumnView *)parent
{
    self = [super init];
    if (self) {
        _view = rootView;
        _currentShowcard = parent;
        _gatheredInputs = [[NSMutableArray<ACRIBaseInputHandler> alloc] init];
        _set = [[NSHashTable alloc] initWithOptions:NSHashTableWeakMemory capacity:5];
    }
    return self;
}

- (void)validateInput
{
    self.hasValidationPassed = YES;
    self.hasViewChangedForAnyViews = NO;
    NSError *error = nil;

    ACRColumnView *parent = _currentShowcard;

    while (parent) {
        NSMutableArray<ACRIBaseInputHandler> *inputs = parent.inputHandlers;
        for (id<ACRIBaseInputHandler> input in inputs) {
            BOOL validationResult = [input validate:&error];
            [_gatheredInputs addObject:input];
            if (self.hasValidationPassed && !validationResult) {
                self.firstFailedInput = input;
            } else {
                [input setFocus:NO view:nil];
            }
            if (validationResult) {
                [_set addObject:input];
            }
            self.hasValidationPassed &= validationResult;
            self.hasViewChangedForAnyViews |= input.hasVisibilityChanged;
        }
        parent = [_view getParent:parent];
    }
}

- (BOOL)isInputValid:(id<ACRIBaseInputHandler>)input
{
    return [_set containsObject:input];
}

@end
