// We often want to call internal melee functions located in the iso.
// Including this file (called the mex header) will the compiler how to call those functions.
//
// For example, the mex headers contain a function prototype for `HSD_Randi`.
// It looks like this: `int HSD_Randi(int n);`
// This tells the compiler that there is a symbol called HSD_Randi somewhere else that we want to use,
// which takes in an int and returns an int.
// In the case of HSD_Randi, it takes in a positive number `n` and returns a random value in 0..n.
// 
// When we compile to a dat file, MexTK will take a look at all the melee functions we used
// and map them to the location in the iso they should be called at.
// You can see this map for yourself in the melee.link file in the MexTK repository. 
#include "mex.h"



// This IASA (interruptible as soon as) callback is for GNW's grounded down special.
// We will program this to allow GNW to jump cancel out of the move.
// This function is called every frame that GNW is in the down special state.
//
// This function takes in a GOBJ* (pointer to a gobj) and returns void (nothing).   
// gobj is short for a Game or General Object.  
// Every object (item, stage, effect, character) is a gobj,
// which makes gobjs a very convinient thing to pass around.
// IASA callbacks always pass us the GNW's gobj to use.
void specialLw_iasaCallback(GOBJ *gobj) {

	// To allow GNW to jump cancel down special, we need to check if the player jumped. 
	// Thankfully, the mex header provides an internal melee function that does exactly this!
	// The `int Fighter_IASACheck_JumpF(GOBJ *gobj)` function 
	// Checks if the user inputs a jump using an internal melee function.
	// This will return true if the player jumped this frame.
	if (Fighter_IASACheck_JumpF(gobj)) {

		// If there is a jump input, change the fighter state to KNEE_BEND (jumpsquat) using the ActionStateChange internal melee function.
		// `void ActionStateChange(float startFrame, float animSpeed, float animBlend, GOBJ *fighter, int stateID, int flags1, GOBJ *alt_state_source);`
		// We pass a lot of parameters here, but most are irrelevant. 
		// The two key ones are fighter and stateID.
		// These say: "Who's state do we change?" and "What do we change it to?" respectively. 
		// ASID stands for Animation State ID, and you can see the full list of ASIDs in fighter.h in the MexTK repository. 
		ActionStateChange(0.0f, 1.0f, 0.0f, gobj, ASID_KNEEBEND, 0, 0);

		// One more thing to note:  
		// The FighterData struct is super important for character modding.
		// You can get this from a character's gobj with `FighterData *data = gobj->userdata;`.
		// This struct contains all sorts of data for a character that you can use and modify.
		// Take a look at the FighterData struct in fighters.h in the MexTK repository to see what's in there (it's huge!).  
	}

	// Now because we overwrote GNW's usual IASA callback, his normal IASA code won't run.
	// However, we can still call it ourselves! 
	// 
	// The function pointer syntax here is a little wacky. 
	// This just says to the compiler: "There is a function at address 0x8014D1AC. Give it the name specialLw_iasaCallback_vanilla". 
	// 
	// If the MexTK headers provided this function, then we wouldn't need to do this.
	// But since it doesn't, this workaround lets us call any melee function in the game if we know its address. 
	void (*gnw_specialLw_iasaCallback_vanilla)(GOBJ *gobj) = (void*)0x8014D1AC;
	
	// Now that we've told the compiler about that function, we can call it ourselves. 
	// This will restore vanilla IASA behavior. 
	gnw_specialLw_iasaCallback_vanilla(gobj);
}



// This callback is much the same as the previous one.
void specialAirLw_iasaCallback(GOBJ *gobj) {
	if (Fighter_IASACheck_JumpAerial(gobj)) {
		// Instead of entering jumpsquat, we enter double jump, aka JumpAerial.
		// We could use ActionStateChange for this, but melee provides a convenient way, so we use it!
		Fighter_EnterJumpAerial(gobj);
	}
	void (*gnw_specialAirLw_iasaCallback_vanilla)(GOBJ *gobj) = (void*)0x8014D264;
	gnw_specialAirLw_iasaCallback_vanilla(gobj);
}



// The move logic struct.
// It contains a list of the fighter's special states and what callbacks/data to use for them.
// In this example, we replace the IASA (interruptible as soon as) callback for ground & air down special at the indicated lines.
// When creating fully custom states though, often many fields such as the 
// AnimationID, AnimationCallback, IASACallback, PhysicsCallback, and CollisionCallback are completely changed and replaced with custom functions.
//
// Normally, this table will not contain non-special attacks such as jabs, tilts, aerials, or smash attacks.
// However, GNW is special - many of his regular attacks are programmed as special moves, so they appear here.
// 
// You can see a list of every special action state in the game here:
// https://docs.google.com/spreadsheets/d/1Nu3hSc1U6apOhU4JIJaWRC4Lj0S1inN8BFsq3Y8cFjI/edit?gid=1923544852#gid=1923544852 
FtState move_logic[] = {
	// State: 341 - Attack11
	{
		46,         // AnimationID
		0x2C0201,   // StateFlags
		0x2,        // AttackID
		0x80,       // BitFlags
		0x8014C138, // AnimationCallback
		0x8014C174, // IASACallback
		0x8014C194, // PhysicsCallback
		0x8014C1B4, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 342 - Attack100Start
	{
		49,         // AnimationID
		0x2C0204,   // StateFlags
		0x5,        // AttackID
		0x80,       // BitFlags
		0x8014C224, // AnimationCallback
		0x8014C260, // IASACallback
		0x8014C264, // PhysicsCallback
		0x8014C284, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 343 - Attack100Loop
	{
		50,         // AnimationID
		0x2C0204,   // StateFlags
		0x5,        // AttackID
		0x80,       // BitFlags
		0x8014C308, // AnimationCallback
		0x8014C330, // IASACallback
		0x8014C350, // PhysicsCallback
		0x8014C370, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 344 - Attack100End
	{
		51,         // AnimationID
		0x2C0204,   // StateFlags
		0x5,        // AttackID
		0x80,       // BitFlags
		0x8014C3F4, // AnimationCallback
		0x8014C414, // IASACallback
		0x8014C418, // PhysicsCallback
		0x8014C438, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 345 - AttackLw3
	{
		59,         // AnimationID
		0x240208,   // StateFlags
		0x9,        // AttackID
		0x80,       // BitFlags
		0x8014AE3C, // AnimationCallback
		0x8014AE78, // IASACallback
		0x8014AF6C, // PhysicsCallback
		0x8014AF8C, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 346 - AttackS4
	{
		62,         // AnimationID
		0x240A09,   // StateFlags
		0xA,        // AttackID
		0x80,       // BitFlags
		0x8014AA88, // AnimationCallback
		0x8014AAC4, // IASACallback
		0x8014AAF4, // PhysicsCallback
		0x8014AB14, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 347 - AttackAirN
	{
		68,         // AnimationID
		0x24060C,   // StateFlags
		0xD,        // AttackID
		0x80,       // BitFlags
		0x8014B720, // AnimationCallback
		0x8014B740, // IASACallback
		0x8014B760, // PhysicsCallback
		0x8014B780, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 348 - AttackAirB
	{
		70,         // AnimationID
		0x24060E,   // StateFlags
		0xF,        // AttackID
		0x80,       // BitFlags
		0x8014B87C, // AnimationCallback
		0x8014B89C, // IASACallback
		0x8014B8BC, // PhysicsCallback
		0x8014B8DC, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 349 - AttackAirHi
	{
		71,         // AnimationID
		0x24060F,   // StateFlags
		0x10,       // AttackID
		0x80,       // BitFlags
		0x8014B9D8, // AnimationCallback
		0x8014B9F8, // IASACallback
		0x8014BA18, // PhysicsCallback
		0x8014BA38, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 350 - LandingAirN
	{
		73,         // AnimationID
		0x60C,      // StateFlags
		0xD,        // AttackID
		0xC0,       // BitFlags
		0x8014BB24, // AnimationCallback
		0x8014BB70, // IASACallback
		0x8014BB74, // PhysicsCallback
		0x8014BB94, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 351 - LandingAirB
	{
		75,         // AnimationID
		0x60E,      // StateFlags
		0xF,        // AttackID
		0xC0,       // BitFlags
		0x8014BC0C, // AnimationCallback
		0x8014BC58, // IASACallback
		0x8014BC5C, // PhysicsCallback
		0x8014BC7C, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 352 - LandingAirHi
	{
		76,         // AnimationID
		0x60F,      // StateFlags
		0x10,       // AttackID
		0xC0,       // BitFlags
		0x8014BCF4, // AnimationCallback
		0x8014BD40, // IASACallback
		0x8014BD44, // PhysicsCallback
		0x8014BD64, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 353 - SpecialN
	{
		295,        // AnimationID
		0x340111,   // StateFlags
		0x12,       // AttackID
		0x0,        // BitFlags
		0x8014E73C, // AnimationCallback
		0x8014E87C, // IASACallback
		0x8014E984, // PhysicsCallback
		0x8014E9C4, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 354 - SpecialAirN
	{
		296,        // AnimationID
		0x340511,   // StateFlags
		0x12,       // AttackID
		0x0,        // BitFlags
		0x8014E7DC, // AnimationCallback
		0x8014E900, // IASACallback
		0x8014E9A4, // PhysicsCallback
		0x8014EA00, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 355 - SpecialS
	{
		297,        // AnimationID
		0x340012,   // StateFlags
		0x13,       // AttackID
		0x0,        // BitFlags
		0x8014C8BC, // AnimationCallback
		0x8014C934, // IASACallback
		0x8014C93C, // PhysicsCallback
		0x8014CA10, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 356 - SpecialS
	{
		298,        // AnimationID
		0x340012,   // StateFlags
		0x13,       // AttackID
		0x0,        // BitFlags
		0x8014C8BC, // AnimationCallback
		0x8014C934, // IASACallback
		0x8014C93C, // PhysicsCallback
		0x8014CA10, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 357 - SpecialS
	{
		299,        // AnimationID
		0x340012,   // StateFlags
		0x13,       // AttackID
		0x0,        // BitFlags
		0x8014C8BC, // AnimationCallback
		0x8014C934, // IASACallback
		0x8014C93C, // PhysicsCallback
		0x8014CA10, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 358 - SpecialS
	{
		300,        // AnimationID
		0x340012,   // StateFlags
		0x13,       // AttackID
		0x0,        // BitFlags
		0x8014C8BC, // AnimationCallback
		0x8014C934, // IASACallback
		0x8014C93C, // PhysicsCallback
		0x8014CA10, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 359 - SpecialS
	{
		301,        // AnimationID
		0x340012,   // StateFlags
		0x13,       // AttackID
		0x0,        // BitFlags
		0x8014C8BC, // AnimationCallback
		0x8014C934, // IASACallback
		0x8014C93C, // PhysicsCallback
		0x8014CA10, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 360 - SpecialS
	{
		302,        // AnimationID
		0x340012,   // StateFlags
		0x13,       // AttackID
		0x0,        // BitFlags
		0x8014C8BC, // AnimationCallback
		0x8014C934, // IASACallback
		0x8014C93C, // PhysicsCallback
		0x8014CA10, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 361 - SpecialS
	{
		303,        // AnimationID
		0x340012,   // StateFlags
		0x13,       // AttackID
		0x0,        // BitFlags
		0x8014C8BC, // AnimationCallback
		0x8014C934, // IASACallback
		0x8014C93C, // PhysicsCallback
		0x8014CA10, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 362 - SpecialS
	{
		304,        // AnimationID
		0x340012,   // StateFlags
		0x13,       // AttackID
		0x0,        // BitFlags
		0x8014C8BC, // AnimationCallback
		0x8014C934, // IASACallback
		0x8014C93C, // PhysicsCallback
		0x8014CA10, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 363 - SpecialS
	{
		305,        // AnimationID
		0x340012,   // StateFlags
		0x13,       // AttackID
		0x0,        // BitFlags
		0x8014C8BC, // AnimationCallback
		0x8014C934, // IASACallback
		0x8014C93C, // PhysicsCallback
		0x8014CA10, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 364 - SpecialAirS
	{
		306,        // AnimationID
		0x340412,   // StateFlags
		0x13,       // AttackID
		0x0,        // BitFlags
		0x8014C8F8, // AnimationCallback
		0x8014C938, // IASACallback
		0x8014C974, // PhysicsCallback
		0x8014CA4C, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 365 - SpecialAirS
	{
		307,        // AnimationID
		0x340412,   // StateFlags
		0x13,       // AttackID
		0x0,        // BitFlags
		0x8014C8F8, // AnimationCallback
		0x8014C938, // IASACallback
		0x8014C974, // PhysicsCallback
		0x8014CA4C, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 366 - SpecialAirS
	{
		308,        // AnimationID
		0x340412,   // StateFlags
		0x13,       // AttackID
		0x0,        // BitFlags
		0x8014C8F8, // AnimationCallback
		0x8014C938, // IASACallback
		0x8014C974, // PhysicsCallback
		0x8014CA4C, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 367 - SpecialAirS
	{
		309,        // AnimationID
		0x340412,   // StateFlags
		0x13,       // AttackID
		0x0,        // BitFlags
		0x8014C8F8, // AnimationCallback
		0x8014C938, // IASACallback
		0x8014C974, // PhysicsCallback
		0x8014CA4C, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 368 - SpecialAirS
	{
		310,        // AnimationID
		0x340412,   // StateFlags
		0x13,       // AttackID
		0x0,        // BitFlags
		0x8014C8F8, // AnimationCallback
		0x8014C938, // IASACallback
		0x8014C974, // PhysicsCallback
		0x8014CA4C, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 369 - SpecialAirS
	{
		311,        // AnimationID
		0x340412,   // StateFlags
		0x13,       // AttackID
		0x0,        // BitFlags
		0x8014C8F8, // AnimationCallback
		0x8014C938, // IASACallback
		0x8014C974, // PhysicsCallback
		0x8014CA4C, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 370 - SpecialAirS
	{
		312,        // AnimationID
		0x340412,   // StateFlags
		0x13,       // AttackID
		0x0,        // BitFlags
		0x8014C8F8, // AnimationCallback
		0x8014C938, // IASACallback
		0x8014C974, // PhysicsCallback
		0x8014CA4C, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 371 - SpecialAirS
	{
		313,        // AnimationID
		0x340412,   // StateFlags
		0x13,       // AttackID
		0x0,        // BitFlags
		0x8014C8F8, // AnimationCallback
		0x8014C938, // IASACallback
		0x8014C974, // PhysicsCallback
		0x8014CA4C, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 372 - SpecialAirS
	{
		314,        // AnimationID
		0x340412,   // StateFlags
		0x13,       // AttackID
		0x0,        // BitFlags
		0x8014C8F8, // AnimationCallback
		0x8014C938, // IASACallback
		0x8014C974, // PhysicsCallback
		0x8014CA4C, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 373 - SpecialHi
	{
		315,        // AnimationID
		0x340013,   // StateFlags
		0x14,       // AttackID
		0x0,        // BitFlags
		0x8014E1F8, // AnimationCallback
		0x8014E290, // IASACallback
		0x8014E374, // PhysicsCallback
		0x8014E3B4, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 374 - SpecialAirHi
	{
		316,        // AnimationID
		0x340413,   // StateFlags
		0x14,       // AttackID
		0x0,        // BitFlags
		0x8014E218, // AnimationCallback
		0x8014E2B0, // IASACallback
		0x8014E394, // PhysicsCallback
		0x8014E3D4, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 375 - SpecialLw
	{
		317,        // AnimationID
		0x3C0014,   // StateFlags
		0x15,       // AttackID
		0x0,        // BitFlags
		0x8014D014, // AnimationCallback
		specialLw_iasaCallback, // IASACallback ------------------------------------ MODIFIED -------------------------------------------
		0x8014D31C, // PhysicsCallback
		0x8014D3B4, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 376 - SpecialLwCatch
	{
		318,        // AnimationID
		0x340014,   // StateFlags
		0x15,       // AttackID
		0x0,        // BitFlags
		0x8014D6B4, // AnimationCallback
		0x8014D834, // IASACallback
		0x8014D83C, // PhysicsCallback
		0x8014D87C, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 377 - SpecialLwShoot
	{
		319,        // AnimationID
		0x340014,   // StateFlags
		0x15,       // AttackID
		0x0,        // BitFlags
		0x8014DA60, // AnimationCallback
		0x8014DB80, // IASACallback
		0x8014DB88, // PhysicsCallback
		0x8014DBC8, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 378 - SpecialAirLw
	{
		320,        // AnimationID
		0x3C0414,   // StateFlags
		0x15,       // AttackID
		0x0,        // BitFlags
		0x8014D0E0, // AnimationCallback
		specialAirLw_iasaCallback, // IASACallback ------------------------------------ MODIFIED -------------------------------------------
		0x8014D350, // PhysicsCallback
		0x8014D3F0, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 379 - SpecialAirLwCatch
	{
		321,        // AnimationID
		0x340414,   // StateFlags
		0x15,       // AttackID
		0x0,        // BitFlags
		0x8014D774, // AnimationCallback
		0x8014D838, // IASACallback
		0x8014D85C, // PhysicsCallback
		0x8014D8B8, // CollisionCallback
		0x800761C8, // CameraCallback
	},
	// State: 380 - SpecialAirLwShoot
	{
		322,        // AnimationID
		0x340414,   // StateFlags
		0x15,       // AttackID
		0x0,        // BitFlags
		0x8014DAF0, // AnimationCallback
		0x8014DB84, // IASACallback
		0x8014DBA8, // PhysicsCallback
		0x8014DC04, // CollisionCallback
		0x800761C8, // CameraCallback
	},
};
