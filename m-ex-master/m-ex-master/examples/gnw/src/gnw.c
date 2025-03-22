#include "gnw.h"
#include "special_lw.c"

// ^ Include the gnw.h header file to access mex.h, and the function signatures for special_lw
// ^ Include the special_lw.c c file to import the functions defined in there to this primary file


// The move logic struct, copied from mexTool.
// It contains a list of the fighter's special states and what callbacks/data to use for them
// In this example, we replace the IASA (interruptible as soon as) callback for ground & air down special at lines 430, and 465
// When creating fully custom states though, often many fields such as the 
// AnimationID, AnimationCallback, IASACallback, PhysicsCallback, and CollisionCallback are completely changed and replaced with custom functions
__attribute__((used))
static struct FtState move_logic[] = {
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
		specialLw_iasaCallback, // IASACallback
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
		specialAirLw_iasaCallback, // IASACallback
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
