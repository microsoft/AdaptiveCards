//
//  UtiliOS
//
//  Copyfight © 2019 Microsoft. All rights reserved.
//

#import "ACRErrors.h"
#import "ACRSeparator.h"
#import "ACRViewPrivate.h"
#import "BaseCardElement.h"
#import "CollectionTypeElement.h"
#import "RichTextElementProperties.h"
#import "TextBlock.h"
#import "TextRun.h"
#import "UnknownAction.h"
#import <UIKit/UIKit.h>

using namespace AdaptiveCards;

// configures tag and initial visibility of the given view. Toggle visibility action
// will access the view by the tag to change the visibility.
void configVisibility(UIView *view, std::shared_ptr<BaseCardElement> const &visibilityInfo);

void configSeparatorVisibility(ACRSeparator *view,
                               std::shared_ptr<BaseCardElement> const &visibilityInfo);

void configBleed(ACRView *rootView, std::shared_ptr<BaseCardElement> const &elem,
                 ACRContentStackView *container, ACOHostConfig *acoConfig);

void configBleed(ACRView *rootView, std::shared_ptr<BaseCardElement> const &elem,
                 ACRContentStackView *container, ACOHostConfig *acoConfig, UIView<ACRIContentHoldingView> *superview);

void renderBackgroundImage(const std::shared_ptr<BackgroundImage> backgroundImageProperties,
                           UIView *containerView, ACRView *rootView);

void renderBackgroundImage(const BackgroundImage *backgroundImageProperties, UIImageView *imageView,
                           UIImage *img);

void applyBackgroundImageConstraints(const BackgroundImage *backgroundImageProperties,
                                     UIImageView *imageView, UIImage *img);

ObserverActionBlock generateBackgroundImageObserverAction(
    std::shared_ptr<BackgroundImage> backgroundImageProperties, ACRView *observer,
    std::shared_ptr<BaseCardElement> const &context);

UIFontDescriptor *getItalicFontDescriptor(UIFontDescriptor *descriptor, bool isItalic);

void handleFallbackException(ACOFallbackException *exception, UIView<ACRIContentHoldingView> *view,
                             ACRView *rootView, NSMutableArray *inputs,
                             std::shared_ptr<BaseCardElement> const &elem, ACOHostConfig *config);
void handleActionFallbackException(ACOFallbackException *exception,
                                   UIView<ACRIContentHoldingView> *view, ACRView *rootView,
                                   NSMutableArray *inputs, ACOBaseActionElement *acoElem,
                                   ACOHostConfig *config,
                                   UIStackView *actionSet);

void removeLastViewFromCollectionView(const CardElementType elemType,
                                      UIView<ACRIContentHoldingView> *view);

ACRRenderingStatus buildTargetForButton(ACRTargetBuilderDirector *director,
                                        ACOBaseActionElement *action,
                                        UIButton *button, NSObject **target);

ACRRenderingStatus buildTarget(ACRTargetBuilderDirector *director,
                               ACOBaseActionElement *action, NSObject **target);

void setAccessibilityTrait(UIView *recipientView, ACOBaseActionElement *action);

void TextBlockToRichTextElementProperties(const std::shared_ptr<TextBlock> &textBlock, RichTextElementProperties &textProp);

void TextRunToRichTextElementProperties(const std::shared_ptr<TextRun> &textRun, RichTextElementProperties &textProp);

void buildIntermediateResultForText(ACRView *rootView, ACOHostConfig *hostConfig, RichTextElementProperties const &textProperties, NSString *elementId);

UIFont *getFont(ACOHostConfig *hostConfig, const AdaptiveCards::RichTextElementProperties &textProperties);

ACOBaseActionElement *deserializeUnknownActionToCustomAction(const std::shared_ptr<UnknownAction> action);

UIColor *getForegroundUIColorFromAdaptiveAttribute(std::shared_ptr<HostConfig> const &config, ACRContainerStyle style, ForegroundColor textColor = ForegroundColor::Default, bool isSubtle = false);

unsigned int getSpacing(Spacing spacing, std::shared_ptr<HostConfig> const &config);

void configHorizontalAlignmentConstraintsForBackgroundImageView(const BackgroundImage *backgroundImageProperties, UIView *superView, UIImageView *imageView);

void configVerticalAlignmentConstraintsForBackgroundImageView(const BackgroundImage *backgroundImageProperties, UIView *superView, UIImageView *imageView);

void configWidthAndHeightAnchors(UIView *superView, UIImageView *imageView, bool isComplimentaryAxisHorizontal);

NSMutableAttributedString *initAttributedText(ACOHostConfig *acoConfig, const std::string &text, const AdaptiveCards::RichTextElementProperties &textElementProperties, ACRContainerStyle style);

NSString *makeKeyForImage(ACOHostConfig *acoConfig, NSString *keyType, NSDictionary<NSString *, NSString *> *pieces);

ACRImageSize getImageSize(ImageSize adaptiveImageSize);

CGSize getAspectRatio(CGSize size);
