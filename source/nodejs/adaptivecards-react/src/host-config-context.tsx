// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import React, { createContext, useCallback, useRef, useState } from 'react';
import defaultHostConfigJson from '../assets/default-host-config.json';

interface Variant {
  text: string;
  key: string;
}

interface HostConfigOption {
  text: string;
  key: string;
  variants?: Variant[];
}

interface HostConfig {
  text: string;
  key: string;
  variant?: Variant;
  configJson: object;
}

interface HostConfigContextValue {
  loading: boolean;
  setHostConfig: (themeKey: any, subThemeKey?: any) => void;
  hostConfig: HostConfig;
  options: HostConfigOption[];
}

const options = [
  { text: 'Default', key: 'default' },
  {
    text: 'Teams',
    key: 'teams',
    variants: [
      { text: 'Light', key: 'light' },
      { text: 'Dark', key: 'dark' },
    ],
  },
  { text: 'Outlook', key: 'outlook' },
  {
    text: 'Cortana',
    key: 'cortana',
    variants: [
      { text: 'Classic', key: 'classic' },
      { text: 'Light', key: 'light' },
      { text: 'Dark', key: 'dark' },
    ],
  },
  { text: 'Skype', key: 'skype' },
  { text: 'Webchat', key: 'webchat' },
  { text: 'Windows Notification', key: 'windows-notification' },
  { text: 'Windows Timeline', key: 'windows-timeline' },
];

const defaultHostConfig = {
  configJson: defaultHostConfigJson,
  text: 'Default',
  key: 'default',
};

const defaultContextValue: HostConfigContextValue = {
  loading: false,
  setHostConfig: () => null,
  hostConfig: defaultHostConfig,
  options,
};

const HostConfigContext = createContext<HostConfigContextValue>(
  defaultContextValue
);

export default HostConfigContext;

export const Provider = (props: React.PropsWithChildren<{}>) => {
  const [hostConfig, setHostConfig] = useState<HostConfig>(defaultHostConfig);
  const [loading, setLoading] = useState<boolean>(false);
  const loadedConfigsRef = useRef<{ [key: string]: HostConfig }>({
    default: defaultHostConfig,
  });

  const chooseNewHostConfig = useCallback(
    (key: any, variantKey?: any) => {
      const filename = variantKey ? `${key}-${variantKey}` : key;
      const chosenOption = options.find(
        ({ key: optionKey }) => key === optionKey
      );
      if (!chosenOption) {
        return;
      }

      const loadedConfigs = loadedConfigsRef.current;
      const variant = chosenOption.variants?.find(
        ({ key }) => key === variantKey
      );
      if (loadedConfigs.hasOwnProperty(filename)) {
        setHostConfig(loadedConfigs[filename]);
        return;
      }

      const fetchConfig = async () => {
        setLoading(true);
        try {
          const response = await window.fetch(`hostConfigs/${filename}.json`);
          const configJson = await response.json();
          const newConfig = {
            text: chosenOption.text,
            key,
            variant,
            configJson,
          };
          loadedConfigs[filename] = newConfig;
          setHostConfig(newConfig);
        } catch (e) {
          console.error(`Could not fetch host config for ${filename}`, e);
        } finally {
          setLoading(false);
        }
      };
      fetchConfig();
    },
    [loadedConfigsRef, setHostConfig, setLoading]
  );

  return (
    <HostConfigContext.Provider
      {...props}
      value={{
        loading,
        hostConfig,
        setHostConfig: chooseNewHostConfig,
        options,
      }}
    />
  );
};
