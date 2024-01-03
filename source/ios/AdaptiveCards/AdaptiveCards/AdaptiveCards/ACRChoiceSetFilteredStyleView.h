//
//  ACRChoiceSetFilteredStyleView.h
//  AdaptiveCards
//
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import "ACOHostConfig.h"
#import "ACOTypeaheadDynamicChoicesService.h"
#import "ACRIBaseInputHandler.h"
#import "ACRView.h"
#import <UIKit/UIKit.h>

@class ACRTypeaheadStateAllParameters;

@protocol ACRChoiceSetFilteredDelegate <NSObject>
- (void)updateSelectedChoiceInTextField:(NSString *)text;
- (NSString *)getSelectedText;
- (NSString *)getChoiceSetId;
@end

@interface ACRChoiceSetFilteredStyleView : UITextField <UITextFieldDelegate, ACRIBaseInputHandler, ACRChoiceSetFilteredDelegate>

@property (weak) UIView *showFilteredListControl;

- (instancetype)initWithInputChoiceSet:(ACOBaseCardElement *)acoElem
                              rootView:(ACRView *)rootView
                            hostConfig:(ACOHostConfig *)hostConfig
                     searchStateParams:(ACRTypeaheadStateAllParameters *)searchStateParams
                    typeaheadViewTitle:(NSString *)typeaheadViewTitle;

@end
