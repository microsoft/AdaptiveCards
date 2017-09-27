  
Pod::Spec.new do |spec|
  spec.name             = 'AdaptiveCards'

  spec.version          = '0.5.1'
  
  spec.license          = { :type => 'MIT', :file => 'LICENSE.txt' } 
  
  spec.homepage         = 'https://adaptivecards.io'
  
  spec.authors          = { 'Joseph Woo' => 'Joseph.Woo@microsoft.com' }
  
  spec.summary          = 'Adaptive Cards are a new way for developers to exchange card content in a common and consistent way'
  
  spec.source           = { :http => 'https://github.com/Microsoft/AdaptiveCards/raw/master/source/ios/release/binary/AdaptiveCards.framework.zip'}
 
  spec.vendored_frameworks = 'AdaptiveCards.framework'
  
  spec.platform         = :ios, '10.3'
end
