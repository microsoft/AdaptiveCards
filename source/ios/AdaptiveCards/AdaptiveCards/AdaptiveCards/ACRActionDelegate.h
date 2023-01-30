//
//  ACRActionDelegate
//  ACRActionDelegate.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOAdaptiveCard.h"
#import "ACOBaseActionElement.h"
#import "ACOTypeaheadSearchHandler.h"

#import <Foundation/Foundation.h>

@class ACROverflowMenuItem;
@class ACROverflowTarget;

@protocol ACRActionDelegate <NSObject>

- (void)didFetchUserResponses:(ACOAdaptiveCard *)card action:(ACOBaseActionElement *)action;

@optional
- (void)didLoadElements;
- (void)didChangeVisibility:(UIButton *)button isVisible:(BOOL)isVisible;
- (void)didChangeViewLayout:(CGRect)oldFrame newFrame:(CGRect)newFrame;
- (void)didChangeViewLayout:(CGRect)oldFrame newFrame:(CGRect)newFrame properties:(NSDictionary *)properties;

#pragma mark - callback for typeahead search (input.choiceset)

/**
- when choices.data property is present in input.choiceset
 - This callback is called on input change in choiceset control and used to fetch dynamic choices from the host.
   - "searchRequest": search request object format to be sent to the host
   - "acoElem": ChoiceSetInput element on which text change was observed
   - "completion": completion block with results dictionary as response or error in case of any failure
 */
- (void)onChoiceSetQueryChange:(NSDictionary *)searchRequest acoElem:(ACOBaseCardElement *)elem completion:(void (^)(NSDictionary *response, NSError *error))completion;

/**
- This callback is to update the layout of the typeahead view whenever search state is changed
*/
- (void)didUpdateTypeaheadSearchViewController:(UIViewController *)typeaheadSearchVC searchStateImageView:(UIImageView *)searchStateImageView searchViewState:(TSTypeaehadSearchViewState)searchViewState;

/**
- This callback is to launch the full screen search VC fromm input.choiceset control
 - Client callback requires to return a BOOL value.
 - Returning YES means let SDK continue to launch VC on top of the parent view, while NO informs SDK don't launch the typeahead search VC in full screen
   (which implies client code might grab the typeahead search view controller and launch view by itself).
 */
- (BOOL)shouldLaunchTypeaheadSearchViewController:(UIViewController *)typeaheadSearchVC;

/**
- This callback is to configure the navigation item which is present at the top of the search view controller (configure back button and checkmark)
 - Client callback requires to return a BOOL value.
 - Returning YES means let SDK continue to launch VC on top of the parent view, while NO informs SDK don't launch the typeahead search VC in full screen
 */
- (BOOL)shouldConfigureNavigationItemViewWithVC:(UIViewController *)typeaheadSearchVC;

#pragma mark - callbacks for overflow actions

/**
 If callback returns YES  then the actions exceeding the number defined in hostConfig.actions.maxActions will be auto wrapped up as overflow actions and "..." button for context menu will be displayed, even for those primary buttons.
 */
- (BOOL)shouldAllowMoreThanMaxActionsInOverflowMenu;

/**
 - This callback is called when "..." overflow button will be rendered.
    - "button": the current "..." overflow button
    - "target": the target to trigger popup menu or current "..." overflow button. Client can access its associated menu item actions through target.menuItems, or add this target to any UIButton to trigger the popup
    - "isRootLevelActions":  indicates if the current "..." overflow action belongs to root level actions array. If it's NO then it indicates it's ActionSet as body elements.

 - Client callback requires to return a BOOL value. Returning NO means let SDK continue to render "..." button, while YES informs SDK don't render the current "..." button (which implies client code might grab those flyout actions (target.menuItems) and render / handle overflow actions by itself).
 */
- (BOOL)onRenderOverflowAction:(UIButton *)button
                     forTarget:(ACROverflowTarget *)target
          isAtRootLevelActions:(BOOL)isAtRootLevelActions;

/**
 - It'll be called when overflow context menu (action sheet) will be shown. If client returns NO, SDK will continue to present default overlow menu in action sheet, while returning YES informs SDK don't display the popup overflow menu.
 - By using this callbak client can implement its own custom overlow menu to display
    - "menuItems": the action items on the overflow menu associated with the current triggered overflow "..." button
    - "alert": presentable-ready alert controller. Client can just use its view controller to present this. Or client can grab "menuItems" to prepare its own overflow menu
 */
- (BOOL)onDisplayOverflowActionMenu:(NSArray<ACROverflowMenuItem *> *)menuItems
                    alertController:(UIAlertController *)alert
                     additionalData:(NSDictionary *)additionalData;
@end
