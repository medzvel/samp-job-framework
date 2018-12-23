#include <YSI\y_hooks>
#include <YSI\y_iterate>

//JOB DEFINES
#if !defined MAX_JOBS
	#define MAX_JOBS 15
#endif

#if !defined MAX_JOB_NAME
	#define MAX_JOB_NAME 120
#endif

#if !defined MAX_JOB_WORKER_STATUS
	#define MAX_JOB_WORKER_STATUS (164)
#endif

//JOB TYPE DEFINES
#if !defined MAX_JOB_TYPES
	#define MAX_JOB_TYPES 	(JobType:50)
#endif

#if !defined INVALID_JOB_TYPE
	#define INVALID_JOB_TYPE	(JobType:-1)
#endif

#if !defined STARTING_JOB_TYPE
	#define STARTING_JOB_TYPE 	(JobType:0)
#endif

#if !defined INVALID_JOB_ID
	#define INVALID_JOB_ID (-1)
#endif	

forward OnJobCreate(jobID, Float:jPos_X, Float:jPos_Y, Float:jPos_Z);

enum type_job
{
	//Back-end
	JTYPworkerStatus[MAX_JOB_WORKER_STATUS],
	JTYPpayment,
	JTYPpickupID,
}

new 
	VAR__typeJob[MAX_JOB_TYPES][type_job];

new JobType:VAR__createdjtypes = STARTING_JOB_TYPE;		


enum main_job
{
	//Back-end
	jName[MAX_JOB_NAME],
	JobType:jobType,
	Float:jPosition[3],

	//Front-end
	jPickup
}

new 
	VAR__Job[MAX_JOBS][main_job],
	VAR__createdjobs = 0
;	

stock JobType:DefineJobType(jTypWorkerStatus[], jTypPayment, jTypPickupID = 1239)
{
	//Back-end
	strcat(VAR__typeJob[VAR__createdjtypes][JTYPworkerStatus], jTypWorkerStatus);
	VAR__typeJob[VAR__createdjtypes][JTYPpayment] = jTypPayment;
	VAR__typeJob[VAR__createdjtypes][JTYPpickupID] = jTypPickupID;
	return VAR__createdjtypes++;
}


stock CreateJob(jobName[], JobType:jType, Float:jPosition_X, Float:jPosition_Y, Float:jPosition_Z)
{
	//Back-end
	VAR__Job[VAR__createdjobs][jobType] = jType;
	strcat(VAR__Job[VAR__createdjobs][jName], jobName);
	VAR__Job[VAR__createdjobs][jPosition][0] = jPosition_X;
	VAR__Job[VAR__createdjobs][jPosition][1] = jPosition_Y;
	VAR__Job[VAR__createdjobs][jPosition][2] = jPosition_Z;
	//Front-end
	VAR__Job[VAR__createdjobs][jPickup] = CreatePickup(VAR__typeJob[VAR__Job[VAR__createdjobs][jobType]][JTYPpickupID], 21, jPosition_X, jPosition_Y, jPosition_Z);
	#if defined OnJobCreate
		CallLocalFunction("OnJobCreate", "dfff", VAR__createdjobs, jPosition_X, jPosition_Y, jPosition_Z);
	#endif	
	return VAR__createdjobs++;
}


stock CountJobWorkers(jobID)
{
	new counted;
	foreach(new i : Player)
	{
		if(GetPlayerJob(i) == jobID) counted++;
	}
	return counted;
}

stock GetJobPayment(jobID)
{
	return VAR__typeJob[VAR__Job[jobID][jobType]][JTYPpayment];
}

stock GetJobName(jobID, output[], len = sizeof(output))
{
	if(jobID == INVALID_JOB_ID) return printf("[JOB FRAMEWORK] ERROR: GetJobName | Invalid Job ID!");
	format(output, len, "%s", VAR__Job[jobID][jName]);
	return 1;
}

stock GetJobWorkerStatus(jobID, output[], len = sizeof(output))
{
	if(jobID == INVALID_JOB_ID) return printf("[JOB FRAMEWORK] ERROR: GetJobWorkerStatus | Player Invalid Job!"); 
	format(output, len, "%s", VAR__typeJob[VAR__Job[jobID][jobType]][JTYPworkerStatus]);
	return 1;
}


stock JobsCreated()
{
	return VAR__createdjobs;
}