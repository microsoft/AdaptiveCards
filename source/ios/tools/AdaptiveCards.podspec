  
Pod::Spec.new do |spec|
  spec.name             = 'AdaptiveCards'

  spec.version          = '2.8.0'
  
  spec.license          = { :type => 'Adaptive Cards Binary EULA', :file => 'source/EULA-Non-Windows.txt' } 
  
  spec.homepage         = 'https://adaptivecards.io'
  
  spec.authors          = { 'AdaptiveCards' => 'Joseph.Woo@microsoft.com' }
  
  spec.summary          = 'Adaptive Cards are a new way for developers to exchange card content in a common and consistent way'
  
  spec.source       = { :git => 'https://github.com/microsoft/AdaptiveCards.git', :branch => 'jwoo/ios-cocoapod' }

  spec.source_files           = 'source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/**/*.{h,m,mm}' 

  spec.subspec 'ObjectModel' do | sspec |
    sspec.source_files = 'source/shared/cpp/ObjectModel/**/*.{h,cpp}', 'source/shared/cpp/ObjectModel/json/**/*.{h}'
    sspec.header_mappings_dir = 'source/shared/cpp/ObjectModel/'
    sspec.project_header_files = 'source/shared/cpp/ObjectModel/**/*.{h}'
    sspec.xcconfig = {
         'CLANG_CXX_LANGUAGE_STANDARD' => 'c++17',
         'CLANG_CXX_LIBRARY' => 'libc++'
    }
  end

  spec.platform         = :ios, '13'

  spec.frameworks = 'AVFoundation', 'AVKit', 'CoreGraphics', 'QuartzCore', 'UIKit' 

  spec.public_header_files = 'source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACOActionOverflow.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACOAdaptiveCard.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACOAdaptiveCardParseResult.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACOBaseCardElement.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACOEnums.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACOHostConfig.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACOHostConfigParseResult.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACOIResourceResolver.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACOInputResults.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACOMediaEvent.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACORemoteResourceInformation.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACORenderContext.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACOResourceResolvers.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRActionDelegate.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRActionOpenURLRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRActionSetRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRActionShowCardRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRActionSubmitRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRBaseActionElementRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRBaseCardElementRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRBaseTarget.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRButton.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRChoiceSetCompactStyleView.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRColumnRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRColumnSetRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRContainerRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRContentHoldingUIView.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRErrors.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRFactSetRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRIBaseActionElementRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRIBaseCardElementRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRIBaseInputHandler.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRIMedia.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRImageProperties.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRImageRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRImageSetRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRInputChoiceSetRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRInputDateRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRInputLabelView.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRInputNumberRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRInputRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRInputTimeRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRInputToggleRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRMediaRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRMediaTarget.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRParseWarning.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRRegistration.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRRenderResult.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRRichTextBlockRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRTableCellRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRTableCellView.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRTableRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRTableRow.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRTableView.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRTapGestureRecognizerEventHandler.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRTapGestureRecognizerFactory.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRTextBlockRenderer.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRTextInputHandler.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRTextView.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRToggleInputView.h, source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/ACRView.h'

  spec.dependency 'MicrosoftFluentUI', '~> 0.2.6'
end

