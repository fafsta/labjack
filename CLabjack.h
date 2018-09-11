#pragma once

#include <Windows.h>

class LabjackU3 {
public:
	LabjackU3();
	double get_driver_version() const;

	bool Open();
	void CloseAll();
	void SetFIOAsAnalog(int pin_setting);

	void SetDAC(int pin, double volt);
	void SetFIO(int pin, int level); // 1:high 0:low
	void ExecuteRequest();


private:
	long lngErrorcode;
	double dblDriverVersion;
	long lngHandle = 0;
	bool is_open;
};