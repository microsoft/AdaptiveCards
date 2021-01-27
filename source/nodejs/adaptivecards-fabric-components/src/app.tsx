import * as React from 'react';

import * as monaco from 'monaco-editor';
import markdownit from 'markdown-it';
import * as ACDesigner from 'adaptivecards-designer';
import * as AC from 'adaptivecards';
// import { ProgressBar } from './customElement/progressBars';

import { Breadcrumb } from './customElement/uifabric/Breadcrumb/Breadcrumb';
// import { ProgressBarPeer } from './customElement/progressBarPeer';

// if you want to bundle the designer CSS using something like mini-css-loader:
import 'adaptivecards-designer/dist/adaptivecards-designer.css';

import './app.scss';
import { CardDesignerSurface } from 'adaptivecards-designer';

import { initializeIcons } from "@fluentui/react";
initializeIcons()

import { BreadcrumbPeer } from './customElement/uifabric/Breadcrumb/BreadcrumbPeer';
import { Icon } from './customElement/uifabric/Icon/Icon';
import { IconPeer } from './customElement/uifabric/Icon/IconPeer';
import { Spinner } from './customElement/uifabric/Spinner/Spinner';
import { SpinnerPeer } from './customElement/uifabric/Spinner/SpinnerPeer';
import { ProgressIndicator } from './customElement/uifabric/ProgressIndicator/ProgressIndicator';
import { ProgressIndicatorPeer } from './customElement/uifabric/ProgressIndicator/ProgressIndicatorPeer';
import { Persona } from './customElement/uifabric/Persona/Persona';
import { PersonaPeer } from './customElement/uifabric/Persona/PersonaPeer';
import { Nav } from './customElement/uifabric/Nav/Nav';
import { NavPeer } from './customElement/uifabric/Nav/NavPeer';
  
CardDesignerSurface.cardElementPeerRegistry.registerPeer(Breadcrumb, BreadcrumbPeer, "Custom Elements", "acd-icon-adaptiveCard")
CardDesignerSurface.cardElementPeerRegistry.registerPeer(Icon, IconPeer, "Custom Elements", "acd-icon-adaptiveCard")
CardDesignerSurface.cardElementPeerRegistry.registerPeer(Spinner, SpinnerPeer, "Custom Elements", "acd-icon-adaptiveCard")
CardDesignerSurface.cardElementPeerRegistry.registerPeer(ProgressIndicator, ProgressIndicatorPeer, "Custom Elements", "acd-icon-adaptiveCard")
CardDesignerSurface.cardElementPeerRegistry.registerPeer(Persona, PersonaPeer, "Custom Elements", "acd-icon-adaptiveCard")
CardDesignerSurface.cardElementPeerRegistry.registerPeer(Nav, NavPeer, "Custom Elements", "acd-icon-adaptiveCard")
   
// const originalPeerRegistry =  CardElementPeerRegistry.prototype.reset;
// CardElementPeerRegistry.prototype.reset = () =>{
//   originalPeerRegistry();
//   CardElementPeerRegistry.prototype.registerPeer(Breadcrumb, BreadcrumbPeer, "Containers", "acd-icon-adaptiveCard")
// }

// No routing as currently it is supposed to be a single page application
export default class App extends React.Component {
  private designer: ACDesigner.CardDesigner;

  constructor(props: any) {
    super(props);
  }

  public componentDidMount(): void {
    
    // Turn general support for data binding (templating) on or off. When set to false, this flag overrides showDataStructureToolbox and showSampleDataEditorToolbox.
    ACDesigner.GlobalSettings.enableDataBindingSupport = true;

    // Show or hide the "Data structure" toolbox. NOTE: the "Data structure" toolbox is currently non functional and will likely be removed in a future release
    ACDesigner.GlobalSettings.showDataStructureToolbox = false;

    // Show or hide the "Sample Data" toolbox.
    ACDesigner.GlobalSettings.showSampleDataEditorToolbox = true;

    // Show or hide the target version picker.
    ACDesigner.GlobalSettings.showVersionPicker = true;

    // Controls whether the target version should change according to the selected  host application. Each host application is associated with a maximum supported target version.
    ACDesigner.GlobalSettings.selectedHostContainerControlsTargetVersion = true;

    // Controls whether a warning message should be displayed when the selected target version is greater than the version supported by the selected host application. This warning is meant to inform the user that not all features they're designing their card with will work in the target host.
    ACDesigner.GlobalSettings.showTargetVersionMismatchWarning = true;

    ACDesigner.CardDesigner.onProcessMarkdown = (
      text: string,
      result: { didProcess: boolean; outputHtml?: string }
    ) => {
      result.outputHtml = new markdownit().render(text);
      result.didProcess = true;
    };

    let hostContainers: Array<ACDesigner.HostContainer> = [];
    hostContainers.push(
      new ACDesigner.OutlookContainer('Outlook Actionable Messages', 'containers/outlook-container.css')
    );
    hostContainers.push(new ACDesigner.WebChatContainer('Bot Framework WebChat', 'containers/webchat-container.css'));
    
    hostContainers.push(new ACDesigner.TimelineContainer('Windows Timeline', 'containers/timeline-container.css'));
    hostContainers.push(
      new ACDesigner.DarkTeamsContainer('Microsoft Teams - Dark', 'containers/teams-container-dark.css')
    );
    hostContainers.push(
      new ACDesigner.LightTeamsContainer('Microsoft Teams - Light', 'containers/teams-container-light.css')
    );
    hostContainers.push(
      new ACDesigner.BotFrameworkContainer(
        'Bot Framework Other Channels (Image render)',
        'containers/bf-image-container.css'
      )
    );
    hostContainers.push(
      new ACDesigner.ToastContainer('Windows Notifications (Preview)', 'containers/toast-container.css')
    );

    // AC.GlobalRegistry.elements.register(ProgressBar.JsonTypeName, ProgressBar);
    let designer = new ACDesigner.CardDesigner(hostContainers);
    designer.sampleCatalogueUrl = window.location.origin + '/sample-catalogue.json';

    this.designer = new ACDesigner.CardDesigner(hostContainers);
    
    this.designer.attachTo(document.getElementById('designerRootHost'));
    // ACDesigner.CardDesignerSurface.cardElementPeerRegistry.registerPeer(
    //   ProgressBar,
    //   ProgressBarPeer,
    //   'Elements',
    //   'acd-icon-adaptiveCard'
    // );
    // AC.GlobalRegistry.elements.register(ProgressBar.JsonTypeName, ProgressBar);
    //part of basic designer properties
    this.designer.monacoModuleLoaded(monaco);


    this.designer.hostContainer.elementsRegistry.register(Breadcrumb.JsonTypeName, Breadcrumb);
    this.designer.hostContainer.elementsRegistry.register(Icon.JsonTypeName, Icon);
    this.designer.hostContainer.elementsRegistry.register(Spinner.JsonTypeName, Spinner);
    this.designer.hostContainer.elementsRegistry.register(ProgressIndicator.JsonTypeName, ProgressIndicator);
    this.designer.hostContainer.elementsRegistry.register(Persona.JsonTypeName, Persona);
    this.designer.hostContainer.elementsRegistry.register(Nav.JsonTypeName, Nav);
    //@ts-ignore
    this.designer.buildPalette();

    this.designer.setCard({
      "type": "AdaptiveCard",
      "body": [],
      "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
      "version": "1.3"
    })

    // this.designer.hostContainer.elementsRegistry.register(ProgressBar.JsonTypeName, ProgressBar);
    //@ts-ignore
    // this.designer.designerSurface.addPeer(BreadcrumbPeer);
     // this.designer.designerSurface.reg
    //  CardDesignerSurface.cardElementPeerRegistry.registerPeer(Breadcrumb, BreadcrumbPeer, "Containers", "acd-icon-adaptiveCard")
   
    // this.designer.
  }

  public render(): React.ReactElement<{}> {
    return <div id='designerRootHost'></div>;
  }
}