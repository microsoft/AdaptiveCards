//
//  ACRTypeaheadSearchParameters.mm
//  AdaptiveCards
//
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import "ACRTypeaheadSearchParameters.h"


@implementation ACRTypeaheadStateParameters

- (instancetype)initWithtitle:(NSString *)title
                     subtitle:(NSString *)subtitle
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

- (instancetype)initWithtitle:(NSString *)title
                     subtitle:(NSString *)subtitle
{
    self = [super init];
    if (self) {
        if (!title) {
            title = @"No Internet";
        }
        self = [super initWithtitle:title subtitle:subtitle];
    }
    return self;
}

@end

@implementation ACRTypeaheadNoResultsStateParams

- (instancetype)initWithtitle:(NSString *)title
                     subtitle:(NSString *)subtitle
{
    self = [super init];
    if (self) {
        if (!title) {
            title = @"No results found";
        }
        self = [super initWithtitle:title subtitle:subtitle];
    }
    return self;
}

@end

@implementation ACRTypeaheadErrorStateParams

- (instancetype)initWithtitle:(NSString *)title
                     subtitle:(NSString *)subtitle
{
    self = [super init];
    if (self) {
        if (!title) {
            title = @"Something went wrong";
        }
        self = [super initWithtitle:title subtitle:subtitle];
    }
    return self;
}
@end

@implementation ACRTypeaheadZeroStateParams

- (instancetype)initWithtitle:(NSString *)title
                     subtitle:(NSString *)subtitle
{
    self = [super init];
    if (self) {
        if (!title) {
            title = @"Search options";
        }
        self = [super initWithtitle:title subtitle:subtitle];
    }
    return self;
}
@end

@implementation ACRTypeaheadStateAllParameters

- (nonnull instancetype)initWithzeroStateParams:(ACRTypeaheadZeroStateParams *)zeroStateParams
                               errorStateParams:(ACRTypeaheadErrorStateParams *)errorStateParams
                            noResultStateParams:(ACRTypeaheadNoResultsStateParams *)noResultStateParams
                             offlineStateParams:(ACRTypeaheadOfflineStateParams *)offlineStateParams
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
