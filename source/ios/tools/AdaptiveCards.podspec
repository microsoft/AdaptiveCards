  
Pod::Spec.new do |spec|
  spec.name             = 'AdaptiveCards'

  spec.version          = '1.0.3'
  
  spec.license          = { :type => 'Adaptive Cards Binary EULA', :file => 'EULA-Non-Windows.txt' } 
  
  spec.homepage         = 'https://adaptivecards.io'
  
  spec.authors          = { 'AdaptiveCards' => 'Joseph.Woo@microsoft.com' }
  
  spec.summary          = 'Adaptive Cards are a new way for developers to exchange card content in a common and consistent way'
  
  spec.source           = { :http => 'https://adaptivecardsblob.blob.core.windows.net/adaptivecardsiosblobs/AdaptiveCards.framework.zip' }
 
  spec.vendored_frameworks = 'AdaptiveCards.framework'
  
  spec.platform         = :ios, '10'
end
