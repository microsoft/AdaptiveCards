# Adaptive Cards UI TestApp

## Running the UI TestApp

1. Follow the steps detailed [here](../README.md) to bootstrap and build the repo
2. Move to this directory `cd adaptivecards-ui-testapp`
3. Execute the `build` task `npm run build`
4. Execute the `start` task `npm run start`
5. A browser window/tab should open automatically with the adress `localhost:8080`

If you have made any changes to the html, css or ts files the project should rebuild itself; if package.json, tsconfig.json or webpack.config.js have been modified the project has to be rebuilt manually for the changed to take effect (execute steps 3 and 4).

## Running the UI tests

To execute the UI tests follow the steps detailed [here](../tests/ui-tests/README.md)