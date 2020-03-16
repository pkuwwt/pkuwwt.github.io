---
vim: wrap expandtab ft=markdown
layout: blog
tags: [jenkins, flask, continuous integration testing, docker, python]
title: Continuous Integration Testing For Flask with Jenkins
---

## Create a simple flask app

There is a minimal flask app `app.py`

```python
from flask import Flask
app = Flask(__name__)
@app.route('/')
def hello():
    return 'Hello World!\n'
if __name__ == '__main__':
    app.run()
```

## Create a test case

Create a test file `test.py`
```python
import unittest
from app import app
class TestHello(unittest.TestCase):
    def setUp(self):
        app.testing = True
        self.app = app.test_client()
    def test_hello(self):
        rv = self.app.get('/')
        self.assertEqual(rv.status, '200 OK')
        self.assertEqual(rv.data, b'Hello World!\n')
if __name__ == '__main__':
    unittest.main()
```

Now if we run `python3 test.py`, the test should pass.

## Jenkinsfile

The `Jenkinsfile` is
```
pipeline {
    agent { docker { image 'python:3.7.2' } }
    stages {
        stage('build') {
            steps {
                sh 'pip install flask
            }
        }
        stage('test') {
            steps {
                sh 'python test.py'
            }
        }
    }
}
```

Now we have a repository with three files:

  * app.py
  * test.py
  * Jenkinsfile

Save it to github or other git server, suppose the git url is `https://github.com/darkn3rd/webmf-python-flask`.

## Install Jenkins

The quickest way is to use a customized jenkins docker.

Suppose we have a `Dockerfile`

```
FROM jenkins/jenkins:alpine

ENV JENKINS_USER admin
ENV JENKINS_PASS admin

# Skip initial setup
ENV JAVA_OPTS -Djenkins.install.runSetupWizard=false


COPY plugins.txt /usr/share/jenkins/plugins.txt
RUN /usr/local/bin/install-plugins.sh < /usr/share/jenkins/plugins.txt
USER root
RUN apk add docker
RUN apk add py-pip
RUN apk add python-dev libffi-dev openssl-dev gcc libc-dev make
RUN pip install docker-compose
```

and the `plugins.txt`

```
ace-editor
ant
antisamy-markup-formatter
branch-api
cloudbees-folder
credentials
cvs
docker
durable-task
external-monitor-job
git-client
git-server
git
github-api
github-branch-source
github
javadoc
jquery-detached
junit
ldap
mailer
matrix-auth
matrix-project
maven-plugin
metrics
pam-auth
plain-credentials
scm-api
script-security
ssh-credentials
ssh-slaves
subversion
translation
variant
windows-slaves
workflow-aggregator
workflow-api
workflow-basic-steps
workflow-cps-global-lib
workflow-cps
workflow-durable-task-step
workflow-job
workflow-multibranch
workflow-scm-step
workflow-step-api
workflow-support
favorite
token-macro
pipeline-stage-step
blueocean
blueocean-autofavorite
gitlab-plugin
```

then execute
```
sudo docker build -t custom-jenkins .
```

After the image `custom-jenkins` is finished, run it with

```
# use user root other than default jenkins to avoid permission problem
# use docker on the host, because there is no docker daemon in a docker container
sudo docker run --user root \
		 -v /var/run/docker.sock:/var/run/docker.sock \
		 -p 8080:8080 -p 50000:50000 custom-jenkins
```

Open `http://127.0.0.1:8080` in browser, and

  * add a `Pipeline` with `Definition` being `Pipeline script from SCM`
  * set the `SCM` to `Git` with url `https://github.com/darkn3rd/webmf-python-flask`.
  * Save

## Test Report

Jenkins supports to represent the test reports with the JUnit format in the **Blue Ocean**,
so we should change the output of the test

```
if __name__ == '__main__':
    import xmlrunner
    runner = xmlrunner.XMLTestRunner(output='test-reports')
    unittest.main(testRunner=runner)
```

and the `Jenkinsfile`

```
pipeline {
    agent { docker { image 'python:3.7.2' } }
    stages {
        stage('build') {
            steps {
                sh 'pip install flask
            }
        }
        stage('test') {
            steps {
                sh 'python test.py'
            }
            post {
                always {junit 'test-reports/*.xml'}
            }
        }
    }
}
```

## References

  * [Jenkins CI Pipeline with Python](https://medium.com/@Joachim8675309/jenkins-ci-pipeline-with-python-8bf1a0234ec3)
  * [Custom jenkins images with plugins pre-installed](https://dev.to/rubiin/custom-jenkins-images-with-plugins-pre-installed-1pok)

