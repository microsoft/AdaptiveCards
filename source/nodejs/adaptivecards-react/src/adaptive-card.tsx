// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

import * as AdaptiveCards from 'adaptivecards';
import React, { 
  useContext,
  useCallback,
  useEffect,
  useRef,
  useState,
} from 'react';
import * as PropTypes from 'prop-types';
import * as markdown from 'markdown-it';
import HostConfigContext from './host-config-context';

export interface Props {
  payload: object;
  onExecuteAction?: Function;
  onActionSubmit?: Function;
  onActionOpenUrl?: Function;
  onActionShowCard?: Function;
  onError?: Function;
  style?: object;
}

const propTypes = {
  /** The card schema.  It must comply with the card schema. [More Info](https://docs.microsoft.com/en-us/adaptive-cards/create/cardschema) */
  payload: PropTypes.object.isRequired,
  /** Method that will be invoked anytime a card action is executed. [More Info](https://docs.microsoft.com/en-us/adaptive-cards/display/implementingrenderer#actions) */
  onExecuteAction: PropTypes.func,
  /** Method that will be invoked when a Submit action is executed. [More Info](https://docs.microsoft.com/en-us/adaptive-cards/display/implementingrenderer#actionsubmit) */
  onActionSubmit: PropTypes.func,
  /** Method that will be invoked when an Open Url action is executed. [More Info](https://docs.microsoft.com/en-us/adaptive-cards/display/implementingrenderer#actionopenurl) */
  onActionOpenUrl: PropTypes.func,
  /** Method that will be invoked when a Show Card action is executed. [More Info](https://docs.microsoft.com/en-us/adaptive-cards/display/implementingrenderer#actionshowcard) */
  onActionShowCard: PropTypes.func,
  /** Method that will be invoked if an error is thrown while trying to render a card. */
  onError: PropTypes.func,
  /** JSX styles that will be applied to the card conatiner */
  style: PropTypes.object,
};

const defaultOpenUrlHandler = (action: AdaptiveCards.OpenUrlAction) => {
  window.open(action.url, '_blank');
};

const setUpMarkdownIt = () => {
  AdaptiveCards.AdaptiveCard.onProcessMarkdown = (text, result) => {
    result.outputHtml = new markdown.default().render(text);
    result.didProcess = true;
  };
};

export const AdaptiveCard = ({
  payload,
  onExecuteAction,
  onActionSubmit,
  onActionOpenUrl,
  onActionShowCard,
  onError,
  style,
}: Props) => {
  const [error, setError] = useState<Error>();
  const targetRef = useRef<HTMLDivElement>(null);
  const cardRef = useRef<AdaptiveCards.AdaptiveCard>(
    new AdaptiveCards.AdaptiveCard()
  );
  const { hostConfig } = useContext(HostConfigContext);

  useEffect(setUpMarkdownIt, []);

  const executeAction = useCallback(
    (a: AdaptiveCards.Action) => {
      const type = a.getJsonTypeName();
      switch (type) {
        case AdaptiveCards.OpenUrlAction.JsonTypeName: {
          if (onActionOpenUrl) {
            onActionOpenUrl(a);
          } else {
            defaultOpenUrlHandler(a as AdaptiveCards.OpenUrlAction);
          }

          break;
        }
        case AdaptiveCards.ShowCardAction.JsonTypeName: {
          if (onActionShowCard) {
            onActionShowCard(a);
          }
          break;
        }
        case AdaptiveCards.SubmitAction.JsonTypeName: {
          if (onActionSubmit) {
            onActionSubmit(a);
          }
          break;
        }
      }
      // TODO: Why is there a global action handler when we have specific
      // handlers for the above cases? Can we simplify to one approach?
      if (onExecuteAction) {
        onExecuteAction(a);
      }
    },
    [onActionOpenUrl, onActionShowCard, onActionSubmit, onExecuteAction]
  );

  useEffect(() => {
    cardRef.current.onExecuteAction = executeAction;
  }, [executeAction]);

  useEffect(() => {
    cardRef.current.hostConfig = new AdaptiveCards.HostConfig(
      hostConfig.configJson
    );

    if (!targetRef.current) {
      return;
    }
    const result = cardRef.current.render() as HTMLElement;
    targetRef.current.innerHTML = '';
    targetRef.current.appendChild(result);
  }, [hostConfig]);

  useEffect(() => {
    if (!targetRef.current) {
      return;
    }
    const card = cardRef.current;

    try {
      card.parse(payload);
      const result = card.render() as HTMLElement;
      targetRef.current.innerHTML = '';
      targetRef.current.appendChild(result);
    } catch (cardRenderError) {
      if (onError) {
        onError(cardRenderError);
        setError(cardRenderError);
      }
    }
  }, [payload, onError]);

  if (error) {
    return <div style={{ color: 'red' }}>{error.message}</div>;
  }
  return <div style={style} ref={targetRef} />;
};

AdaptiveCard.propTypes = propTypes;
