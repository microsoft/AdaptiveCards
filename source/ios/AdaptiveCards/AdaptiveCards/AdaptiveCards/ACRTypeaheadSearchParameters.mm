//
//  ACRChoiceSetTypeaheadSearchStateParams.cpp
//  AdaptiveCards
//
//  Created by Jyoti Kukreja on 12/01/23.
//  Copyright © 2023 Microsoft. All rights reserved.
//

#include "ACRTypeaheadSearchParameters.h"


@implementation ACRTypeaheadStateParameters

- (instancetype)initWithtitle:(nullable NSString *)title
                     subtitle:(nullable NSString *)subtitle
{
    self = [super init];
    if (self) {
        self.title = title;
        self.subtitle = subtitle;
    }
    return self;
}

@synthesize title;
@synthesize subtitle;

@end

@implementation ACRTypeaheadOfflineStateParams

- (instancetype)initWithtitle:(nullable NSString *)title
                     subtitle:(nullable NSString *)subtitle
{
    self = [super init];
    if (self) {
        if(!title)
        {
            title = @"No Internet";
        }
        self = [super initWithtitle:title subtitle:subtitle];
    }
    return self;
}

@end

@implementation ACRTypeaheadNoResultsStateParams

- (instancetype)initWithtitle:(nullable NSString *)title
                     subtitle:(nullable NSString *)subtitle
{
    self = [super init];
    if (self) {
        if(!title)
        {
            title = @"No results found";
        }
        self = [super initWithtitle:title subtitle:subtitle];
    }
    return self;
}

@end

@implementation ACRTypeaheadErrorStateParams

- (instancetype)initWithtitle:(nullable NSString *)title
                     subtitle:(nullable NSString *)subtitle
{
    self = [super init];
    if (self) {
        if(!title)
        {
            title = @"Something went wrong";
        }
        self = [super initWithtitle:title subtitle:subtitle];
    }
    return self;
}
@end

@implementation ACRTypeaheadZeroStateParams

- (instancetype)initWithtitle:(nullable NSString *)title
                     subtitle:(nullable NSString *)subtitle
{
    self = [super init];
    if (self) {
        if(!title)
        {
            title = @"Search options";
        }
        self = [super initWithtitle:title subtitle:subtitle];
    }
    return self;
}
@end

@implementation ACRTypeaheadStateAllParameters

- (nonnull instancetype)initWithzeroStateParams:(nullable ACRTypeaheadZeroStateParams *)zeroStateParams
                               errorStateParams:(nullable ACRTypeaheadErrorStateParams *)errorStateParams
                            noResultStateParams:(nullable ACRTypeaheadNoResultsStateParams *)noResultStateParams
                             offlineStateParams:(nullable ACRTypeaheadOfflineStateParams *)offlineStateParams
{
    self = [super init];
    if (self) {
        self.zeroStateParams = zeroStateParams;
        self.errorStateParams = errorStateParams;
        self.noResultStateParams = noResultStateParams;
        self.offlineStateParams = offlineStateParams;
    }
    return self;
}

@end
