#include "gnw.h"


void specialLw_iasaCallback(GOBJ* gobj) {
	if (Fighter_IASACheck_JumpF(gobj) != 0) {
		ActionStateChange(0,1,0,gobj, ASID_KNEEBEND, 0x0, 0);
	}
	void (*cb)(GOBJ * gobj) = (void*)0x8014D1AC;
	cb(gobj);
}

void specialAirLw_iasaCallback(GOBJ* gobj) {
	if (Fighter_IASACheck_JumpAerial(gobj) != 0) {
		Fighter_EnterJumpAerial(gobj);
	}
	void (*cb)(GOBJ * gobj) = (void*)0x8014D264;
	cb(gobj);
}
