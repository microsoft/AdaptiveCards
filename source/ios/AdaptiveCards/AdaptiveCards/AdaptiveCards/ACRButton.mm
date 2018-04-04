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
        __block UIImage *img = nil;
        // Generate key for ImageViewMap
        NSString *key = [NSString stringWithCString:action->GetId().c_str() encoding:[NSString defaultCStringEncoding]];
        // Syncronize access to imageViewMap
        dispatch_sync([rootView getSerialQueue], ^{
            // if image is available, get it, otherwise cache UIButton, so it can be used once images are ready
            if(actionsViewMap[key] && [actionsViewMap[key] isKindOfClass:[UIImage class]]) {
                img = actionsViewMap[key];
            }
            else {
                actionsViewMap[key] = button;
            }
        });
        
        if(img){
            // Format the image so it fits in the button and is placed where it must be placed
            double imageHeight = contentSize.height;
            CGSize originalImageSize = [img size];
            double scaleRatio = imageHeight / originalImageSize.height;
            double imageWidth = scaleRatio * originalImageSize.width;
            
            UIImage *scaledImage = [rootView scaleImage:img toSize:CGSizeMake(imageWidth, imageHeight)];
            [button setImage:scaledImage forState:UIControlStateNormal];
            
            AdaptiveCards::IconPlacement iconPlacement = config->actions.iconPlacement;
            if( iconPlacement == AdaptiveCards::IconPlacement::AboveTitle ){
                // Changes the insets for image, title and contents so the icon is rendered above the title
                CGFloat totalHeight = (imageHeight + contentSize.height);
                [button setImageEdgeInsets:UIEdgeInsetsMake(-(totalHeight - 2 * imageHeight), 0.0f, 0.0f, -contentSize.width)];
                [button setTitleEdgeInsets:UIEdgeInsetsMake(imageHeight, -imageWidth, - (totalHeight - contentSize.height), 0.0f)];
                [button setContentEdgeInsets:UIEdgeInsetsMake(5, 5, 5 + imageHeight, 5)];
            } else {
                // The icons are drawn to the left of the title by default, so we only set the padding to the right for the image
                int iconPadding = config->spacing.defaultSpacing;
                [button setImageEdgeInsets:UIEdgeInsetsMake(0, 0, 0, iconPadding)];
            }
            
            // remove postfix added for imageMap access
            std::string id = action->GetId();
            std::size_t idx = id.find_last_of('_');
            action->SetId(id.substr(0, idx));
        }
        
    }
    
    return button;
}
@end
