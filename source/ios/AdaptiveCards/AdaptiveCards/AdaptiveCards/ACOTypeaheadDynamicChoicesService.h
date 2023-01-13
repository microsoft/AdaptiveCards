//
//  ACOTypeaheadDynamicChoicesService.h
//  AdaptiveCards
//
//  Created by Jyoti Kukreja on 12/01/23.
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol ACOTypeaheadDynamicChoicesProtocol <NSObject>
- (void)updateUIWithqueryString:(NSString*)queryString dynamicChoices:(NSArray<NSString *> *)choices withError:(NSError *)error;
@end

@interface ACOTypeaheadDynamicChoicesService: NSObject<ACODebouncerDelegate>

-(instancetype)initWithRootView:(ACRView *)rootView
                      inputElem:(ACOBaseCardElement *)inputElem
        typeaheadSearchDelegate:(id<ACOTypeaheadDynamicChoicesProtocol>) delegate;

- (void)fetchChoicesFromDynamicSourceWithSearchQuery:(NSString *)searchQuery;

@end
