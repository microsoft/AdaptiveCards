//
//  ACOTypeaheadDynamicChoicesService.h
//  AdaptiveCards
//
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACOTypeaheadDebouncer.h"
#import "ACOTypeaheadSearchHandler.h"
#import "ACRView.h"

@interface ACOTypeaheadDynamicChoicesService: NSObject<ACOTypeaheadDebouncerDelegate>

- (instancetype)initWithRootView:(ACRView *)rootView
                       inputElem:(ACOBaseCardElement *)inputElem
         typeaheadSearchDelegate:(id<ACRTypeaheadSearchProtocol>)typeaheadSearchProtocol;

- (void)fetchChoicesFromDynamicSourceWithSearchQuery:(NSString *)searchQuery;

@end
