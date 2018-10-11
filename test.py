import json
import base64
import requests
import os

personalAccessToken = ':7rvtdw3ihxbfo262z7h24asnkr42znukpzzccy7fl2eoinfdqrdq';

headers = {}

headers['Authorization'] = b'Basic ' + base64.b64encode(bytes(personalAccessToken, 'utf-8'))

#buildId = '%2f' + os.environ['BUILD_BUILDNUMBER'] + '%2f' +  os.environ['BUILD_BUILDID']

#url = 'https://artifacts.dev.azure.com/microsoft/_apis/drop/manifests/os' + buildId + 'api-version=2.0'
url = 'https://artifacts.dev.azure.com/microsoft/_apis/drop/manifests/os%2f20181005.1%2f12228408?api-version=2.0'

r = requests.get(url, headers=headers)
urlToArtifacts = (r.json()[0]['blob']['url'])

outputBuff = [];
with open('AdaptiveCards.podspec', 'r') as f:
    lines = f.readlines();
    for line in lines:
        if 'spec.source' in line:
            outputBuff.append("  spec.source = { :http => \'%s\',\n                  :type => \'zip\'}\n" % urlToArtifacts) 
        elif 'spec.version' in line:
            outputBuff.append("  spec.version = \'%s\'\n" % '1.0.1') 
        elif ':type => \'zip\'' not in line:
            outputBuff.append(line)

with open('AdaptiveCards.podspec', 'w') as f:
    f.writelines(outputBuff)

print(urlToArtifacts)
