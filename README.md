# samp-job-framework

[![sampctl](https://shields.southcla.ws/badge/sampctl-samp--job--framework-2f2f2f.svg?style=for-the-badge)](https://github.com/medzvel/samp-job-framework)

Job Framework - Create Jobs Easily

## Installation

### sampctl

Simply install to your project:

```bash
sampctl package install medzvel/samp-job-framework
```

Include in your code and begin using the library:

```pawn
#include <jobframework>
```

### non-sampctl

Download that repository or *git clone* it, then copy/cut file *jobframework.inc* and *job_framework* folder and place them into *pawno/includes* directory

Include in your code and begin using the library:

```pawn
#include <jobframework>
```

## Usage

### GLOBAL FUNCTIONS

* `JobType:DefineJobType(jTypWorkerStatus[], jTypPayment, jTypPickupID = 1239);`
* `CreateJob(jobName[], JobType:jType, Float:jPosition_X, Float:jPosition_Y, Float:jPosition_Z);` 
* `CountJobWorkers(jobID);` 
* `GetJobPayment(jobID);` 
* `GetJobName(jobID, output[], len = sizeof(output));` 
* `GetJobWorkerStatus(jobID, output[], len = sizeof(output));` 
* `JobsCreated();` 

### PLAYER FUNCTIONS

* `SetPlayerJob(playerid, jobid);` 
* `GetPlayerJob(playerid);` 
* `RemovePlayerFromJob(playerid);`  

### CALLBACKS

* `forward OnJobCreate(jobID, Float:jPos_X, Float:jPos_Y, Float:jPos_Z);` - *Called after `CreateJob` function*
* `forward OnPlayerPickupJobPickup(playerid, jobID);` *Called after a player pick ups job pickup* 
* `forward OnPlayerGetNewJob(playerid, jobID);` *Called after `SetPlayerJob` function*
* `forward OnPlayerRemoveFromJob(playerid, jobID);` *Called after `RemovePlayerFromJob` function*

## Testing

```bash
sampctl package get medzvel/samp-job-framework

sampctl package build --forceBuild

sampctl package run
```