  
Pod::Spec.new do |spec|
  spec.name             = 'AdaptiveCards'

  spec.version          = '2.8.3'
  
  spec.license          = { :type => 'Adaptive Cards Binary EULA', :file => 'source/EULA-Non-Windows.txt' } 
  
  spec.homepage         = 'https://adaptivecards.io'
  
  spec.authors          = { 'AdaptiveCards' => 'Joseph.Woo@microsoft.com' }
  
  spec.summary          = 'Adaptive Cards are a new way for developers to exchange card content in a common and consistent way'
  
  spec.source       = { :git => 'https://github.com/microsoft/AdaptiveCards.git', :tag => 'ios-v2.8.3' }

  spec.source_files           = 'source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/PublicHeaders/*.{h,m,mm}'

  spec.public_header_files = 'source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/PublicHeaders/*.h'
    
  spec.subspec 'UIProviders' do | sspec |
    sspec.source_files = 'source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/UIProviders/*.h'
    sspec.header_mappings_dir = 'source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/UIProviders/'
    sspec.private_header_files = 'source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/UIProviders/*.h'
    sspec.dependency 'MicrosoftFluentUI/Tooltip_ios', '~> 0.3.6'
  end
  
  spec.subspec 'ObjectModel' do | sspec |
    sspec.source_files = 'source/shared/cpp/ObjectModel/**/*.{h,cpp}'
    sspec.header_mappings_dir = 'source/shared/cpp/ObjectModel/'
    sspec.private_header_files = 'source/shared/cpp/ObjectModel/**/*.{h}'
    sspec.xcconfig = {
         'CLANG_CXX_LANGUAGE_STANDARD' => 'c++17',
         'CLANG_CXX_LIBRARY' => 'libc++'
    }
  end

  spec.subspec 'Private' do | sspec |
    sspec.source_files = 'source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/PrivateHeaders/*.h'
    sspec.header_mappings_dir = 'source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/PrivateHeaders/'
    sspec.private_header_files = 'source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/PrivateHeaders/*.h'
  end
  
  spec.subspec 'Public' do | sspec |
    sspec.source_files = 'source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/PublicHeaders/*.h'
    sspec.header_mappings_dir = 'source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/PublicHeaders/'
    sspec.public_header_files = 'source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/PublicHeaders/*.h'
  end



  spec.platform         = :ios, '14'

  spec.frameworks = 'AVFoundation', 'AVKit', 'CoreGraphics', 'QuartzCore', 'UIKit'

  spec.public_header_files = 'source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/*.h'
  
  spec.resource_bundles = {'AdaptiveCards' => ['source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/Resources/**/*']}

  spec.exclude_files = 'source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/include/**/*'

end
