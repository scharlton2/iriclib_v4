#include "h5cgnsparticlegroupimagesolution_impl.h"

using namespace iRICLib;

H5CgnsParticleGroupImageSolution::Impl::Impl()
{}

void H5CgnsParticleGroupImageSolution::Impl::clear()
{
	m_coordinateX.clear();
	m_coordinateY.clear();
	m_size.clear();
	m_angle.clear();
}
