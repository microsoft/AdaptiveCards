//
//  ACOTypeaheadSearchHandler.h
//  AdaptiveCards
//
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
    zeroState = 0,
    searchInProgress,
    displayingGenericError,
    displayingInvalidSearchError,
    displayingResults,
} TSTypeaehadSearchViewState;

@protocol ACRTypeaheadSearchProtocol <NSObject>
- (void)updateTypeaheadUIWithSearchText:(NSString *)searchText dynamicChoices:(NSDictionary *)response withError:(NSError *)error;
@end
