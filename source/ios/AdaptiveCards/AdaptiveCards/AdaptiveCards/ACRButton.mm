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
         andHostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const &)config;
{
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    [button setTitle:title forState:UIControlStateNormal];
    [button setTitleColor:UIColor.whiteColor forState:UIControlStateNormal];
    [button setBackgroundColor:[UIColor colorWithRed:0.0
                                               green:122.0/255.0
                                                blue:1.0
                                               alpha:1.0]];

    CGSize contentSize = [button.titleLabel intrinsicContentSize];
    [button setFrame:CGRectMake(0, 0, contentSize.width, contentSize.height)];
    [button setContentEdgeInsets:UIEdgeInsetsMake(5,5,5,5)];
    
    std::shared_ptr<AdaptiveCards::BaseActionElement> action = [acoAction element];
    if( [iconUrl length] != 0 ){
        NSMutableDictionary *actionsViewMap = [rootView getActionsMap];
        __block UIImageView *imgView = nil;
        // Generate key for ImageViewMap
        NSString *key = [NSString stringWithCString:action->GetId().c_str() encoding:[NSString defaultCStringEncoding]];
        // Syncronize access to imageViewMap
        dispatch_sync([rootView getSerialQueue], ^{
            // if imageView is available, get it, otherwise cache UIButton, so it can be used once images are ready
            if(actionsViewMap[key] && [actionsViewMap[key] isKindOfClass:[UIImageView class]]) {
                imgView = actionsViewMap[key];
            }
            else {
                actionsViewMap[key] = button;
            }
        });
        
        if(imgView){
            // Format the image so it fits in the button and is placed where it must be placed
            CGSize contentSize = [button.titleLabel intrinsicContentSize];
            double imageHeight = contentSize.height;
            CGSize originalImageSize = [imgView intrinsicContentSize];
            double scaleRatio = imageHeight / originalImageSize.height;
            double imageWidth = scaleRatio * originalImageSize.width;
            
            IconPlacement iconPlacement = config->actions.iconPlacement;
            if( iconPlacement == AdaptiveCards::IconPlacement::AboveTitle ){
                [imgView setFrame:CGRectMake( (button.frame.size.width - imageWidth) / 2, 5, imageWidth, imageHeight)];
                [button setTitleEdgeInsets:UIEdgeInsetsMake(imageHeight, 5, -imageHeight, 5)];
                [button setContentEdgeInsets:UIEdgeInsetsMake(5, 5, 5 + imageHeight, 5)];
            } else {
                int iconPadding = config->spacing.defaultSpacing;
                [button setTitleEdgeInsets:UIEdgeInsetsMake(5, (iconPadding + imageWidth), 5, 0)];
                double titleOriginX = button.titleLabel.frame.origin.x;
                [imgView setFrame:CGRectMake( titleOriginX - (iconPadding + imageWidth) / 2, 5, imageWidth, imageHeight)];
            }
            [button addSubview:imgView];
            
            // remove postfix added for imageMap access
            std::string id = action->GetId();
            std::size_t idx = id.find_last_of('_');
            action->SetId(id.substr(0, idx));
        }
        
    }
    
    return button;
}
@end
