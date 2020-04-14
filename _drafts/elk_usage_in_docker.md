---
vim: wrap expandtab ft=markdown
layout: blog
tags: ELK docker log
title: Usage of ELK stack in docker
---

## Install

```
docker pull sebp/elk
```

## Data Sources

### Filebeat

```
docker pull elastic/filebeat:7.6.2
```

### Heartbeat

```
docker pull elastic/heartbeat:7.6.2
docker run -d elastic/heartbeat \
		   setup -E setup.kibana.host=kibna-host:5601 \
		   -E output.elasticsearch.hosts=["elasticsearch-host:9200"]
```

### Metricbeat

```
docker pull elastic/metricbeat:7.6.2
```

## Dashboard


## References

  * [Running filebeat on docker](https://www.elastic.co/guide/en/beats/filebeat/current/running-on-docker.html)
  * [Running heartbeat on docker](https://www.elastic.co/guide/en/beats/heartbeat/current/running-on-docker.html)
  * [ELK Docker](https://elk-docker.readthedocs.io/)

