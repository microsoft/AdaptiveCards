//
//  ADCIOSPresentationViewController.h
//  ADCIOS
//
//  Created by jwoo on 5/31/17.
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface ADCIOSPresentationViewController : UIViewController

@property (readonly) NSString* jsonStr;

- (id) init:(NSString*) str;

@end
