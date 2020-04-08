---
vim: wrap expandtab ft=markdown
layout: blog
tags: postgres postgis docker database
title: Usage of PostGIS in docker
---

## Install

Pull the image from docker hub
```bash
docker pull mdillon/postgis
```

Start a container with password and port specified
```bash
docker run -e POSTGRES_PASSWORD=your-postgres-password \
		   -v /path/to/local_storage:/var/lib/postgresql \
		   -p 5432:5432 -d mdillon/postgis
```

Try to connect the server with command line client `mysql`
```bash
psql -h 127.0.0.1 -p 5432 -U postgres postgres
```

Create a database `dbname` through command line
```bash
psql -h 127.0.0.1 -p 5432 -U postgres -c "CREATE DATABASE dbname;" postgres
psql -h 127.0.0.1 -p 5432 -U postgres -c "CREATE EXTENSION postgis;" dbname
```


