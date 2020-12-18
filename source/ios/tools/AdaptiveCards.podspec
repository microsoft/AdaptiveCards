  
Pod::Spec.new do |spec|
  spec.name             = 'AdaptiveCards'

  spec.version          = '2.4.1'
  
  spec.license          = { :type => 'Custom', 
                            :file => 'LICENSE' }
  
  spec.homepage         = 'https://adaptivecards.io'
  
  spec.authors          = { 'AdaptiveCards' => 'AdaptiveCards@service.microsoft.com' }
  
  spec.summary          = 'Adaptive Cards are a new way for developers to exchange card content in a common and consistent way'
  
  spec.source           = { :http => 'https://adaptivecardsblob.blob.core.windows.net/adaptivecardsiosblobs/f8c4c778-3181-4e44-ac87-98062e4312c1AdaptiveCards.framework.zip' }

  spec.description = <<-DESC
                       Please note that the consumption of the binary packages such as this pod is subject to the Microsoft
                       EULA (End User License Agreement) included in the pod and not MIT as incorrectly shown in the pod page.
                       For more detail please see our README at https://github.com/microsoft/AdaptiveCards/blob/main/README.md#end-user-license-agreement-for-our-binary-packages
                     DESC

  spec.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }

  spec.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
 
  spec.vendored_frameworks = 'AdaptiveCards.framework'
  
  spec.platform         = :ios, '10'
end
