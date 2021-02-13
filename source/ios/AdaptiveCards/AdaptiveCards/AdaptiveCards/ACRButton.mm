//
//  ACRButton
//  ACRButton.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRButton.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRUIImageView.h"
#import "ACRViewPrivate.h"

@implementation ACRButton

- (void)setImageView:(UIImage *)image withConfig:(ACOHostConfig *)config
{
    float imageHeight = 0.0f;
    CGSize contentSize = [self.titleLabel intrinsicContentSize];

    // apply explicit image size when the below condition is met
    if (_iconPlacement == ACRAboveTitle && config.allActionsHaveIcons) {
        imageHeight = [config getHostConfig] -> GetActions().iconSize;
    } else { // format the image so it fits in the button
        imageHeight = contentSize.height;
    }

    CGFloat widthToHeightRatio = 0.0f;
    if (image && image.size.height > 0) {
        widthToHeightRatio = image.size.width / image.size.height;
    }

    CGSize imageSize = CGSizeMake(imageHeight * widthToHeightRatio, imageHeight);
    _iconView.frame = CGRectMake(0, 0, imageSize.width, imageSize.height);
    _iconView.translatesAutoresizingMaskIntoConstraints = NO;

    // scale the image using UIImageView
    [NSLayoutConstraint constraintWithItem:_iconView
                                 attribute:NSLayoutAttributeWidth
                                 relatedBy:NSLayoutRelationEqual
                                    toItem:nil
                                 attribute:NSLayoutAttributeNotAnAttribute
                                multiplier:1.0
                                  constant:imageSize.width]
        .active = YES;

    [NSLayoutConstraint constraintWithItem:_iconView
                                 attribute:NSLayoutAttributeHeight
                                 relatedBy:NSLayoutRelationEqual
                                    toItem:nil
                                 attribute:NSLayoutAttributeNotAnAttribute
                                multiplier:1.0
                                  constant:imageSize.height]
        .active = YES;

    if (_iconPlacement == ACRAboveTitle && config.allActionsHaveIcons) {
        // fix image view to top and center x of the button
        [NSLayoutConstraint constraintWithItem:_iconView
                                     attribute:NSLayoutAttributeTop
                                     relatedBy:NSLayoutRelationEqual
                                        toItem:self
                                     attribute:NSLayoutAttributeTop
                                    multiplier:1.0
                                      constant:config.buttonPadding]
            .active = YES;
        [NSLayoutConstraint constraintWithItem:_iconView
                                     attribute:NSLayoutAttributeCenterX
                                     relatedBy:NSLayoutRelationEqual
                                        toItem:self
                                     attribute:NSLayoutAttributeCenterX
                                    multiplier:1.0
                                      constant:0]
            .active = YES;
        // image can't be postion at the top of the title, so adjust title inset edges
        [self setTitleEdgeInsets:UIEdgeInsetsMake(imageHeight, 0, -imageHeight, 0)];
        // readjust content edge, so intrinsic content size can be accurately determined by system library, and give enough room for title and image icon
        [self setContentEdgeInsets:UIEdgeInsetsMake(config.buttonPadding, config.buttonPadding + self.layer.cornerRadius, config.buttonPadding + imageHeight, config.buttonPadding + self.layer.cornerRadius)];
        // configure button frame to correct size; in case translatesAutoresizingMaskIntoConstraints is used
        self.frame = CGRectMake(0, 0, MAX(imageSize.width, contentSize.width), imageSize.height + config.buttonPadding);
    } else if (_iconPlacement != ACRNoTitle) {
        int iconPadding = [config getHostConfig] -> GetSpacing().defaultSpacing;
        [self setTitleEdgeInsets:UIEdgeInsetsMake(config.buttonPadding, (imageSize.width) + iconPadding, config.buttonPadding, -(iconPadding + imageSize.width))];
        [self setContentEdgeInsets:UIEdgeInsetsMake(config.buttonPadding, config.buttonPadding, config.buttonPadding, imageSize.width + iconPadding + self.layer.cornerRadius)];
        [NSLayoutConstraint constraintWithItem:_iconView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeLeft multiplier:1.0 constant:config.buttonPadding].active = YES;
        [NSLayoutConstraint constraintWithItem:_iconView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:self attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;
        self.frame = CGRectMake(0, 0, imageSize.width + config.buttonPadding + contentSize.width, MAX(imageSize.height, contentSize.height));
        // update action set view that hold buttons and buttons' layout view
        [self.superview.superview setNeedsLayout];
    }
}

+ (UIButton *)rootView:(ACRView *)rootView
     baseActionElement:(ACOBaseActionElement *)acoAction
                 title:(NSString *)title
         andHostConfig:(ACOHostConfig *)config;
{
    NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
    ACRButton *button = [bundle loadNibNamed:@"ACRButton" owner:rootView options:nil][0];
    [button setTitle:title forState:UIControlStateNormal];
    button.titleLabel.adjustsFontSizeToFitWidth = NO;
    button.isAccessibilityElement = YES;
    button.accessibilityLabel = title;

    button.sentiment = acoAction.sentiment;

    button.defaultPositiveBackgroundColor = [config getTextBlockColor:(ACRContainerStyle::ACRDefault) textColor:(ForegroundColor::Accent)subtleOption:false];
    button.defaultDestructiveForegroundColor = [config getTextBlockColor:(ACRContainerStyle::ACRDefault) textColor:(ForegroundColor::Attention)subtleOption:false];
    [button applySentimentStyling];
    button.iconPlacement = [config getIconPlacement];

    std::shared_ptr<AdaptiveCards::BaseActionElement> action = [acoAction element];
    NSDictionary *imageViewMap = [rootView getImageMap];
    NSString *key = [NSString stringWithCString:action->GetIconUrl().c_str() encoding:[NSString defaultCStringEncoding]];
    UIImage *img = imageViewMap[key];

    if (img) {
        UIImageView *iconView = [[ACRUIImageView alloc] init];
        iconView.image = img;
        [button addSubview:iconView];
        button.iconView = iconView;
        [button setImageView:img withConfig:config];

    } else if (key.length) {
        NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)action.get()];
        NSString *key = [number stringValue];
        UIImageView *view = [rootView getImageView:key];
        if (view) {
            if (view.image) {
                button.iconView = view;
                [button addSubview:view];
                [button setImageView:view.image withConfig:config];
            } else {
                button.iconView = view;
                [button addSubview:view];
                [rootView setImageView:key view:button];
            }
        }
    } else {
        // button's intrinsic content size is determined by title size and content edge
        // add corner radius to content size by adding it to content edge inset
        [button setContentEdgeInsets:UIEdgeInsetsMake(config.buttonPadding, config.buttonPadding + button.layer.cornerRadius, config.buttonPadding, config.buttonPadding + button.layer.cornerRadius)];
    }

    return button;
}

- (void)applySentimentStyling
{
    if ([@"positive" caseInsensitiveCompare:_sentiment] == NSOrderedSame) {
        BOOL usePositiveDefault = [_positiveUseDefault boolValue];

        // By default, positive sentiment must have background accentColor and white text/foreground color
        if (usePositiveDefault) {
            [self setBackgroundColor:_defaultPositiveBackgroundColor];
            [self setTitleColor:UIColor.whiteColor forState:UIControlStateNormal];
        } else {
            // Otherwise use the values defined by the user in the ACRButton.xib
            [self setBackgroundColor:_positiveBackgroundColor];
            [self setTitleColor:_positiveForegroundColor forState:UIControlStateNormal];
        }
    } else if ([@"destructive" caseInsensitiveCompare:_sentiment] == NSOrderedSame) {
        BOOL useDestructiveDefault = [_destructiveUseDefault boolValue];

        // By default, destructive sentiment must have a attention text/foreground color
        if (useDestructiveDefault) {
            [self setTitleColor:_defaultDestructiveForegroundColor forState:UIControlStateNormal];
        } else {
            // Otherwise use the values defined by the user in the ACRButton.xib
            [self setBackgroundColor:_destructiveBackgroundColor];
            [self setTitleColor:_destructiveForegroundColor forState:UIControlStateNormal];
        }
    }
}

@end
