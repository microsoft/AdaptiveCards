//
//  ACRHttpTarget
//  ACRHttpTarget.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRHttpTarget.h"
#import "ACRContentHoldingUIView.h"
#import "ACRIBaseInputHandler.h"
#import "ACRViewController.h"

@implementation ACRHttpTarget
{
    NSString *header;
    NSString *body;
    NSString *url;
    NSString *method;
    NSArray *_inputs;
    __weak UIViewController *_vc;
}

- (instancetype)initWithHttpAction:(std::shared_ptr<AdaptiveCards::HttpAction> const&)httpAction
                            inputs:(NSArray *)inputs
                                vc:(UIViewController *)vc
{
    self = [super init];
    if(self)
    {
        _vc = vc;
        _inputs = inputs;
        url = [NSString stringWithCString:httpAction->GetUrl().c_str() encoding:NSUTF8StringEncoding];
        body = [NSString stringWithCString:httpAction->GetBody().c_str() encoding:NSUTF8StringEncoding];
        method = [NSString stringWithCString:httpAction->GetMethod().c_str() encoding:NSUTF8StringEncoding];
    }
    return self;
}

- (NSString *)replaceMatchInString:(NSString *)string data:(NSDictionary *)data
{
    NSError *err = nil;
    NSString *pattern = [[@"\\{\\{(" stringByAppendingString:[[data allKeys] componentsJoinedByString:@"|"]] stringByAppendingString:@")\\.Value\\}\\}"];
    NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:pattern options:0 error:&err];
    NSMutableString *replacedString = [[NSMutableString alloc] init];
    __block NSRange prefix = NSMakeRange(0, [string length]);
    __block NSString *replacementString;
    __block BOOL matchFound = NO;

    [regex enumerateMatchesInString:string options:0 range:prefix usingBlock:^(NSTextCheckingResult * _Nullable result, NSMatchingFlags flags, BOOL * _Nonnull stop)
    {
        NSRange group0 = [result range];
        NSRange group1 = [result rangeAtIndex:1];

        prefix.length = group0.location - prefix.location;
        replacementString = [string substringWithRange:prefix];
        [replacedString appendString:replacementString];
        NSString *replacementString = [string substringWithRange:group1];
        if(data[replacementString])
        {
            [replacedString appendString:data[replacementString]];
        }
        prefix.location = group0.location + group0.length;
        matchFound = YES;
    }];

    if(matchFound == NO)
    {
        return string;
    }

    if(prefix.location < [string length])
    {
        replacementString = [string substringFromIndex:prefix.location];
        [replacedString appendString:replacementString];
    }

    return replacedString;
}

- (IBAction)create:(UIButton *)sender
{
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] init];
    NSError *err;

    for(id<ACRIBaseInputHandler> input in _inputs)
    {
        if([input validate:&err] == NO)
        {
            NSLog(@"input validation failed %@", err);
        }
        else
        {
            [input getInput:dictionary];
        }
    }

    NSString *replacedURL  = [self replaceMatchInString:url data:dictionary];
    NSString *replacedBody = [self replaceMatchInString:body data:dictionary];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:replacedURL]];
    request.HTTPMethod = method;
    request.HTTPBody   = [replacedBody dataUsingEncoding:NSUTF8StringEncoding];
    [((ACRViewController *)_vc).acrActionDelegate didFetchHttpRequest:request];
}

@end
