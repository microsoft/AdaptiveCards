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

void renderBackgroundImageView(const AdaptiveCards::BackgroundImage *backgroundImageProperties, UIView *containerView, ACRView *rootView)
{
    std::string imageUrl = "";
    if((backgroundImageProperties != nullptr) && !(backgroundImageProperties->GetUrl().empty())) {
        imageUrl = backgroundImageProperties->GetUrl();
    }
    
    NSString *key = [NSString stringWithCString:imageUrl.c_str() encoding:[NSString defaultCStringEncoding]];
    if ([key length]) {
        UIImageView *imgView = nil;
        UIImage *img = nil;
        img = [rootView getImageMap][key];
        if (img) {
            if (backgroundImageProperties->GetMode() == BackgroundImageMode::Stretch) {
                imgView = [[ACRUIImageView alloc] initWithImage:img];
            } else {
                imgView = [[ACRUIImageView alloc] init];
                imgView.backgroundColor = [UIColor colorWithPatternImage:img];
            }
        } else {
            NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)backgroundImageProperties];
            NSString *imageViewKey = [number stringValue];
            imgView = [rootView getImageView:imageViewKey];
        }
        
        if (imgView) {
            imgView.translatesAutoresizingMaskIntoConstraints = NO;
            [containerView addSubview:imgView];
            [containerView sendSubviewToBack:imgView];
            
            applyBackgroundImageConstraints(backgroundImageProperties, imgView);
            
            [imgView setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
            [imgView setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
            [imgView setContentCompressionResistancePriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
            [imgView setContentCompressionResistancePriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
        }
    }
}

void applyBackgroundImageConstraints(const BackgroundImage *backgroundImageProperties, UIImageView *imageView)
{
    UIView *parentView = [imageView superview];
    UIImage *image = [imageView image];
    switch (backgroundImageProperties->GetMode()) {
        case BackgroundImageMode::Repeat:
        {
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeLeading multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTrailing relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeTrailing multiplier:1.0 constant:0].active = YES;
            
            imageView.contentMode = UIViewContentModeScaleAspectFill;
            break;
        }
        case BackgroundImageMode::RepeatHorizontally:
        {
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:image.size.height].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeLeading multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTrailing relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeTrailing multiplier:1.0 constant:0].active = YES;
            
            switch (backgroundImageProperties->GetVerticalAlignment())
            {
                case VerticalAlignment::Bottom:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
                    break;
                case VerticalAlignment::Center:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;
                    break;
                case VerticalAlignment::Top:
                default:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
                    break;
            }
            break;
        }
        case BackgroundImageMode::RepeatVertically:
        {
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:image.size.width].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
            switch (backgroundImageProperties->GetHorizontalAlignment())
            {
                case HorizontalAlignment::Right:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeRight multiplier:1.0 constant:0].active = YES;
                    break;
                case HorizontalAlignment::Center:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
                    break;
                case HorizontalAlignment::Left:
                default:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeLeft multiplier:1.0 constant:0].active = YES;
                    break;
            }
            break;
        }
        case BackgroundImageMode::Stretch:
        default:
        {
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeLeading multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTrailing relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeTrailing multiplier:1.0 constant:0].active = YES;
            
            imageView.contentMode = UIViewContentModeScaleAspectFill;
            break;
        }
    }
}
