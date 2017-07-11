//
//  ACRSeparator.mm
//  ADCIOSFramework
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRSeparator.h"
#import "HostConfig.h"
#import "TextBlock.h"
#import <UIKit/UIKit.h>

using namespace AdaptiveCards;

@implementation ACRSeparator
{
    CGFloat width;
    CGFloat height;
    CGFloat lineWidth;
    UILayoutConstraintAxis axis;
    long rgb;
}

+ (void) renderSeparation:(std::shared_ptr<BaseCardElement> const &) elem
             forSuperview:(UIView*) view
           withHostConfig:(std::shared_ptr<HostConfig> const &) config
{          
    ACRSeparator* separator = nil;
    if(SeparationStyle::None != elem->GetSeparationStyle() &&
       [view isKindOfClass: [UIStackView class] ])
    {
        UIStackView* superview = (UIStackView*) view;
        separator = [[ACRSeparator alloc] init];
        SeparationConfig* separatorHstCnfig = 
            [separator getSeparationConfig: elem
                       withHostConfig: config];
        if(separator && separatorHstCnfig)
        {
            separator->width  = separatorHstCnfig->spacing;
            separator->height = separatorHstCnfig->spacing;
            separator->rgb = std::stoul(separatorHstCnfig->lineColor.substr(1), nullptr, 16);
            separator->lineWidth = separatorHstCnfig->lineThickness;
            separator.backgroundColor = UIColor.clearColor;
            [superview addArrangedSubview:separator];
            
            NSLayoutConstraint* constraint = nil;
            separator->axis = superview.axis;
            if(UILayoutConstraintAxisVertical == superview.axis)
            {
                constraint = [NSLayoutConstraint constraintWithItem: separator
                                                          attribute: NSLayoutAttributeWidth
                                                          relatedBy: NSLayoutRelationEqual
                                                             toItem: superview
                                                          attribute: NSLayoutAttributeWidth
                                                         multiplier: 1
                                                           constant: 0];
                [separator setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
                [separator setContentCompressionResistancePriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
                [separator setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisVertical];
                [separator setContentCompressionResistancePriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisVertical];
            }
            else
            {
                constraint = [NSLayoutConstraint constraintWithItem: separator
                                                          attribute: NSLayoutAttributeHeight
                                                          relatedBy: NSLayoutRelationEqual
                                                             toItem: superview
                                                          attribute: NSLayoutAttributeHeight
                                                         multiplier: 1
                                                           constant: 0];
                [separator setContentHuggingPriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];
                [separator setContentCompressionResistancePriority:UILayoutPriorityDefaultHigh forAxis:UILayoutConstraintAxisHorizontal];
                [separator setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
                [separator setContentCompressionResistancePriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
            }
            
            if(constraint) [superview addConstraint:constraint];
        }
    }
}

- (SeparationConfig* ) getSeparationConfig:(std::shared_ptr<BaseCardElement> const &) elem
                            withHostConfig:(std::shared_ptr<HostConfig> const &) config
{
    switch (elem->GetSeparationStyle())
    {
        case SeparationStyle::Strong:
            return &config->strongSeparation;
        case SeparationStyle::Default:
            switch (elem->GetElementType())
            {
                case CardElementType::Container:
                    return &config->container.separation;
                case CardElementType::Column:
                    return &config->column.separation;
                case CardElementType::ColumnSet:
                    return &config->columnSet.separation;
                case CardElementType::FactSet: 
                    return &config->factSet.separation;
                case CardElementType::Image:
                    return &config->image.separation;
                case CardElementType::ImageSet:
                    return &config->imageSet.separation;
                case CardElementType::TextBlock:
                {
                    std::shared_ptr<TextBlock> txtBlck = std::dynamic_pointer_cast<TextBlock>(elem);
                    switch (txtBlck->GetTextSize())
                    {
                        case TextSize::Small:
                            return &config->textBlock.smallSeparation;
                        case TextSize::Normal:
                            return &config->textBlock.normalSeparation;
                        case TextSize::Medium:
                            return &config->textBlock.mediumSeparation;
                        case TextSize::Large:
                            return &config->textBlock.largeSeparation;
                        case TextSize::ExtraLarge:
                            return &config->textBlock.extraLargeSeparation;
                    }
                    break;
                }
                default:
                    break;
            }
            break;

        case SeparationStyle::None:
            break;
        default:
            break;
    }

    return nullptr;
}

- (void) drawRect: (CGRect) rect
{
    CGPoint orig, dest;
    if(UILayoutConstraintAxisVertical == self->axis)
    { 
        orig = CGPointMake(rect.origin.x, rect.origin.y + rect.size.height / 2.0);
        dest = CGPointMake(rect.origin.x + rect.size.width, 
                                          rect.origin.y + rect.size.height / 2.0);
    }
    else
    {
        orig = CGPointMake(rect.origin.x + rect.size.width / 2.0, rect.origin.y);
        dest = CGPointMake(rect.origin.x + rect.size.width / 2.0, 
                                             rect.origin.y + rect.size.height);
    }
 
    UIBezierPath *path = [UIBezierPath bezierPath];
    if(path)
    {
        [path moveToPoint:    orig];
        [path addLineToPoint: dest];
        path.lineWidth =      self->lineWidth;
 
        [[UIColor colorWithRed: ((self->rgb & 0x00FF0000) >> 16) / 255.0
                         green: ((self->rgb & 0x0000FF00) >> 8)  / 255.0
                          blue: ((self->rgb & 0x000000FF))       / 255.0
                         alpha: ((self->rgb & 0xFF000000) >> 24) / 255.0] setStroke];
 
         [path stroke];
     }
}

- (CGSize) intrinsicContentSize
{
    return CGSizeMake(width, height);
}

@end
