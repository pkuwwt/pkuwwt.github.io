---
vim: wrap expandtab ft=markdown
layout: blog
tags: s3 minio docker
title: Usage of MinIO in Docker
---

## Install

Pull the image
```bash
docker pull minio/minio
docker pull minio/mc
```

Start the container
```bash
docker run -p 9000:9000 minio/minio server /data
```

Connect it through web url `http://127.0.0.1:9000`.

Connect it through `s3cmd`
```bash
pip3 install s3cmd
s3cmd --host=127.0.0.1:9000 --access-key=minioadmin --secret-key=minioadmin ls
s3cmd --host=127.0.0.1:9000 --access-key=minioadmin --secret-key=minioadmin mb s3://abc
```

Connect it through `boto3`



