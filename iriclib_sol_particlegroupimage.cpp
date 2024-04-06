#include "error_macros.h"
#include "h5cgnsparticlegroupimagesolution.h"
#include "h5cgnszone.h"
#include "iriclib_errorcodes.h"
#include "iriclib_sol_particlegroupimage.h"
#include "vectorutil.h"

#include "internal/iric_logger.h"
#include "internal/iric_util.h"

using namespace iRICLib;

namespace {

int getParticleGroupImageSolutionForRead(int fid, int gid, int step, H5CgnsParticleGroupImageSolution** solution, const std::string& f_name)
{
	H5CgnsZone* zone = nullptr;
	int ier = _iric_get_zone_for_solread(fid, gid, step, &zone, f_name);
	RETURN_IF_ERR;

	*solution = zone->particleGroupImageSolution();
	return IRIC_NO_ERROR;
}

int getParticleGroupImageSolutionForWrite(int fid, int gid, H5CgnsParticleGroupImageSolution** solution, const std::string& f_name)
{
	H5CgnsZone* zone = nullptr;
	int ier = _iric_get_zone_for_solwrite(fid, gid, &zone, f_name);
	RETURN_IF_ERR;

	*solution = zone->particleGroupImageSolution();
	return IRIC_NO_ERROR;
}

} // namespace

int cg_iRIC_Read_Sol_ParticleGroupImage_Count_WithGridId(int fid, int gid, int step, const char* groupname, int* count)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsParticleGroupImageSolution* solution = nullptr;
	int ier = getParticleGroupImageSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_ParticleGroupImage_Count_WithGridId");
	RETURN_IF_ERR;

	ier = solution->count(groupname, count);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_ParticleGroupImage_Pos2d_WithGridId(int fid, int gid, int step, const char* groupname, double* x_arr, double* y_arr, double* size_arr, double* angle_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsParticleGroupImageSolution* solution = nullptr;
	int ier = getParticleGroupImageSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_ParticleGroupImage_Pos2d_WithGridId");
	RETURN_IF_ERR;

	std::vector<double> xvec, yvec, sizevec, anglevec;
	ier = solution->readCoordinatesX(groupname, &xvec);
	RETURN_IF_ERR;
	ier = solution->readCoordinatesY(groupname, &yvec);
	RETURN_IF_ERR;
	ier = solution->readSize(groupname, &sizevec);
	RETURN_IF_ERR;
	ier = solution->readAngle(groupname, &anglevec);
	RETURN_IF_ERR;

	_vectorToPointerT(xvec, x_arr);
	_vectorToPointerT(yvec, y_arr);
	_vectorToPointerT(sizevec, size_arr);
	_vectorToPointerT(anglevec, angle_arr);

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_ParticleGroupImage_GroupBegin_WithGridId(int fid, int gid, const char* groupname)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsParticleGroupImageSolution* solution = nullptr;
	int ier = getParticleGroupImageSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_ParticleGroupImage_GroupBegin_WithGridId");
	RETURN_IF_ERR;

	solution->writeBegin(groupname);

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_ParticleGroupImage_GroupEnd_WithGridId(int fid, int gid)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsParticleGroupImageSolution* solution = nullptr;
	int ier = getParticleGroupImageSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_ParticleGroupImage_GroupEnd_WithGridId");
	RETURN_IF_ERR;

	ier = solution->writeEnd();
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_ParticleGroupImage_Pos2d_WithGridId(int fid, int gid, double x, double y, double size, double angle)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsParticleGroupImageSolution* solution = nullptr;
	int ier = getParticleGroupImageSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_ParticleGroupImage_Pos2d_WithGridId");
	RETURN_IF_ERR;

	solution->writePos2d(x, y, size, angle);

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}
