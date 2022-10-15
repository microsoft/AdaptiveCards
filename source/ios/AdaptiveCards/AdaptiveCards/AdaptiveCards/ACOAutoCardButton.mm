//
//  ACOAuthCardButton
//  ACOAuthCardButton.mm
//
//  Copyright © 2021 Microsoft. All rights reserved.
//
//
//
//
#import "ACOAuthCardButtonPrivate.h"

@implementation ACOAuthCardButton {
    std::shared_ptr<AuthCardButton> _adaptiveAuthCardButton;
}

- (instancetype)init:(std::shared_ptr<AuthCardButton> const &)adaptiveAuthCardButton;
{
    self = [super init];
    if (self && adaptiveAuthCardButton) {
        _adaptiveAuthCardButton = adaptiveAuthCardButton;

        self.type = [NSString stringWithCString:adaptiveAuthCardButton->GetType().c_str() encoding:NSUTF8StringEncoding];
        self.title = [NSString stringWithCString:adaptiveAuthCardButton->GetTitle().c_str() encoding:NSUTF8StringEncoding];
        self.image = [NSString stringWithCString:adaptiveAuthCardButton->GetImage().c_str() encoding:NSUTF8StringEncoding];
        self.value = [NSString stringWithCString:adaptiveAuthCardButton->GetValue().c_str() encoding:NSUTF8StringEncoding];
    }
    return self;
}

- (instancetype)init:(NSString *)type title:(NSString *)title image:(NSString *)image value:(NSString *)value
{
    std::string ctype, ctitle, cimage, cvalue;
    if (type) {
        ctype = [type UTF8String];
    }

    if (title) {
        ctitle = [title UTF8String];
    }

    if (image) {
        cimage = [image UTF8String];
    }

    if (value) {
        cvalue = [value UTF8String];
    }

    return [self init:std::make_shared<AuthCardButton>(ctype, ctitle, cimage, cvalue)];
}

- (instancetype)init
{
    return [self init:nil];
}

- (std::shared_ptr<AuthCardButton> const &)adaptiveButton
{
    return _adaptiveAuthCardButton;
}

@end
