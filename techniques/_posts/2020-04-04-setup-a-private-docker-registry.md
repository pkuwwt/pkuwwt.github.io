---
vim: wrap expandtab ft=markdown
layout: blog
comments: true
tags: docker registry web-UI
title: Setup a private docker registry v2 with web-ui
---

Docker registry is a repository for docker images, like `https://registry.hub.docker.com/`, where user can `pull` and `search` docker images.

## Basic usage

### Start a docker registry container

```bash
docker run -d -p 8080:5000 --name registry --restart=always registry:2
```

### Push a local image to the local registry server

```bash
docker tag registry:2 localhost:8080/myimages/registry:2
docker push localhost:8080/myimages/registry:2
```

### Pull images from the local registry server

```bash
docker pull localhost:8080/myimages/registry:2
```

### Search images in local registry server

There are no `search` support in docker registry v2. However, it provides some api to do this.

```bash
wget localhost:8080/v2/_catalog
wget localhost:8080/v2/myimages/registry/tags/list
```

So there is a python script to help us to search the local registry server

```bash
import sys
import json
import requests
def get_json(url):
    if url.startswith('1') or url.startswith('localhost'):
        url = 'http://' + url
    return json.loads(requests.get(url).content)
def get_repositories(url):
    return get_json(url + '/v2/_catalog')['repositories']
def get_repo_tags(url, image_name):
    return get_json(url + '/v2/' + image_name + '/tags/list')['tags']
def get_all_tags(url):
    tags = {}
    repositories = get_repositories(url)
    for repo in repositories:
        tags[repo] = get_repo_tags(url, repo)
    return tags
def padding(name, length):
    if length > len(name):
        return name + ' '*(length-len(name))
    return name[0:length]
def print_all_tags(tags):
    for repo in tags:
        print(padding(repo, 30) + '\t' + ','.join(tags[repo]))
def filter_tags(tags, keyword):
    results = {}
    for repo in tags:
        if repo.lower().find(keyword.lower()) >= 0:
            results[repo] = tags[repo]
    return results
def main():
    if len(sys.argv) == 1:
        print('USAGE: http://localhost:8080 [keyword]')
        return
    if len(sys.argv) == 2:
        print_all_tags(get_all_tags(sys.argv[1]))
        return
    print_all_tags(filter_tags(get_all_tags(sys.argv[1]), sys.argv[2]))
if __name__ == '__main__':
    main()
```

## Web UI

Besides the command line usage, it will be nice to have a web UI. There are quite a few candidates for this purpose, e.g. [Portus](http://port.us.org/), [docker-registry-ui](https://github.com/Joxit/docker-registry-ui).

Here, we only demostrate the usage of docker-registry-ui.

First we pull the images
```
docker pull joxit/docker-registry-ui:latest
docker pull joxit/docker-registry-ui:static
```

Then run it as a container, which expose the service on port `8080`, by
```bash
docker-compose -f simple.yml up -d
```
where `simple.yml` looks like
```
version: '2.0'
services:
  registry:
    image: registry:2.6.2
    volumes:
      - ./registry-data:/var/lib/registry
    networks:
      - registry-ui-net

  ui:
    image: joxit/docker-registry-ui:static
    ports:
      - 8080:80
    environment:
      - REGISTRY_TITLE=My Private Docker Registry
      - REGISTRY_URL=http://registry:5000
    depends_on:
      - registry
    networks:
      - registry-ui-net

networks:
  registry-ui-net:
```

Then we have a local registry server on port `8080` for both web UI and registry.

The test script looks like
```bash
docker tag joxit/docker-registry-ui:static localhost:8080/joxit/docker-registry-ui:static
docker tag joxit/docker-registry-ui:static localhost:8080/joxit/docker-registry-ui:0.3
docker tag joxit/docker-registry-ui:static localhost:8080/joxit/docker-registry-ui:0.3.0
docker tag joxit/docker-registry-ui:static localhost:8080/joxit/docker-registry-ui:0.3.0-static
docker tag joxit/docker-registry-ui:static localhost:8080/joxit/docker-registry-ui:0.3-static

docker push localhost:8080/joxit/docker-registry-ui

docker tag registry:2.6.2 localhost:8080/registry:latest
docker tag registry:2.6.2 localhost:8080/registry:2.6.2
docker tag registry:2.6.2 localhost:8080/registry:2.6
docker tag registry:2.6.2 localhost:8080/registry:2.6.0
docker tag registry:2.6.2 localhost:8080/registry:2

docker push localhost:8080/registry
```

The scripts here refer to the example in `https://github.com/Joxit/docker-registry-ui/ui-as-proxy/`.

