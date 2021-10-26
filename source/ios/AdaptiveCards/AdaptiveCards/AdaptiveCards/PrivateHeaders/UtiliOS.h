//
//  UtiliOS
//
//  Copyfight © 2021 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACORenderContext.h>
#import "ACOVisibilityManager.h"
#import "ACRErrors.h"
#import <AdaptiveCards/ACRIBaseCardElementRenderer.h>
#import <AdaptiveCards/ACRSeparator.h>
#import <AdaptiveCards/ACRViewPrivate.h>
#import <AdaptiveCards/BaseCardElement.h>
#import <AdaptiveCards/StyledCollectionElement.h>
#import <AdaptiveCards/RichTextElementProperties.h>
#import <AdaptiveCards/TextBlock.h>
#import <AdaptiveCards/TextRun.h>
#import <AdaptiveCards/UnknownAction.h>
#import <UIKit/UIKit.h>

using namespace AdaptiveCards;

extern const CGFloat kACRScalerTolerance;

// configures tag and initial visibility of the given view. Toggle visibility action
// will access the view by the tag to change the visibility.
void configVisibility(UIView *view, std::shared_ptr<BaseCardElement> const &visibilityInfo);

void configSeparatorVisibility(ACRSeparator *view,
                               std::shared_ptr<BaseCardElement> const &visibilityInfo);

void configVisibilityWithVisibilityManager(ACRView *rootView, NSObject<ACOIVisibilityManagerFacade> *facade, ACRContentStackView *view);

void configRtl(UIView *view, ACORenderContext *context);

ACRRtl getiOSRtl(std::optional<bool> const rtl);

void configBleed(ACRView *rootView, std::shared_ptr<BaseCardElement> const &elem,
                 ACRContentStackView *container, ACOHostConfig *acoConfig);

void configBleed(ACRView *rootView, std::shared_ptr<BaseCardElement> const &elem,
                 ACRContentStackView *container, ACOHostConfig *acoConfig, UIView<ACRIContentHoldingView> *superview);

void renderBackgroundImage(const std::shared_ptr<BackgroundImage> backgroundImageProperties,
                           ACRContentStackView *containerView, ACRView *rootView);

void renderBackgroundImage(ACRView *rootView, const BackgroundImage *backgroundImageProperties, UIImageView *imageView,
                           UIImage *img);

void applyBackgroundImageConstraints(const BackgroundImage *backgroundImageProperties,
                                     UIImageView *imageView, UIImage *img);

void renderBackgroundCoverMode(UIView *backgroundView, UIView *targetView, NSMutableArray<NSLayoutConstraint *> *constraints, ACRContentStackView *parentView);

void configHorizontalAlignmentConstraintsForBackgroundImageView(const BackgroundImage *backgroundImageProperties, UIView *superView, UIImageView *imageView, NSMutableArray<NSLayoutConstraint *> *constraints);

void configVerticalAlignmentConstraintsForBackgroundImageView(const BackgroundImage *backgroundImageProperties, UIView *superView, UIImageView *imageView, NSMutableArray<NSLayoutConstraint *> *constraints);

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

NSString *configureForAccessibilityLabel(ACOBaseActionElement *action, NSString *contentString);

void TexStylesToRichTextElementProperties(const std::shared_ptr<TextBlock> &textBlock,
                                          const TextStyleConfig &textStyleConfig,
                                          RichTextElementProperties &textProp);

void TextRunToRichTextElementProperties(const std::shared_ptr<TextRun> &textRun, RichTextElementProperties &textProp);

void buildIntermediateResultForText(ACRView *rootView, ACOHostConfig *hostConfig, RichTextElementProperties const &textProperties, NSString *elementId);

UIFont *getFont(ACOHostConfig *hostConfig, const AdaptiveCards::RichTextElementProperties &textProperties);

void UpdateFontWithDynamicType(NSMutableAttributedString *content);

ACOBaseActionElement *deserializeUnknownActionToCustomAction(const std::shared_ptr<UnknownAction> action);

UIColor *getForegroundUIColorFromAdaptiveAttribute(std::shared_ptr<HostConfig> const &config, ACRContainerStyle style, ForegroundColor textColor = ForegroundColor::Default, bool isSubtle = false);

unsigned int getSpacing(Spacing spacing, std::shared_ptr<HostConfig> const &config);

NSMutableAttributedString *initAttributedText(ACOHostConfig *acoConfig, const std::string &text, const AdaptiveCards::RichTextElementProperties &textElementProperties, ACRContainerStyle style);

NSString *makeKeyForImage(ACOHostConfig *acoConfig, NSString *keyType, NSDictionary<NSString *, NSString *> *pieces);

CGSize getAspectRatio(CGSize size);

ACRImageSize getACRImageSize(ImageSize adaptiveImageSize, BOOL hasExplicitDimensions);

ACRHorizontalAlignment getACRHorizontalAlignment(HorizontalAlignment horizontalAlignment);

ACRHeightType GetACRHeight(HeightType adaptiveHeight);

ACRVerticalContentAlignment GetACRVerticalContentAlignment(VerticalContentAlignment adaptiveVerticalContentAlignment);

void printSize(NSString *msg, CGSize size);

NSData *JsonToNSData(const Json::Value &blob);

void partitionActions(
    const std::vector<std::shared_ptr<BaseActionElement>> &elems,
    std::vector<std::shared_ptr<BaseActionElement>> &primary,
    std::vector<std::shared_ptr<BaseActionElement>> &secondary,
    unsigned int maxActions,
    ACRView *rootView);

UIImage *scaleImageToSize(UIImage *image, CGSize newSize);

NSNumber *iOSInternalIdHash(const std::size_t internalIdHash);

id traverseResponderChainForUIViewController(UIView *view);

CGRect FindClosestRectToCover(CGRect coverRect, CGRect targetRectToCover);
