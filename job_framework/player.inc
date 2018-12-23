#include <YSI\y_hooks>

#if !defined INVALID_PLAYER_JOB
	#define INVALID_PLAYER_JOB (-1)
#endif

forward OnPlayerPickupJobPickup(playerid, jobID);
forward OnPlayerGetNewJob(playerid, jobID);
forward OnPlayerRemoveFromJob(playerid, jobID);

enum _jf_player_ {

 	jf_pJob,
 	jf_paymentForPlayer

}

new jf_pVar[MAX_PLAYERS][_jf_player_];


hook OnPlayerPickUpPickup(playerid, pickupid)
{
	for(new i; i<VAR__createdjobs;i++)
	{
		while(VAR__Job[i][jPickup] == pickupid)
		{
			CallLocalFunction("OnPlayerPickupJobPickup", "dd", playerid, i);
			break;
		}
	}
}

hook OnPlayerConnect(playerid)
{
	SetPlayerJob(playerid, INVALID_PLAYER_JOB);
}

stock SetPlayerJob(playerid, jobid)
{
	jf_pVar[playerid][jf_pJob] = jobid;
	jf_pVar[playerid][jf_paymentForPlayer] = GetJobPayment(jobid);
	#if defined OnPlayerGetNewJob
		CallLocalFunction("OnPlayerGetNewJob", "dd", playerid, jobid);
	#endif	
	return 1;
}

stock GetPlayerJob(playerid)
{
	return jf_pVar[playerid][jf_pJob];
}

stock RemovePlayerFromJob(playerid)
{
	#if defined OnPlayerRemoveFromJob
		CallLocalFunction("OnPlayerRemoveFromJob", "dd", playerid, jf_pVar[playerid][jf_pJob]);
	#endif
	jf_pVar[playerid][jf_pJob] = -1;
	jf_pVar[playerid][jf_paymentForPlayer] = -1;		
	return 1;
}