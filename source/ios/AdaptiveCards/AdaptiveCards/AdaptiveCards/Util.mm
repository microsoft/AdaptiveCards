//
//  Util
//  Util.mm
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import "BackgroundImage.h"
#import "Enums.h"
#import "ACRViewPrivate.h"
#import "ACRUIImageView.h"
#import "Util.h"

void configVisibility(UIView *view, const std::shared_ptr<AdaptiveCards::BaseCardElement>visibilityInfo)
{
    view.hidden = !(visibilityInfo->GetIsVisible());
    NSString *hashkey = [NSString stringWithCString:visibilityInfo->GetId().c_str() encoding:NSUTF8StringEncoding];
    view.tag = hashkey.hash;
}

void renderBackgroundImage(const AdaptiveCards::BackgroundImage *backgroundImage, UIView *containerView, ACRView *rootView)
{
    std::string imageUrl = backgroundImage->GetUrl();
    NSString *key = [NSString stringWithCString:imageUrl.c_str() encoding:[NSString defaultCStringEncoding]];
    if ([key length]) {
        UIImageView *imgView = nil;
        UIImage *img = [rootView getImageMap][key];
        if (img) {
            switch (backgroundImage->GetMode()) {
                case BackgroundImageMode::Repeat:
                case BackgroundImageMode::RepeatHorizontally:
                case BackgroundImageMode::RepeatVertically:
                    imgView = [[ACRUIImageView alloc] init];
                    imgView.backgroundColor = [UIColor colorWithPatternImage:img];
                    break;
                case BackgroundImageMode::Stretch:
                default:
                    imgView = [[ACRUIImageView alloc] initWithImage:img];
                    break;
            }
        } else {
            NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)backgroundImage];
            NSString *imageViewKey = [number stringValue];
            imgView = [rootView getImageView:imageViewKey];
        }
        
        if (imgView) {
            imgView.translatesAutoresizingMaskIntoConstraints = NO;
            [containerView addSubview:imgView];
            [containerView sendSubviewToBack:imgView];
            
            if (img) {
                // apply now if image is ready, otherwise wait until it is loaded (ACRView::observeValueForKeyPath)
                applyBackgroundImageConstraints(backgroundImage, imgView, img);
            }
            
            [imgView setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
            [imgView setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
            [imgView setContentCompressionResistancePriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
            [imgView setContentCompressionResistancePriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
        }
    }
}

void applyBackgroundImageConstraints(const BackgroundImage *backgroundImageProperties, UIImageView *imageView, UIImage *image)
{
    UIView *superView = [imageView superview];
    switch (backgroundImageProperties->GetMode()) {
        case BackgroundImageMode::Repeat:
        {
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeLeading multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTrailing relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeTrailing multiplier:1.0 constant:0].active = YES;
            
            imageView.contentMode = UIViewContentModeScaleAspectFill;
            break;
        }
        case BackgroundImageMode::RepeatHorizontally:
        {
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:image.size.height].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeLeading multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTrailing relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeTrailing multiplier:1.0 constant:0].active = YES;
            
            switch (backgroundImageProperties->GetVerticalAlignment())
            {
                case VerticalAlignment::Bottom:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
                    break;
                case VerticalAlignment::Center:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;
                    break;
                case VerticalAlignment::Top:
                default:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
                    break;
            }
            break;
        }
        case BackgroundImageMode::RepeatVertically:
        {
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:image.size.width].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
            switch (backgroundImageProperties->GetHorizontalAlignment())
            {
                case HorizontalAlignment::Right:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeRight multiplier:1.0 constant:0].active = YES;
                    break;
                case HorizontalAlignment::Center:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
                    break;
                case HorizontalAlignment::Left:
                default:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeLeft multiplier:1.0 constant:0].active = YES;
                    break;
            }
            break;
        }
        case BackgroundImageMode::Stretch:
        default:
        {
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeLeading multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTrailing relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeTrailing multiplier:1.0 constant:0].active = YES;
            
            imageView.contentMode = UIViewContentModeScaleAspectFill;
            break;
        }
    }
}
