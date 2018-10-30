#include <YSI\y_hooks>


//JOB DEFINES
#if !defined MAX_JOBS
	#define MAX_JOBS 15
#endif

#if !defined MAX_JOB_NAME
	#define MAX_JOB_NAME 120
#endif

#if !defined MAX_JOB_WORKER_STATUS
	#define MAX_JOB_WORKER_STATUS 164
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


enum type_job
{
	//Back-end
	JTYPworkerStatus[164],
	JTYPpayment
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

stock JobType:DefineJobType(jTypWorkerStatus[], jTypPayment)
{
	//Back-end
	strcat(VAR__typeJob[VAR__createdjtypes][JTYPworkerStatus], jTypWorkerStatus);
	VAR__typeJob[VAR__createdjtypes][JTYPpayment] = jTypPayment;
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
	VAR__Job[VAR__createdjobs][jPickup] = CreatePickup(1239, 21, jPosition_X, jPosition_Y, jPosition_Z);
	return VAR__createdjobs++;
}




stock GetJobPayment(jobID)
{
	return VAR__typeJob[VAR__Job[jobID][jobType]][JTYPpayment];
}

stock GetJobName(jobID, name[], maxsize = sizeof(name))
{
	strcat(name, VAR__Job[jobID][jName], maxsize);
}
