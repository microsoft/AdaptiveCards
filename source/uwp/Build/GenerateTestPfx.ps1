$CertificateFriendlyName = "AdaptiveCards"
$Publisher = "CN=AdaptiveCards"

$cert = New-SelfSignedCertificate -Type Custom `
    -Subject $Publisher `
    -KeyUsage DigitalSignature `
    -FriendlyName $CertificateFriendlyName `
    -CertStoreLocation "Cert:\CurrentUser\My" `
    -TextExtension @("2.5.29.37={text}1.3.6.1.5.5.7.3.3", "2.5.29.19={text}")

$certificateBytes = $cert.Export([System.Security.Cryptography.X509Certificates.X509ContentType]::Pkcs12)

[System.IO.File]::WriteAllBytes("$PSScriptRoot\..\AdaptiveCardTestApp\Assets\AdaptiveCardTestApp_TemporaryKey.pfx", $certificateBytes)
[System.IO.File]::WriteAllBytes("$PSScriptRoot\..\PerfApp\Assets\PerfApp_TemporaryKey.pfx", $certificateBytes)
[System.IO.File]::WriteAllBytes("$PSScriptRoot\..\UWPUITestApp\Assets\UWPUITestApp_TemporaryKey.pfx", $certificateBytes)
[System.IO.File]::WriteAllBytes("$PSScriptRoot\..\UWPUnitTests\Assets\UWPUnitTests_TemporaryKey.pfx", $certificateBytes)
[System.IO.File]::WriteAllBytes("$PSScriptRoot\..\Visualizer\AdaptiveCardVisualizer_TemporaryKey.pfx", $certificateBytes)