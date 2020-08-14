# Details about Hosting .NET WPF Driver
Make the following changes to the files dotnetWPF-renderer folder under source/tools/testConsistency before deploying it on a docker container:
1. In **REST_WPF.py** add the following lines at the end:
   ``` 
   if __name__ == "__main__":
    app.run(host="0.0.0.0", port=80)
   ```
   This allows the REST API to run on port 80.
2. In **app/routes.py**, change the line: 
   ```
     res_json = subprocess.run(['WPFDriver/WPFDriver/bin/Debug/WPFDriver.exe'],
                                 input=card_byte_buffer,
                                 capture_output=True
                                 )
    ```
    to 
    ```
     res_json = subprocess.run(['c:/WPFApp/WPFDriver.exe'],
                                input=card_byte_buffer,
                                capture_output=True
                                 )
    ```
3. Build the WPFDriver solution. Then, copy the files from the Release folder to a new directory WPFApp. 
4. Add the WPFApp folder, dockerfile and the **REST_WPF.py** and app folder to the same folder. 
5. Download the windows python3.8.5 installer and add it to the directory which contains the files above. 

   (*A later version of python would work too. Just edit the dockerfile to reflect the name of the installer file.*)

5. Host the docker image on an azure container registry.