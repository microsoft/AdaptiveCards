FROM mcr.microsoft.com/dotnet/framework/sdk:4.7.2
COPY . c:/
RUN C:/python-3.8.5.exe /passive InstallAllUsers=1 PrependPath=1 Include_test=0
RUN pip install flask
EXPOSE 80 
CMD ["python", "c:/REST_WPF.py"]