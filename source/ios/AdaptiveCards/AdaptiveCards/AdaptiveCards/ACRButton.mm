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
<<<<<<< HEAD
=======

+ (void)setImageView:(UIImage*)image inButton:(UIButton*)button withConfig:(ACOHostConfig *)config
{
    float imageHeight = 0.0f;
    IconPlacement iconPlacement = [config getHostConfig]->actions.iconPlacement;
    CGSize contentSize = [button.titleLabel intrinsicContentSize];

    // apply explicit image size when the below condition is met
    if(iconPlacement == AdaptiveCards::IconPlacement::AboveTitle && config.allActionsHaveIcons) {
        imageHeight = [config getHostConfig]->actions.iconSize;
    } else { // format the image so it fits in the button
        imageHeight = contentSize.height;
    }

    CGFloat widthToHeightRatio = 0.0f;
    if(image && image.size.height > 0) {
        widthToHeightRatio = image.size.width / image.size.height;
    }

    CGSize imageSize = CGSizeMake(imageHeight * widthToHeightRatio, imageHeight);

    ACRUIImageView *imageView = [[ACRUIImageView alloc] initWithFrame:CGRectMake(0, 0, imageSize.width, imageSize.height)];
    imageView.translatesAutoresizingMaskIntoConstraints = NO;
    imageView.image = image;
    [button addSubview:imageView];
    // scale the image using UIImageView
    [NSLayoutConstraint constraintWithItem:imageView
                                 attribute:NSLayoutAttributeWidth
                                 relatedBy:NSLayoutRelationEqual
                                    toItem:nil
                                 attribute:NSLayoutAttributeNotAnAttribute
                                multiplier:1.0
                                  constant:imageSize.width].active = YES;

    [NSLayoutConstraint constraintWithItem:imageView
                                 attribute:NSLayoutAttributeHeight
                                 relatedBy:NSLayoutRelationEqual
                                    toItem:nil
                                 attribute:NSLayoutAttributeNotAnAttribute
                                multiplier:1.0
                                  constant:imageSize.height].active = YES;

    if(iconPlacement == AdaptiveCards::IconPlacement::AboveTitle && config.allActionsHaveIcons) {
        // fix image view to top and center x of the button
        [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:button
            attribute:NSLayoutAttributeTop multiplier:1.0 constant:config.buttonPadding].active = YES;
        [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:button
            attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
        // image can't be postion at the top of the title, so adjust title inset edges
        [button setTitleEdgeInsets:UIEdgeInsetsMake(imageHeight, 0, -imageHeight, 0)];
        // readjust content edge, so intrinsic content size can be accurately determined by system library, and give enough room for title and image icon
        [button setContentEdgeInsets:UIEdgeInsetsMake(config.buttonPadding, config.buttonPadding + button.layer.cornerRadius, config.buttonPadding + imageHeight, config.buttonPadding + button.layer.cornerRadius)];
        // configure button frame to correct size; in case translatesAutoresizingMaskIntoConstraints is used
        button.frame = CGRectMake(0, 0, MAX(imageSize.width, contentSize.width), imageSize.height + config.buttonPadding);
    } else {
        int iconPadding = [config getHostConfig]->spacing.defaultSpacing;
        [button setTitleEdgeInsets:UIEdgeInsetsMake(config.buttonPadding, (imageSize.width) + iconPadding, config.buttonPadding, -(iconPadding + imageSize.width))];
        [button setContentEdgeInsets:UIEdgeInsetsMake(config.buttonPadding, config.buttonPadding, config.buttonPadding, imageSize.width + iconPadding + button.layer.cornerRadius)];
        [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:button attribute:NSLayoutAttributeLeft multiplier:1.0 constant:config.buttonPadding].active = YES;
        [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:button attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;
        button.frame = CGRectMake(0, 0, imageSize.width + config.buttonPadding + contentSize.width, MAX(imageSize.height, contentSize.height));
    }
}

>>>>>>> master
+ (UIButton* )rootView:(ACRView *)rootView
     baseActionElement:(ACOBaseActionElement *)acoAction
                 title:(NSString *)title
               iconUrl:(NSString *)iconUrl
         andHostConfig:(ACOHostConfig *)config;
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
