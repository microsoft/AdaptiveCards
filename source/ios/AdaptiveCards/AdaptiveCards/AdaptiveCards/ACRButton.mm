//
//  ACRButton
//  ACRButton.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRButton.h"

@implementation UIButton(ACRButton)
+ (UIButton* )acr_renderButton:(UIView *)view
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
    
    if( [iconUrl length] != 0 ){
        // Format the image so it looks pretty
        NSData *imageData = [[NSData alloc] initWithContentsOfURL: [NSURL URLWithString: @"https://i.imgur.com/95qFPCV.jpg"]];
        UIImage *image = [UIImage imageWithData: imageData];

        double imageHeight = contentSize.height;
        CGSize originalImageSize = [image size];
        double scaleRatio = imageHeight / originalImageSize.height;
        double imageWidth = scaleRatio * originalImageSize.width;
        
        UIImage *scaledImage = [self scaleImage:image toSize:CGSizeMake(imageWidth, imageHeight)];
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
        
    }
    
    return button;
}

+ (UIImage*)scaleImage:(UIImage *)image toSize:(CGSize)newSize {
    //UIGraphicsBeginImageContext(newSize);
    // In next line, pass 0.0 to use the current device's pixel scaling factor (and thus account for Retina resolution).
    // Pass 1.0 to force exact pixel size.
    UIGraphicsBeginImageContextWithOptions(newSize, NO, 0.0);
    [image drawInRect:CGRectMake(0, 0, newSize.width, newSize.height)];
    UIImage *scaledImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return scaledImage;
}
@end
