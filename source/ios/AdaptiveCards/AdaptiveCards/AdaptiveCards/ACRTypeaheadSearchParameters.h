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

@property (nonatomic, retain, nullable) NSString *title;
@property (nonatomic, retain, nullable) NSString *subtitle;

@end

@interface ACRTypeaheadStateParameters : NSObject <ACRITypeaheadSearchStateDelegate>
- (nonnull instancetype)initWithtitle:(nullable NSString *)title
                              subtitle:(nullable NSString *)subtitle;

@end

@interface ACRTypeaheadOfflineStateParams: ACRTypeaheadStateParameters
@end

@interface ACRTypeaheadNoResultsStateParams: ACRTypeaheadStateParameters
@end

@interface ACRTypeaheadErrorStateParams: ACRTypeaheadStateParameters
@end

@interface ACRTypeaheadZeroStateParams: ACRTypeaheadStateParameters
@end

@interface ACRTypeaheadStateAllParameters : NSObject
@property (nonatomic, nonnull) ACRTypeaheadZeroStateParams *zeroStateParams;
@property (nonatomic, nonnull) ACRTypeaheadErrorStateParams *errorStateParams;
@property (nonatomic, nonnull) ACRTypeaheadNoResultsStateParams *noResultStateParams;
@property (nonatomic, nonnull) ACRTypeaheadOfflineStateParams *offlineStateParams;

- (nonnull instancetype)initWithzeroStateParams:(nullable ACRTypeaheadZeroStateParams *)zeroStateParams
                               errorStateParams:(nullable ACRTypeaheadErrorStateParams *)errorStateParams
                            noResultStateParams:(nullable ACRTypeaheadNoResultsStateParams *)noResultStateParams
                             offlineStateParams:(nullable ACRTypeaheadOfflineStateParams *)offlineStateParams;
@end
