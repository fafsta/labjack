#include "CLabjack.h"
#include "LabJackUD.h"


LabjackU3::LabjackU3() {
	this->lngHandle = 0;
	this->is_open = false;
}

double LabjackU3::get_driver_version() const {
	return GetDriverVersion();
}

bool LabjackU3::Open() {
	if (!this->is_open) {
		// Å‰‚ÉŒ©‚Â‚©‚Á‚½Labjack‚ðŠJ‚­
		this->lngErrorcode = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", 1, &this->lngHandle);
		if (this->lngErrorcode == LJE_NOERROR) {
			this->is_open = true;
			//Start by using the pin_configuration_reset IOType so that all
			//pin assignments are in the factory default condition.
			lngErrorcode = ePut(this->lngHandle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);
		}
	} else {
		this->is_open = false;
	}
	return this->is_open;
}

void LabjackU3::CloseAll() {
	if (this->is_open) {
		Close();
	}
}

void LabjackU3::SetFIOAsAnalog(int pin_setting) {
	// Ý’è—á
	// pin_setting = b0000111100001111;
	// FIOƒsƒ“‚Ì 0~3,8*11‚ðAnalog‚ÉÝ’è‚·‚é
	this->lngErrorcode = ePut(this->lngHandle, LJ_ioPUT_ANALOG_ENABLE_PORT, 0, pin_setting, 16);
}

void LabjackU3::SetDAC(int pin, double volt) {
	AddRequest(this->lngHandle, LJ_ioPUT_DAC, pin, volt, 0, 0);
}

void LabjackU3::SetFIO(int pin, int level) {
	AddRequest(this->lngHandle, LJ_ioPUT_DIGITAL_BIT, pin, level, 0, 0);
}

void LabjackU3::ExecuteRequest() {

	Go();
}
 
