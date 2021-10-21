// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import React, { createContext, FC, useContext } from 'react';
import { Props, AdaptiveCard } from './adaptive-card'

interface HostConfig {
    hostConfig: object;
}

export const HostConfigContext = createContext<HostConfig>({ hostConfig: null });

export type PropsWithoutHostConfig = Omit<Props, 'hostConfig'>;

export const AdaptiveCardUsingHostConfigContext = (props: PropsWithoutHostConfig) => {
    const context = useContext(HostConfigContext);
    return <AdaptiveCard {...props} hostConfig={context.hostConfig} />
}

export const ProvidesHostConfigContext: FC<{ hostConfig: object }> = ({ hostConfig, children }) => {
    return <HostConfigContext.Provider value={{ hostConfig }} >{children}</HostConfigContext.Provider>
};
