---
vim: wrap expandtab ft=markdown
layout: blog
tags: mysql docker database
title: Usage of Mysql in docker
---

## Install

Pull the image from docker hub. This is the server-only image, much smaller than the full `mysql` image.
```bash
docker pull mysql/mysql-server
```

Start a container with password and port specified
```bash
docker run -e MYSQL_ROOT_PASSWORD=your-root-password \
		   -v /path/to/local_storage:/var/lib/mysql \
		   -p 3306:3306 -d mysql:latest \
		   --default-authentication-plugin=mysql_native_password
```

After a dozen of seconds, try to connect the server with command line client `mysql`
```bash
mysql -h127.0.0.1 -P3306 -uroot -pyour-root-password
```

