//
//  ACOAuthentication
//  ACOAuthentication.mm
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACOAuthCardButtonPrivate.h"
#import "ACOAuthenticationPrivate.h"
#import "ACOTokenExchangeResourcePrivate.h"

@implementation ACOAuthentication {
    std::shared_ptr<Authentication> _adaptiveAuthentication;
}

- (instancetype)init:(std::shared_ptr<Authentication> const &)adaptiveAuthentication;
{
    self = [super init];
    if (self && adaptiveAuthentication) {
        _adaptiveAuthentication = adaptiveAuthentication;

        self.text = [NSString stringWithCString:adaptiveAuthentication->GetText().c_str() encoding:NSUTF8StringEncoding];
        self.connectionName = [NSString stringWithCString:adaptiveAuthentication->GetConnectionName().c_str() encoding:NSUTF8StringEncoding];
        self.tokenExchangeResource = [[ACOTokenExchangeResource alloc] init:adaptiveAuthentication->GetTokenExchangeResource()];

        NSMutableArray<ACOAuthCardButton *> *buttons = [NSMutableArray array];
        for (const auto &button : adaptiveAuthentication->GetButtons()) {
            [buttons addObject:[[ACOAuthCardButton alloc] init:button]];
        }

        self.buttons = [NSArray arrayWithArray:buttons];
    }
    return self;
}

- (instancetype)init:(NSString *)text connectionName:(NSString *)connectionName tokenExchangeResource:(ACOTokenExchangeResource *)tokenExchangeResource buttons:(NSArray<ACOAuthCardButton *> *)buttons
{
    std::string ctext, cconnectionName;
    if (text) {
        ctext = [text UTF8String];
    }

    if (connectionName) {
        cconnectionName = [connectionName UTF8String];
    }

    std::shared_ptr<TokenExchangeResource> tokenExchangeResourcePtr = nullptr;
    if (tokenExchangeResource && tokenExchangeResource.adaptiveTokenExchangeResource) {
        tokenExchangeResourcePtr = std::make_shared<TokenExchangeResource>(*tokenExchangeResource.adaptiveTokenExchangeResource);
    }

    std::vector<std::shared_ptr<AuthCardButton>> adaptiveButtons;
    if (buttons) {
        for (ACOAuthCardButton *button in buttons) {
            if (button.adaptiveButton) {
                adaptiveButtons.push_back(std::make_shared<AuthCardButton>(*button.adaptiveButton));
            }
        }
    }

    return [self init:std::make_shared<Authentication>(ctext, cconnectionName, tokenExchangeResourcePtr, adaptiveButtons)];
}

- (instancetype)init
{
    return [self init:nil];
}

@end
