#if defined _JF_uses_YSI
	#include <YSI_Coding\y_hooks>
#endif

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

#if defined _INC_y_hooks
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
		return 1;
	}

	hook OnPlayerConnect(playerid)
	{
		SetPlayerJob(playerid, INVALID_PLAYER_JOB);
		return 1;
	}
#else
	public OnPlayerPickUpPickup(playerid, pickupid)
	{
		for(new i; i<VAR__createdjobs;i++)
		{
			while(VAR__Job[i][jPickup] == pickupid)
			{
				CallLocalFunction("OnPlayerPickupJobPickup", "dd", playerid, i);
				break;
			}
		}
		#if defined _JF_OnPlayerPickUpPickup
			return _JF_OnPlayerPickUpPickup(playerid, pickupid);
		#else 
			return 1;
		#endif
	}
	#if defined _ALS_OnPlayerPickUpPickup
		#undef OnPlayerPickUpPickup
	#else
		#define _ALS_OnPlayerPickUpPickup
	#endif
	#define OnPlayerPickUpPickup _JF_OnPlayerPickUpPickup
	#if defined _JF_OnPlayerPickUpPickup
		forward _JF_OnPlayerPickUpPickup(playerid, pickupid);
	#endif

	public OnPlayerConnect(playerid)
	{
		SetPlayerJob(playerid, INVALID_PLAYER_JOB);
		#if defined _JF_OnPlayerConnect
			return _JF_OnPlayerConnect(playerid);
		#else
			return 1;
		#endif
	}
	#if defined _ALS_OnPlayerConnect
		#undef OnPlayerConnect
	#else
		#define _ALS_OnPlayerConnect
	#endif
	#define OnPlayerConnect _JF_OnPlayerConnect
	#if defined _JF_OnPlayerConnect
		forward _JF_OnPlayerConnect(playerid);
	#endif
#endif

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