  
Pod::Spec.new do |spec|
  spec.name             = 'AdaptiveCards'

  spec.version          = '2.8.0'
  
  spec.license          = { :type => 'Adaptive Cards Binary EULA', :file => 'source/EULA-Non-Windows.txt' } 
  
  spec.homepage         = 'https://adaptivecards.io'
  
  spec.authors          = { 'AdaptiveCards' => 'Joseph.Woo@microsoft.com' }
  
  spec.summary          = 'Adaptive Cards are a new way for developers to exchange card content in a common and consistent way'
  
  spec.source       = { :git => 'https://github.com/microsoft/AdaptiveCards.git', :tag => 'dotnet-v2.7.2' }

  spec.source_files           = 'source/ios/AdaptiveCards/AdaptiveCards/AdaptiveCards/**/*.{h,m,mm}', 'source/shared/cpp/ObjectModel/**/*.{h,cpp}', 'source/shared/cpp/ObjectModel/json/**/*.{h}'

  spec.platform         = :ios, '13'

  spec.frameworks = 'AVFoundation', 'AVKit', 'CoreGraphics', 'QuartzCore', 'UIKit' 

  spec.xcconfig = {
       'CLANG_CXX_LANGUAGE_STANDARD' => 'c++17',
       'CLANG_CXX_LIBRARY' => 'libc++'
  }

  spec.script_phase = { :name => 'Writing to files', :script => 'mkdir -p Headers/json', :execution_position => :before_compile }

  spec.header_mappings_dir = 'source/shared/cpp/ObjectModel/json'

  spec.preserve_paths = 'source/shared/cpp/ObjectModel/json'

  spec.dependency 'MicrosoftFluentUI', '~> 0.2.6'
end
