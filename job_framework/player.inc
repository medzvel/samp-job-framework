#include <YSI\y_hooks>

forward OnPlayerPickupJobPickup(playerid, jobID);

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

