//
//  ACRTypeaheadSearchParameters.h
//  AdaptiveCards
//
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import "ACOAdaptiveCard.h"
#import "ACOBaseActionElement.h"
#import <Foundation/Foundation.h>

@protocol ACRITypeaheadSearchStateDelegate <NSObject>

@property NSString *_Nullable title;
@property NSString *_Nullable subtitle;

@end

@interface ACRTypeaheadStateParameters : NSObject <ACRITypeaheadSearchStateDelegate>
- (instancetype _Nullable)initWithtitle:(NSString *_Nullable)title
                               subtitle:(NSString *_Nullable)subtitle;

@end

@interface ACRTypeaheadOfflineStateParams : ACRTypeaheadStateParameters
@end

@interface ACRTypeaheadNoResultsStateParams : ACRTypeaheadStateParameters
@end

@interface ACRTypeaheadErrorStateParams : ACRTypeaheadStateParameters
@end

@interface ACRTypeaheadZeroStateParams : ACRTypeaheadStateParameters
@end

@interface ACRTypeaheadStateAllParameters : NSObject
@property ACRTypeaheadZeroStateParams *_Nullable zeroStateParams;
@property ACRTypeaheadErrorStateParams *_Nullable errorStateParams;
@property ACRTypeaheadNoResultsStateParams *_Nullable noResultStateParams;
@property ACRTypeaheadOfflineStateParams *_Nullable offlineStateParams;

- (nonnull instancetype)initWithzeroStateParams:(ACRTypeaheadZeroStateParams *_Nullable)zeroStateParams
                               errorStateParams:(ACRTypeaheadErrorStateParams *_Nullable)errorStateParams
                            noResultStateParams:(ACRTypeaheadNoResultsStateParams *_Nullable)noResultStateParams
                             offlineStateParams:(ACRTypeaheadOfflineStateParams *_Nullable)offlineStateParams;
@end
