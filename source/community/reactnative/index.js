/** @format */

import { AppRegistry, Platform } from 'react-native';
import App from './App';
import { name as appName } from './app.json';
import { name as windowsapp } from './windows.json';

AppRegistry.registerComponent(Platform.OS === 'windows' ? windowsapp : appName, () => App);

