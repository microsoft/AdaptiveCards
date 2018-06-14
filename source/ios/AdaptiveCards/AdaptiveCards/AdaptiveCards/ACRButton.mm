//
//  ACRButton
//  ACRButton.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOBaseActionElementPrivate.h"
#import "ACRButton.h"
#import "ACRView.h"

@implementation UIButton(ACRButton)

+ (UIButton* )rootView:(ACRView *)rootView
     baseActionElement:(ACOBaseActionElement *)acoAction
                 title:(NSString *)title
               iconUrl:(NSString *)iconUrl
         andHostConfig:(ACOHostConfig *)config;
{
    NSBundle* bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
    UIButton *button = [bundle loadNibNamed:@"ACRButton" owner:rootView options:nil][0];
    [button setTitle:title forState:UIControlStateNormal];

    CGSize contentSize = [button.titleLabel intrinsicContentSize];
    [button setFrame:CGRectMake(0, 0, contentSize.width, contentSize.height)];

    std::shared_ptr<AdaptiveCards::BaseActionElement> action = [acoAction element];
    if([iconUrl length] != 0)
    {
        NSMutableDictionary *actionsViewMap = [rootView getActionsMap];
        __block UIImageView *imgView = nil;
        // Generate key for ImageViewMap
        NSString *key = [NSString stringWithCString:action->GetId().c_str() encoding:[NSString defaultCStringEncoding]];
        // Syncronize access to imageViewMap
        dispatch_sync([rootView getSerialQueue], ^{
            // if imageView is available, get it, otherwise cache UIButton, so it can be used once images are ready
            if(actionsViewMap[key] && [actionsViewMap[key] isKindOfClass:[UIImageView class]])
            {
                imgView = actionsViewMap[key];
            }
            else
            {
                actionsViewMap[key] = button;
            }
        });

        if(imgView)
        {
            [ACRView setImageView:imgView inButton:button withConfig:config];

            // remove postfix added for imageMap access
            std::string id = action->GetId();
            std::size_t idx = id.find_last_of('_');
            action->SetId(id.substr(0, idx));
        }
    }

    return button;
}
@end
