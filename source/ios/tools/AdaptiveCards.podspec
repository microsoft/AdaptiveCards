  
Pod::Spec.new do |spec|
  spec.name             = 'AdaptiveCards'

  spec.version          = '2.8.0-beta.3'
  
  spec.license          = { :type => 'Adaptive Cards Binary EULA', :file => 'EULA-Non-Windows.txt' } 
  
  spec.homepage         = 'https://adaptivecards.io'
  
  spec.authors          = { 'AdaptiveCards' => 'Joseph.Woo@microsoft.com' }
  
  spec.summary          = 'Adaptive Cards are a new way for developers to exchange card content in a common and consistent way'
  
  spec.source           = { :http => 'https://adaptivecardsblob.blob.core.windows.net/adaptivecardsiosblobs/AdaptiveCards.framework.zip' }

  spec.vendored_frameworks = 'AdaptiveCards.xcframework'

  spec.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'i386' }

  spec.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'i386' }
  
  spec.platform         = :ios, '11'
end
