---
vim: wrap expandtab ft=markdown
layout: blog
tags: kubernates virtualization server
title: The Kubernates Concepts
---

## Overview

Kubernates provides the `Kubernates API` and a command line `kubectl` to manipulate the state of the cluster, including

  * which applications/workloads to run
  * what container images to use
  * how many replicas
  * what resources to make availabe, e.g. network or disk
  * ...

After the user submit his/her desired state, the `Kubernates Control Plane` then use the `Pod Lifecycle Event Generator` ([PLEG](https://github.com/kubernetes/community/blob/master/contributors/design-proposals/node/pod-lifecycle-event-generator.md)) to commit those states to the cluster. To do so, there are a variety of tasks being performed:

  * starting/restarting containers
  * scaling the number of replicas of given applications
  * ...

The Kubernates Control Plane consists of a collection of processes running on the cluster:

  * `Kubernates Master node`: including processes
    * kube-apiserver
	* kube-controller-manager
	* kube-scheduler
  * `Non-master node`: including two processes
    * kubelet: used to communicate with master
	* kube-proxy: the network proxy which reflects Kubernates networking services on each node

## Kubernates objects

The state of Kubernates are represented by a number of abstractions:
  * containerized applications and workloads
  * their associated network and disk resources 
  * other information about what the cluster is doing

These abstractions are represented by objects in Kubernates API. See [Understanding Kubernates objects](https://kubernetes.io/docs/concepts/overview/working-with-objects/kubernetes-objects/#kubernetes-objects) for more details.

The basic objects include

  * Pod
  * Service
  * Volume
  * Namespace

Kubernates also contains higher-level abstractions that rely on [controllers]() to build upon these basic objects,
and provide additional functionality and convenience features:

  * Deployment
  * DaemonSet
  * StatefulSet
  * ReplicaSet
  * Job

## References

  * [Kubernates Concepts](https://kubernetes.io/docs/concepts/)


