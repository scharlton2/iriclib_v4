#include "error_macros.h"
#include "h5cgnsparticlegroupimagesolution.h"
#include "iriclib_errorcodes.h"

#include "internal/iric_logger.h"

#include "private/h5cgnsparticlegroupimagesolution_impl.h"

#include <sstream>

using namespace iRICLib;

H5CgnsParticleGroupImageSolution::H5CgnsParticleGroupImageSolution(const std::string& name, hid_t groupId, H5CgnsZone* zone) :
	impl {new Impl {}}
{
	impl->m_name = name;
	impl->m_groupId = groupId;
	impl->m_zone = zone;
}

H5CgnsParticleGroupImageSolution::~H5CgnsParticleGroupImageSolution()
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Gclose");
	herr_t status = H5Gclose(impl->m_groupId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Gclose");

	if (status < 0) {
		_iric_logger_error("H5CgnsParticleGroupImageSolution::~H5CgnsParticleGroupImageSolution", "H5Gclose", status);
	}

	delete impl;
}

std::string H5CgnsParticleGroupImageSolution::name() const
{
	return impl->m_name;
}

int H5CgnsParticleGroupImageSolution::readGroupNames(std::vector<std::string>* names) const
{
	std::string coordXSuffix = "_coordinateX";
	std::vector<std::string> tmpNames;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
	int ier = H5Util::getGroupNames(impl->m_groupId, &tmpNames);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);
	RETURN_IF_ERR;

	for (const auto& name : tmpNames) {
		auto offset = static_cast<int> (name.length()) - static_cast<int> (coordXSuffix.length());
		if (offset < 0) {continue;}

		auto suffix = name.substr(offset, coordXSuffix.length());
		if (suffix != coordXSuffix) {continue;}

		names->push_back(name.substr(0, offset));
	}

	return IRIC_NO_ERROR;
}

int H5CgnsParticleGroupImageSolution::count(const std::string& groupName, int* count)
{
	std::ostringstream ss;
	ss << groupName << "_coordinateX";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayLength");
	int ier = H5Util::readDataArrayLength(impl->m_groupId, ss.str(), count);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayLength", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleGroupImageSolution::readCoordinatesX(const std::string& groupName, std::vector<double>* values) const
{
	std::ostringstream ss;
	ss << groupName << "_coordinateX";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, ss.str(), values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleGroupImageSolution::readCoordinatesY(const std::string& groupName, std::vector<double>* values) const
{
	std::ostringstream ss;
	ss << groupName << "_coordinateY";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, ss.str(), values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleGroupImageSolution::readSize(const std::string& groupName, std::vector<double>* values) const
{
	std::ostringstream ss;
	ss << groupName << "_size";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, ss.str(), values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}


int H5CgnsParticleGroupImageSolution::readAngle(const std::string& groupName, std::vector<double>* values) const
{
	std::ostringstream ss;
	ss << groupName << "_angle";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, ss.str(), values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}


void H5CgnsParticleGroupImageSolution::writeBegin(const std::string& groupName)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsParticleGroupImageSolution::Impl::clear");
	impl->clear();
	_IRIC_LOGGER_TRACE_CALL_END("H5CgnsParticleGroupImageSolution::Impl::clear");

	impl->m_groupName = groupName;
}

int H5CgnsParticleGroupImageSolution::writeEnd()
{
	std::ostringstream ss;
	int ier;

	// coordinateX
	ss.str("");
	ss << impl->m_groupName << "_coordinateX";

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createDataArray");
	ier = H5Util::createDataArray(impl->m_groupId, ss.str(), impl->m_coordinateX);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createDataArray", ier);
	RETURN_IF_ERR;

	// coordinateY
	ss.str("");
	ss << impl->m_groupName << "_coordinateY";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createDataArray");
	ier = H5Util::createDataArray(impl->m_groupId, ss.str(), impl->m_coordinateY);
	RETURN_IF_ERR;

	// size
	ss.str("");
	ss << impl->m_groupName << "_size";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createDataArray");
	ier = H5Util::createDataArray(impl->m_groupId, ss.str(), impl->m_size);
	RETURN_IF_ERR;

	// angle
	ss.str("");
	ss << impl->m_groupName << "_angle";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createDataArray");
	ier = H5Util::createDataArray(impl->m_groupId, ss.str(), impl->m_angle);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

void H5CgnsParticleGroupImageSolution::writePos2d(double x, double y, double size, double angle)
{
	impl->m_coordinateX.push_back(x);
	impl->m_coordinateY.push_back(y);
	impl->m_size.push_back(size);
	impl->m_angle.push_back(angle);
}

H5CgnsZone* H5CgnsParticleGroupImageSolution::zone() const
{
	return impl->m_zone;
}
