//
//  ACEditorViewController.m
//  ADCIOSVisualizer
//
//  Created by Inyoung Woo on 9/28/22.
//  Copyright © 2022 Microsoft. All rights reserved.
//

#import "ACEditorViewController.h"
#include "ACVTableViewController.h"
#import <Foundation/Foundation.h>


@implementation ACEditorViewController

- (void)configure:(ACVTableViewController *)controller delegate:(id<ACVTableViewControllerDelegate>)delegate
{
    self.applyButton.target = self;
    self.applyButton.action = @selector(handleUserSelection);
    self.cancelButton.target = self;
    self.cancelButton.action = @selector(handleUserCancleRequest);
    self.actableViewController = controller;
    self.delegate = delegate;
}

- (void)handleUserSelection
{
    [self.delegate fromACVTable:_actableViewController userSelectedJson:_editorView.text];
    [self dismissViewControllerAnimated:YES completion:nil];
    [self.editorDelegate userIsDoneWithEditing:self];
}

- (void)handleUserCancleRequest
{
    [self dismissViewControllerAnimated:YES completion:nil];
}

@end
