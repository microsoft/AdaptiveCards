import 'react-native';
import React from 'react';
import renderer from 'react-test-renderer';
import AdaptiveCard from '../src/adaptive-card'

it('renders correctly', () => {
    const tree = renderer.create(
        <AdaptiveCard payload={{
            "type": "AdaptiveCard",
            "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
            "version": "1.2",
            "body": [
                {
                    "type": "TextBlock",
                    "text": "Adaptive Card Test"
                }
            ]
        }}/>
    ).toJSON();
    expect(tree).toMatchSnapshot();
  });
