/**
 * BaseImage component that is used across all the image components
 * in the SDK
 *
 * @example
 * <BaseImage source={uri: 'example_url'} />
 *
 * BaseImage can be overriden using registry
 * @example
 * Registry.getManager.registerInternalComponent('BaseImage', CustomBaseImage);
 */

import React from 'react';
import {Image} from 'react-native';
import {Registry} from '../registration/registry';

export const BaseImage = (props) => {
    const BaseImageExtension = Registry.getManager().getInternalComponentOfType(
        'BaseImage',
    );
    return BaseImageExtension ? (
        <BaseImageExtension {...props} />
    ) : (
        <Image {...props} />
    );
};
