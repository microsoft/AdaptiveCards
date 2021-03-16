//
//  ACOAuthentication
//  ACOAuthentication.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACOAuthCardButton.h"
#import "ACOTokenExchangeResource.h"
#import <Foundation/Foundation.h>

@interface ACOAuthentication : NSObject

@property NSString *text;
@property NSString *connectionName;
@property ACOTokenExchangeResource *tokenExchangeResource;
@property NSArray<ACOAuthCardButton *> *buttons;

- (instancetype)init:(NSString *)text connectionName:(NSString *)connectionName tokenExchangeResource:(ACOTokenExchangeResource *)tokenExchangeResource buttons:(NSArray<ACOAuthCardButton *> *)buttons;

@end
