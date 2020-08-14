# Details about Hosting JavaScript Driver
Make the following changes to the files nodejs-renderer folder under source/tools/testConsistency before deploying it on a docker container:
1. In **REST_nodeJs.py** add the following lines at the end:
   ``` 
   if __name__ == "__main__":
    app.run(host="0.0.0.0", port=80)
   ```
   This allows the REST API to run on port 80.
2. In **app/routes.py**, change the line: 
   ```
    res_json = subprocess.run(['node', 'NodeApp/app.js'],
                              input=card_byte_buffer,
                              capture_output=True,
                              shell=False
                             )
    ```
    to 
    ```
     res_json = subprocess.run(['node', '/src/NodeApp/app.js'],
                              input=card_byte_buffer,
                              capture_output=True,
                              shell=False
                             )
    ```
3. In **NodeApp/app.js**, change the line 36 from: 
   ```
   const browser = await puppeteer.launch();
   ```
   to
   ```
   const browser = await puppeteer.launch({args: ['--no-sandbox', '--disable-setuid-sandbox']});
   ```

4. Copy the dockerfile in this to the folder nodejs-renderer and host it on an an azure container registry.