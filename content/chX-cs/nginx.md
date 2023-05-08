---
title: 'X.3: Nginx Web server'
pre: "<i class='fab fa-linux'></i> "
weight: 3
---

## 1. Installing Nginx on Ubuntu

For this lesson, you can use a virtual private server running Ubuntu or provision a virtual machine on your local system using Vagrant. To install Nginx on Ubuntu, first update your software repository and then install Nginx using the following commands:

```bash
sudo apt update
sudo apt install nginx
```

After installation, start the Nginx web server and check its status:

```bash
sudo systemctl start nginx
sudo systemctl status nginx
```

## 2. Basic Nginx Configuration

The main Nginx configuration file is located at `/etc/nginx/nginx.conf`. This file contains global configurations and settings for your Nginx server. To edit the configuration file, use the following command:

```bash
sudo nano /etc/nginx/nginx.conf
```

Some important directives in the `nginx.conf` file include:

- `user`: Specifies the user and group that Nginx worker processes run as.
- `worker_processes`: Defines the number of Nginx worker processes.
- `error_log`: Specifies the file where Nginx logs error messages.
- `http`: Contains the main HTTP server configurations, such as `access_log` and `keepalive_timeout`.
- `include /etc/nginx/modules-enabled/*.conf;`: All config files in the modules-enabled folder will be served by nginx.

After making changes to the configuration file, always validate the configuration and reload Nginx:

```bash
sudo nginx -t
sudo systemctl reload nginx
```

## 3. Configuring a Simple Webpage

Create a new directory for your website and set the appropriate permissions

The `www-data` user is the default user for web servers like Nginx and Apache on Ubuntu systems. By default, the `www-data` user has limited permissions and is placed in the `www-data` group. This user and group setup is crucial for maintaining security and minimizing potential risks associated with running a web server.

In Linux, users and groups are essential for managing file permissions and access control. Users can be part of multiple groups, and each group can have multiple users. The `www-data` user and group are specifically designed for web server processes.

File ownership and permissions are critical for securing a web server. By setting the appropriate ownership and permissions for website files and directories, you can prevent unauthorized users from modifying or deleting your web content.

```bash
sudo mkdir -p /var/www/hellonginx/html
sudo chown -R www-data:www-data /var/www/hellonginx
sudo chmod -R 755 /var/www/hellonginx
```

### What does chmod mean?

And what are these random numbers? 

Linux has 3 kinds of permissions: read, write and execute. For easy configuration this permissions are represented be a 1 base-8 digit (a number between 0 and 7).

* 4 for read permissions
* 2 for write permissions
* 1 for execute permissions

By adding these numbers together every possible combination can be represented in that 1 octal number. So in our example chmod command: `sudo chmod -R 755 /var/www/hellonginx` we are given the following permissions:

* 7 = 4 + 2 + 1 = read + write + execute permissions
* 5 = 4 + 1 = read + execute permissions
* 5 = 4 + 1 = read + execute permissions

So why am I giving these permissions three times over? Who am I giving these permissions to?

The first number (7) is given to the user owner. In the previous command we set the owner of the directory to the www-data.
The second number (5) is given to the group owner. In the previous command we also set the group owner of the directory to the www-data group.
The final number (5) is for everyone else.

You can check the permissions of a folder or file by using the following command: `ls -al`. This will return an output along the lines of:
```drwxr-xr-x 3 root     root     4096 May  8 08:48 .```

The initial `d` stands for *directory*. A *file* would be denoted with `-`. The following three letters indicate the permissions granted to the user owner. In our case this is `rwx`, which is exactly what we have given. The next three letters are the permissions for the group owner, in our case `r-x`. Since the `w` is missing, the group owner does not have write permissions. The finale 3 letters are the permissions for everyone else.

### Continue configuration

Create an `index.html` file with a simple "Hello World" message:

```bash
sudo nano /var/www/hellonginx/html/index.html
```

Add the following HTML code to the file:

```html
<!DOCTYPE html>
<html>
<head>
<title>Welcome to Nginx Server!</title>
</head>
<body>
<h1>Hello World from Nginx Server!</h1>
</body>
</html>
```

Save and close the file.

Now, create a configuration file for your website:

```bash
sudo nano /etc/nginx/sites-available/hellonginx
```

Add the following configuration to the file:

```nginx
server {
  listen 80;
  server_name localhost;
  root /var/www/hellonginx/html;

  location / {
  }
}
```

### Let's dive in the config file

`listen 80` -> We're listening on port 80, default http port.

`server_name localhost` -> Nginx can host multiple sites, which can all listen on the same port. The server_name directive tells Nginx which requests need to be routed to which site.

`root /var/www/hellonginx/html` -> The location of the root folder of the website, containing the index.html file and all other resources needed to present the website to the user.

```nginx 
  location / {
  }
```
-> This tells nginx where to listen for your requests. In this case any request made to `http://localhost` will be redirected to the root of your folder structure. 

### Enabling the site

Create a symbolic link, this is like creating a shortcut in Windows, to enable the site:

```bash
sudo ln -s /etc/nginx/sites-available/hellonginx /etc/nginx/sites-enabled/
```

Restart Nginx and test the configuration:

```bash
sudo systemctl restart nginx
nginx -t
```

## 4. Logging

Nginx has two types of logs: access logs and error logs. Access logs record all HTTP requests received by the server, while error logs contain information about errors that occur, such as permission errors or configuration-related access errors. Understanding and configuring Nginx logs helps diagnose issues and monitor server performance.

### Access logs

Access logs record all HTTP requests received by the server. You can configure the access logs using the `access_log` directive in the `nginx.conf` file or in a server block. The default log format is called `combined`, which includes information like the client IP address, request method, URI, response status code, and user agent. You can also create custom log formats using the `log_format` directive.

### Error logs

Error logs record information about errors occurring on the server, such as permission errors or configuration-related access errors. You can configure error logs using the `error_log` directive in the `nginx.conf` file or in a server block. The `error_log` directive allows you to set the log level and the location of the log file:

```nginx
error_log log_file_location log_level;
```

Log levels include `debug`, `info`, `notice`, `warn`, `error`, `crit`, `alert`, and `emerg`. Higher log levels also include messages from lower log levels. For example, if you set the log level to `error`, the error log will include messages for `error`, `crit`, `alert`, and `emerg` log levels.

### Examples

1. **Permission errors**: These errors occur when Nginx does not have the necessary permissions to access a file or directory.

```2023/05/08 09:23:31 [error] 7298#7298: *3 "/var/www/hellonginx/html/index.html" is forbidden (13: Permission denied), client: 127.0.0.1, server: localhost, request: "GET / HTTP/1.1", host: "localhost"```

2. **File not found errors**: These errors occur when a requested file does not exist.

```2023/05/08 09:04:27 [error] 7165#7165: *1 open() "/var/www/hellonginx/html/bla" failed (2: No such file or directory), client: 127.0.0.1, server: localhost, request: "GET /bla HTTP/1.1", host: "localhost"```

3. **Configuration error**: These errors occur when there is an issue with the Nginx configuration, such as a missing or incorrect server block.

```2023/08/05 12:34:56 [emerg] 12345#12345: no "ssl_certificate" is defined in server listening on SSL port while SSL handshaking, client: 127.0.0.1, server: localhost:443```


## Exercises

1. Create a simple hello world web page like we did in the previous section. But instead of giving the user read, write and execute permissions, play around with a couple of the following combinations:
* Read + write
* Write + execute
* Execute
* Read

What is the result when accessing your website and why? What is the minimum set of privileges needed to run our static website?

2. Change the owner of your website folder by using the following command:

```bash
sudo chown <youruser>: -R /var/www/hellonginx
```
(Replace <youruser> with the user you user to login to your system). 
Let's also reset the permissions to only have read privileges across the board:

```bash
sudo chmod 444 -R /var/www/hellonginx
```
What command would you now have to execute to give the current user read and write permissions, the user's group read permissions, but allow the nginx user to have read, write and execute permissions?

3. Create a second website that listens on port 4200. Make sure both sites are accessible!

4. Create a new folder in `hellonginx/html`, name this folder `extra_news`, create another simple index.html file in this folder. Now we want to expose this folder in our website through the path `https://localhost/news`. 
Configure the nginx configuration file to make sure this is possible. (Tip: use a second location directive).
  
5. Change the second website to now be accessible through https. (Tip: use a self-signed certificate created by `openssl`)
