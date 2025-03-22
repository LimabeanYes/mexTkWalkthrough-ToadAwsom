#include "gnw.h"

// This IASA callback is for GNW's grounded down special
// Allows GNW to jump cancel out of the move
void specialLw_iasaCallback(GOBJ* gobj) {
	//Checks if the user inputs a jump
	if (Fighter_IASACheck_JumpF(gobj) != 0) {
		//If there is a jump input, chamges the fighter state to KNEE_BEND (jumpsquat)
		//Passing in GNW's gobj so the game knows it is him perforing the action
		ActionStateChange(0,1,0,gobj, ASID_KNEEBEND, 0x0, 0);
	}
	//Assign's GNW's original down special IASA callback (0x8014D1AC) to void function `cb`
	void (*cb)(GOBJ * gobj) = (void*)0x8014D1AC;
	
	//Runs `cb` with GNW's gobj to use GNW's original IASA callback to preserve down special's typical functionality 
	cb(gobj);
}

// This IASA callback is for GNW's air down special
// Allows GNW to jump cancel out of the move
void specialAirLw_iasaCallback(GOBJ* gobj) {
	//Checks if the user inputs a jump
	if (Fighter_IASACheck_JumpAerial(gobj) != 0) {
		//Uses a function to enter a fighter's air jump
		//Passing in GNW's gobj so the game knows it is him perforing the action
		Fighter_EnterJumpAerial(gobj);
	}
	//Assign's GNW's original air down special IASA callback (0x8014D264) to void function `cb`
	void (*cb)(GOBJ * gobj) = (void*)0x8014D264;
	
	//Runs `cb` with GNW's gobj to use GNW's original IASA callback to preserve down special's typical functionality 
	cb(gobj);
}
