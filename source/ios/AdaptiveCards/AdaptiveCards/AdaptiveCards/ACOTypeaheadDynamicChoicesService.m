//
//  ACOTypeaheadDynamicChoicesService.m
//  AdaptiveCards
//
//  Created by Jyoti Kukreja on 12/01/23.
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRView.h"
#import "ACODebouncer.h"
#import "ACOTypeaheadDynamicChoicesService.h"
#import "ACRChoiceSetTypeaheadSearchView.h"

@interface ACOTypeaheadDynamicChoicesService() <ACODebouncerDelegate>
@end

@implementation ACOTypeaheadDynamicChoicesService {
    __weak ACRView *_rootView;
    ACODebouncer *_debouncer;
    dispatch_queue_t _global_queue;
    ACOBaseCardElement *_inputElem;
    id<ACOTypeaheadDynamicChoicesProtocol> _typeaheadSearchDelegate;
}

-(instancetype)initWithRootView:(ACRView *)rootView
                      inputElem:(ACOBaseCardElement *)inputElem
        typeaheadSearchDelegate:(id<ACOTypeaheadDynamicChoicesProtocol>) delegate
{
    self = [super init];
    if(self) {
        _rootView = rootView;
        _debouncer = [[ACODebouncer alloc] initWithDelay:0.2];
        _debouncer.delegate = self;
        _global_queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
        _inputElem = inputElem;
        _typeaheadSearchDelegate = delegate;
    }

    return self;
}

- (void)fetchChoicesFromDynamicSourceWithSearchQuery:(NSString *)searchQuery
{
    [_debouncer postInput:searchQuery];
}

- (void)dealloc
{
    _debouncer.delegate = nil;
}

#pragma mark - ACODebouncerDelegate Methods specifically for dynamic typeahead
- (void)debouncerDidSendOutput:(id)key
{
    if ([key isKindOfClass:NSString.class])
    {
        dispatch_async(_global_queue, ^{
            __weak typeof(self) weakSelf = self;
            if ([self->_rootView.acrActionDelegate
                 respondsToSelector:@selector(onChoiceSetQueryChange:acoElem:completion:)]) {
                [self->_rootView.acrActionDelegate onChoiceSetQueryChange:key acoElem:self->_inputElem completion:^(NSArray<NSString *> * _choices, NSError *error) {
                    __strong typeof(self) strongSelf = weakSelf;
                    dispatch_async(dispatch_get_main_queue(), ^{
                        [strongSelf->_typeaheadSearchDelegate updateUIWithqueryString:key dynamicChoices:_choices withError:error];
                    });
                }];
            }
        });
    }
}
@end
