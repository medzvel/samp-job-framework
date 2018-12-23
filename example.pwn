#include <a_samp>

#include <job_framework\main>
#include <job_framework\player>

#include <zcmd>


new
	JobType:testjobtype1,
	testjob1
;

new pMayChooseJob[MAX_PLAYERS];

main()
{
	print("\n----------------------------------");
	print(" Job Framework usage Example");
	print("----------------------------------\n");
}

new Text3D:JobLabel[MAX_JOBS];

public OnGameModeInit()
{
	// Don't use these lines if it's a filterscript
	SetGameModeText("Blank Script");
	AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);
	
	testjobtype1 = DefineJobType("Farmer", 150);
	testjob1 = CreateJob("Farmers", testjobtype1, 1946.9158,1320.6340,9.1094);
	return 1;
}

public OnGameModeExit()
{
	return 1;
}

public OnJobCreate(jobID, Float:jPos_X, Float:jPos_Y, Float:jPos_Z)
{
	new string[MAX_JOB_NAME + 40], job_Name[MAX_JOB_NAME];
	GetJobName(jobID, job_Name);
	format(string, sizeof(string), "{FF0000}Job\n{78F22C}Name {FFFFFF}- {78F22C}%s\nPayment {FFFFFF}- {78F22C}%d$", job_Name, GetJobPayment(jobID));
	JobLabel[jobID] = Create3DTextLabel(string, -1, jPos_X, jPos_Y, jPos_Z, 5.0, 0, 1);
	//DEBUG
	printf("[JOB CREATED] Job Name: %s, Job Payment: %d", job_Name,GetJobPayment(jobID));
	return 1;
}

public OnPlayerPickupJobPickup(playerid, jobID)
{
	if(GetPlayerJob(playerid) != jobID && GetPlayerJob(playerid != INVALID_PLAYER_JOB))
	{
	    SendClientMessage(playerid, -1, "Leave your current job, then come here again");
	    return 1;
	}
	new job_name[MAX_JOB_NAME];

	GetJobName(jobID, job_name);
	
	new dialog_header[MAX_JOB_NAME + 24], dialog_msgbox[MAX_JOB_WORKER_STATUS + 82];
	format(dialog_header, sizeof(dialog_header), "Job - {FF0000}%s{FFFFFF}", job_name);

	if(GetPlayerJob(playerid) == jobID)
	{
	    format(dialog_msgbox, sizeof(dialog_msgbox), "Are you sure that you want to leave {FF0000}%s{FFFFFF} ?", job_name);
		ShowPlayerDialog(playerid, 2, DIALOG_STYLE_MSGBOX, dialog_header, dialog_msgbox, "Yes", "No");
		return 1;
	}

	new jobworker_status[MAX_JOB_WORKER_STATUS];
	GetJobWorkerStatus(jobID, jobworker_status);

	format(dialog_msgbox, sizeof(dialog_msgbox), "Do you want to start job as {FF0000}%s{FFFFFF} ?\nYour payment will be {45EA2F}%d${FFFFFF} !", jobworker_status, GetJobPayment(jobID));

    pMayChooseJob[playerid] = jobID;

	ShowPlayerDialog(playerid, 1, DIALOG_STYLE_MSGBOX, dialog_header, dialog_msgbox, "Yes", "No");
	return 1;
}

public OnPlayerGetNewJob(playerid, jobID)
{
	new string[MAX_JOB_WORKER_STATUS + 46], pWorkerStatus[MAX_JOB_WORKER_STATUS], job_Name[MAX_JOB_NAME];
	GetJobWorkerStatus(pMayChooseJob[playerid], pWorkerStatus);
  	format(string, sizeof(string), "You started job as {FF0000}%s{FFFFFF}. Your payment will be {45EA2F}%d${FFFFFF} !", pWorkerStatus, GetJobPayment(pMayChooseJob[playerid]));
   	SendClientMessage(playerid, -1, string);
   	format(string, sizeof(string), "{FF0000}Job\n{78F22C}Name {FFFFFF}- {78F22C}%s\nPayment {FFFFFF}- {78F22C}%d$\nCurrent Job Workers - %d", job_Name, GetJobPayment(jobID), CountJobWorkers(jobID));
   	Update3DTextLabelText(JobLabel[jobID], -1, string);
	return 1;
}

public OnPlayerRemoveFromJob(playerid, jobID)
{
	new string[MAX_JOB_WORKER_STATUS + 50], job_WorkerStatus[MAX_JOB_WORKER_STATUS];
	
	GetJobWorkerStatus(jobID, job_WorkerStatus);
	
	format(string, sizeof(string), "You are not working as {FF0000}%s{FFFFFF} anymore!", job_WorkerStatus);
	SendClientMessage(playerid, -1, string);
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	return 1;
}


public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == 1)
	{
	    if(response)
	    {
	        SetPlayerJob(playerid, pMayChooseJob[playerid]);
	    }
	    else
	    {
	        pMayChooseJob[playerid] = INVALID_JOB_ID;
	        SendClientMessage(playerid, -1, "We are sorry, that you don't like our job!");
	    }
	}
	if(dialogid == 2)
	{
	    if(response)
	    {
	        RemovePlayerFromJob(playerid);
		}
	}
	return 1;
}

CMD:myjob(playerid, params[])
{
	new p_JobStatus[MAX_JOB_WORKER_STATUS], string[MAX_JOB_WORKER_STATUS + 15];
	GetJobWorkerStatus(GetPlayerJob(playerid), p_JobStatus);
	format(string, sizeof(string), "Status: %s | Payment: %d", p_JobStatus, GetJobPayment(GetPlayerJob(playerid)));
	SendClientMessage(playerid, -1, string);
	return 1;
}
	
	
