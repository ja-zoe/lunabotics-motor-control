#define Phoenix_No_WPI // remove WPI dependencies
#include "ctre/Phoenix.h"
#include "ctre/phoenix/platform/Platform.hpp"
#include "ctre/phoenix/unmanaged/Unmanaged.h"
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <SDL2/SDL.h>

#include "config.h"

using namespace ctre::phoenix;
using namespace ctre::phoenix::platform;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;

/* make some talons for drive train */
std::string interface = "can0";
TalonSRX talLeft{TALON_L_CAN_ID, interface};
// TalonSRX talRght{TALON_R_CAN_ID, interface};

VictorSPX vicLeft{VICTOR_L_CAN_ID, interface};
// VictorSPX vicRight{VICTOR_R_CAN_ID, interface};

void initDrive()
{
  vicLeft.Set(ControlMode::Follower, TALON_L_CAN_ID);  
  // vicRight.Set(ControlMode::Follower, TALON_R_CAN_ID);  
}

void drive(double fwd, double turn)
{
	double left = fwd - turn;
	double rght = fwd + turn; /* positive turn means turn robot LEFT */

	talLeft.Set(ControlMode::PercentOutput, left);
	// talRght.Set(ControlMode::PercentOutput, rght);
}
/** simple wrapper for code cleanup */
void sleepApp(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int main() {	
	// Comment out the call if you would rather use the automatically running diag-server, note this requires uninstalling diagnostics from Tuner. 
	// c_SetPhoenixDiagnosticsStartTime(-1); // disable diag server, instead we will use the diag server stand alone application that Tuner installs

	/* setup drive */
	initDrive();

	while (true) {
		/* we are looking for gamepad (first time or after disconnect),
		   neutral drive until gamepad (re)connected. */
		drive(0.1, 0);
    sleepApp(2000);
		drive(0.2, 0);
    sleepApp(2000);
		drive(0.3, 0);
    sleepApp(2000);
		drive(0, 0);
    sleepApp(2000);
	}

	SDL_Quit();
	return 0;
}
