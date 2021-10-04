#include "iriclib.h"
#include "iriclib_errorcodes.h"
#include "iriclib_solution.h"

#include <Poco/File.h>

#include <iostream>
#include <cstdlib>

int iRIC_Check_Cancel()
{
	Poco::File f(".cancel");

	if (f.exists()) {
		std::cout << "Solver is stopped because the STOP button was clicked." << std::endl;
		exit(0);
	}

	return IRIC_NO_ERROR;
}

int cg_iRIC_Check_Update(int fid)
{
	return cg_iRIC_Write_Sol_End(fid);
}
