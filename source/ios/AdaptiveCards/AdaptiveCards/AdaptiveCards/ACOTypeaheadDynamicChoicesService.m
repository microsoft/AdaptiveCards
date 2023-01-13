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

@interface ACOTypeaheadDynamicChoicesService() <ACODebouncerDelegate>
@end

@implementation ACOTypeaheadDynamicChoicesService {
    __weak ACRView *_rootView;
    ACODebouncer *_debouncer;
}

-(instancetype)initWithRootView:(ACRView *)rootView
{
    _rootView = rootView;
    _debouncer = [[ACODebouncer alloc] initWithDelay:0.2];
    _debouncer.delegate = self;
}

- (void)fetchChoicesFromDynamicSourceWithSearchQuery:(NSString *)searchQuery
                                            pageSize:(int) pageSize
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
                    if (!error) {
                            [strongSelf->_loader stopAnimating];
                            [strongSelf->_filteredDataSource updatefilteredListForStaticAndDynamicTypeahead:key dynamicChoices:_choices];
                        if (strongSelf->_filteredDataSource.count) {
                            [strongSelf configureSearchStateUI:displayingResults];
                        } else if(![key length]) {
                            [strongSelf configureSearchStateUI:zeroState];
                            [strongSelf->_filteredDataSource resetFilter];
                        } else {
                            [strongSelf configureSearchStateUI:displayingInvalidSearchError];
                        }
                            [strongSelf updateListViewLayout];
                        }
                        else
                        {
                            [strongSelf configureSearchStateUI:displayingGenericError];
                            [strongSelf updateListViewLayout];
                        }
                    });
                }];
            }
        });
    }
}
