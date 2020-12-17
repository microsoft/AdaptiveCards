  
Pod::Spec.new do |spec|
  spec.name             = 'AdaptiveCards'

  spec.version          = '2.4.1'
  
  spec.license          = { :type => 'Custom', :file => 'EULA-Non-Windows.txt' }
  
  spec.homepage         = 'https://github.com/microsoft/AdaptiveCards'
  
  spec.authors          = { 'AdaptiveCards' => 'Joseph.Woo@microsoft.com' }
  
  spec.summary          = 'Adaptive Cards are a new way for developers to exchange card content in a common and consistent way'
  
  spec.source           = { :http => 'https://adaptivecardsblob.blob.core.windows.net/adaptivecardsiosblobs/AdaptiveCards.framework.zip' }

  spec.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }

  spec.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
 
  spec.vendored_frameworks = 'AdaptiveCards.framework'
  
  spec.platform         = :ios, '10'
end
