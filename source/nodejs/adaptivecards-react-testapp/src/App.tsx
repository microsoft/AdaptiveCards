import React from 'react';
import logo from './logo.svg';
import './App.css';
import HostConfigLight from './host-conf-light.json'
import { ACCards } from './ACCards';
import { ProvidesHostConfigContext } from 'adaptivecards-react';

function App() {
  return (
    <div className="App">
      <ProvidesHostConfigContext hostConfig={HostConfigLight} >
        <ACCards />
      </ProvidesHostConfigContext>
    </div>
  );
}

export default App;
