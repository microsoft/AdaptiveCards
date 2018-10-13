import json
import base64
import requests
import os
import netrc

import re

acversion = ''

# get AdaptiveCard Version from custom.prop
with open('custom.props', 'r') as f:
    lines = f.readlines();
    for line in lines:
        if 'NuGetPackVersion' in line:
            p = re.compile(r'\d+\.\d+\.\d+')
            m = p.search(line)
            if m != None:
                acversion = m.group()

token = ':' + os.environ['ACPAT']

headers = {}

headers['Authorization'] = b'Basic ' + base64.b64encode(bytes(token, 'utf-8'))

buildNumber = os.environ['BUILD_BUILDNUMBER']

acversion = acversion + '-' + buildNumber;

buildId = '%2f' + buildNumber + '%2f' +  os.environ['BUILD_BUILDID'] + '%2f'

url = 'https://artifacts.dev.azure.com/microsoft/_apis/drop/manifests/os' + buildId + '?api-version=2.0'

print('url: ' + url)

urlToArtifacts = ''
# get Response via REST API
r = requests.get(url, headers=headers)
# get url to artifact 
for item in r.json():
    if 'AdaptiveCards.framework.zip' in item['path']: 
        urlToArtifacts = item['blob']['url']

outputBuff = [];
# update podspec
with open('AdaptiveCards.podspec', 'r') as f:
    lines = f.readlines();
    for line in lines:
        if 'spec.source' in line:
            outputBuff.append("  spec.source = { :http => \'%s\',\n                  :type => \'zip\'}\n" % urlToArtifacts) 
        elif 'spec.version' in line:
            outputBuff.append("  spec.version = \'%s\'\n" % acversion) 
        elif ':type => \'zip\'' not in line:
            outputBuff.append(line)

with open('AdaptiveCards.podspec', 'w') as f:
    f.writelines(outputBuff)
