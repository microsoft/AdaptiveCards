//
//  ACEditorViewController.h
//  ADCIOSVisualizer
//
//  Created by Inyoung Woo on 9/28/22.
//  Copyright © 2022 Microsoft. All rights reserved.
//

#include <UIKit/UIKit.h>

@class ACEditorViewController;
@class ACVTableViewController;
@protocol ACVTableViewControllerDelegate;

@protocol ACUserChoiceHandlerDelegate

- (void)userIsDoneWithEditing:(ACEditorViewController *)editorViewController;
- (void)userRequestForDelete:(ACEditorViewController *)editorViewControoler;

@end

@interface ACEditorViewController : UIViewController
@property (weak, nonatomic) IBOutlet UIBarButtonItem *cancelButton;
@property (weak, nonatomic) IBOutlet UINavigationBar *navigationBar;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *applyButton;
@property (weak, nonatomic) IBOutlet UITextView *editorView;
@property (nonatomic, weak) id<ACVTableViewControllerDelegate> delegate;
@property (nonatomic, weak) id<ACUserChoiceHandlerDelegate> editorDelegate;

@property (weak, nonatomic) ACVTableViewController *actableViewController;

- (void)handleUserSelection;
- (void)handleUserCancleRequest;
- (void)configure:(ACVTableViewController *)controller delegate:(id<ACVTableViewControllerDelegate>)delegate;

@end
