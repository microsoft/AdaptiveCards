  
Pod::Spec.new do |spec|
  spec.name             = 'AdaptiveCards'

  spec.version          = '1.0.3'
  
  spec.license          = { :type => 'MIT', :text => <<-LICENSE 
                                Copyright (c) 2017 Microsoft

                                Permission is hereby granted, free of charge, to any person obtaining a copy
                                of this software and associated documentation files (the "Software"), to deal
                                in the Software without restriction, including without limitation the rights
                                to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
                                copies of the Software, and to permit persons to whom the Software is
                                furnished to do so, subject to the following conditions:

                                The above copyright notice and this permission notice shall be included in all
                                copies or substantial portions of the Software.

                                THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
                                IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
                                FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
                                AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
                                LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
                                OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
                                SOFTWARE.
                            LICENSE
                          } 
  
  spec.homepage         = 'https://adaptivecards.io'
  
  spec.authors          = { 'AdaptiveCards' => 'Joseph.Woo@microsoft.com' }
  
  spec.summary          = 'Adaptive Cards are a new way for developers to exchange card content in a common and consistent way'
  
  spec.source           = { :http => 'https://github.com/Microsoft/AdaptiveCards/releases/download/ios-v1.0.3/AdaptiveCards.framework.zip' }
 
  spec.vendored_frameworks = 'AdaptiveCards.framework'
  
  spec.platform         = :ios, '10'
end
