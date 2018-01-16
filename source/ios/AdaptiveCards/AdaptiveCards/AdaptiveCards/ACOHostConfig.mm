//
//  ACRHostConfig.mm
//  ACRHostConfig.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "ACOHostConfig.h"
#import "HostConfig.h"
#import "AdaptiveCardParseException.h"
#import "ACRErrors.h"

using namespace AdaptiveCards;

@implementation ACOHostConfig
{
    std::shared_ptr<HostConfig> _config;
}

- (instancetype)init
{
    self = [super init];
    _config = std::make_shared<HostConfig>();
    return self;
}

+ (ACOHostConfigParseResult *)fromJson:(NSString *)payload;
{
    ACOHostConfigParseResult *result = nil;

    if(payload)
    {
        try
        {
            ACOHostConfig *config= [[ACOHostConfig alloc] init];
            *config->_config.get() = AdaptiveCards::HostConfig::DeserializeFromString(std::string([payload UTF8String]));
            result = [[ACOHostConfigParseResult alloc] init:config errors:nil];
        }
        catch(const AdaptiveCardParseException& e)
        {
            // converts AdaptiveCardParseException to NSError
            ErrorStatusCode errorStatusCode = e.GetStatusCode();
            NSInteger errorCode = (long)errorStatusCode;
            NSString *errorMessage= [NSString stringWithCString:e.GetMessage().c_str()
                                                       encoding:[NSString defaultCStringEncoding]];
            NSString *localizedDescription = NSLocalizedString(errorMessage, @"");
            NSError *parseError = [NSError errorWithDomain:ACRParseErrorDomain
                                                      code:errorCode
                                                  userInfo:@{NSLocalizedFailureReasonErrorKey:localizedDescription}];
            NSArray<NSError *> *errors = @[parseError];
            result = [[ACOHostConfigParseResult alloc] init:nil errors:errors];
        }
    }
    return result;
}

- (std::shared_ptr<HostConfig>)getHostConfig
{
    return _config;
}

- (void)setHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    _config = config;
}

@end
