# Copyright (c) Microsoft Corporation. All rights reserved. 
# Licensed under the MIT License. 
from flask import Flask 

app = Flask(__name__)

from app import routes
