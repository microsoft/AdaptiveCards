//
//  ACROpenURLTarget
//  ACROpenURLTarget.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACROpenURLTarget.h"
#import <SafariServices/SafariServices.h>

@implementation ACROpenURLTarget
{
    __weak UIViewController *_vc;
    // view where this action is being executed
    NSURL *_url;
}

- (instancetype)initWithURL:(NSURL *)url viewController:(UIViewController *)vc
{
    self = [super init];
    if(self)
    {
        _vc = vc;
        _url = url;
    }
    return self;
}
- (IBAction)openURL
{
    SFSafariViewController *svc = [[SFSafariViewController alloc] initWithURL:_url];
    [_vc presentViewController:svc animated:YES completion:nil];
}

- (void) doSelectAction
{
    [self openURL];
}
@end
