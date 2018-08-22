//
//  CustomChoiceSetRenderer.h
//  ADCIOSVisualizer
//
//  Created by Ankit Maurya on 8/22/18.
//  Copyright © 2018 Microsoft. All rights reserved.
//

#ifndef CustomChoiceSetRenderer_h
#define CustomChoiceSetRenderer_h

#import <AdaptiveCards/ACRBaseCardElementRenderer.h>
#import <AdaptiveCards/ACRChoiceSetResourceDelegate.h>

@interface CustomChoiceSetRenderer:ACRBaseCardElementRenderer <ACRChoiceSetResourceDelegate>

+ (CustomChoiceSetRenderer *) getInstance;

@end

#endif /* CustomChoiceSetRenderer_h */
