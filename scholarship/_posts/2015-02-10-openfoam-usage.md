---
layout: blog
comments: true
title: Usage of OpenFoam
---

## Installation

## Usage

Steps:

  * init OpenFoam Environment
  * compile a solver
  * configure mesh and intial conditions
  * generate mesh based on configuration or other software
  * use solver to solve the configuration with the mesh
  * convert output to VTK for rendering

### Init OpenFoam Environment

All OpenFoam files lay in the installation directory. Before we use any of its commands, we should setup the environment correctly, Then we stay in the same terminal for further operations.

    source $OpenFoamRoot/etc/bashrc

### Compilation of solver
In `applications/solvers/incompressible/icoFoam/` directory, a solver is defined by header `createFields.H` and `icoFoam.C`. In `icoFoam.C`, a equation `UEqn==-fvc::grad(p)` is defined and solved by function `solve()`. The variables vector field `U` and pressure field `p` are defined in `createFields.H`. After `solve()`, there are `PISO` algorithms to iteratively correct between `p` and `U`, because they are interdependent while `solve` assume one of them as default values.

The compilation commands are 

    cd applications/solvers/incompressible/icoFoam/
    wmake

`wmake` will generate `$OpenFoamRoot/platforms/linux64GccDPOpt/bin/icoFoam`, where `linux64GccDPOpt` depends on the computer and OS. Then you can use `icoFoam` in commandline to solve equations defined by specific mesh and initial conditions.

### Configuration
There are 3 directories in a configuration directory, like `$OpenFoamRoot/tutorials/incompressible/icoFoam/cavity`. They are 

  * 0: initial conditions for vector/scalar field, like `p` and `U`.
  * constant: mesh and variables
  * system: parameters

The mesh can be described by `constant/polyMesh/blockMeshDict`, which is used by `blockMesh` to generate a series mesh file in `constant/polyMesh` directory. We can also use other ways to generate these mesh files, like software `pointwise`.

In `system/controlDict`, there are time steps specification and interval for output. `system/fvSchemes` stores the numerical parameters. `system/fvSolutions` is about solve parameters.

### Mesh Generation

    cd $OpenFoamRoot/tutorials/incompressible/icoFoam/cavity
    blockMesh

### Solve

    icoFoam

### Output Data Conversion

    foamToVTK

## MPI

Use `decomposPar` to divide the mesh, its configuration is `system/decomposeParDict`, which can be found in other directories.

    decomposPar
    mpirun -n 4 icoFoam -parallel

