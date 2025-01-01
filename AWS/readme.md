# AWS Notes

## EC2 web server
* Setup an EC2 instance, enable SSH and web ports
* create an DNS record (A name) to map a subdomain to its IP
* setup NGINX `sudo yum install -y nginx`
* start NGINX `sudo service nginx start` (or `stop` or `reload`)
* edit content in `/usr/share/nginx/html`
* setup dotnet `sudo yum install -y dotnet-sdk-8.0`
* create a minimal API app: `dotnet new web`
* run the web app: `dotnet run --urls http://0.0.0.0:5013`
