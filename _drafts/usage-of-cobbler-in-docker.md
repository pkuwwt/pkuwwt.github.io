---
vim: wrap expandtab ft=markdown
layout: blog
tags: docker cobbler
title: Usage of Cobbler in Docker
---

## Usage of the cobbler docker

### Pull the docker and the repository

```
docker pull ethnchao/cobbler
git clone https://github.com/ethnchao/docker-cobbler.git
cd docker-cobbler
```

### Start the container

```
docker run -d \
		   --privileges \
		   --net host \
		   -v /sys/fs/cgroup:/sys/fs/cgroup:ro \
		   -v $(shell pwd)/etc/cobbler/settings:/etc/cobbler/settings \
		   -v $(shell pwd)/etc/cobbler/dhcp.template:/etc/cobbler/dhcp.template \
		   -v $(shell pwd)/dist/mnt:/mnt:ro \
		   -v $(shell pwd)/var/www/cobbler/images:/var/www/cobbler/images \
		   -v $(shell pwd)/var/www/cobbler/ks_mirror:/var/www/cobbler/ks_mirror \
		   -v $(shell pwd)/var/www/cobbler/links:/var/www/cobbler/links \
		   -v $(shell pwd)/var/lib/cobbler/config:/var/lib/cobbler/config \
		   -v $(shell pwd)/var/lib/tftpboot:/var/lib/tftpboot \
		   -p 69:69 \
		   -p 80:80 \
		   -p 443:443 \
		   -p 25151:25151 \
		   --name cobbler ethnchao/cobbler
```

### Mount and import the iso

```
mkdir -p dist/mnt/ubuntu-18.04
sudo mount -t iso9660 -o loop,ro -v $(shell pwd)/dist/ubuntu-18.04.iso dist/mnt/ubuntu-18.04
docker exec -it cobbler cobbler import --name=ubuntu-18.04 --arch=x86_64 --path=/mnt/ubuntu-18.04
```

### Automate Installation in VirtualBox

```
vboxmanage hostonlyif ifconfig vboxnet0 --ip 192.168.56.1
```

## Configuration for Windows

## References

  * [Cobbler in a Docker Container](http://container-solutions.com/cobbler-in-a-docker-container/)
  * [Installing Windows with cobbler](https://www.letifer.org/2014/03/26/cobbler-and-windows/)

