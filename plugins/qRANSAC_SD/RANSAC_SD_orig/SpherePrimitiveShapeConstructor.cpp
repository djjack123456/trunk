#include "SpherePrimitiveShapeConstructor.h"
#include "SpherePrimitiveShape.h"
#include "ScoreComputer.h"
#include <GfxTL/NullClass.h>

SpherePrimitiveShapeConstructor::SpherePrimitiveShapeConstructor(
	float maxSphereRadius)
: m_maxSphereRadius(maxSphereRadius)
{}

size_t SpherePrimitiveShapeConstructor::Identifier() const
{
	return 1;
}

unsigned int SpherePrimitiveShapeConstructor::RequiredSamples() const
{
	// we use only 2pts with normals
	return 2;//4;
}

std::shared_ptr<PrimitiveShape> SpherePrimitiveShapeConstructor::Construct(
	const MiscLib::Vector< Vec3f > &points,
	const MiscLib::Vector< Vec3f > &normals) const
{
	Sphere sphere;
	if(!sphere.Init2(points[0], points[1], normals[0], normals[1]))//points[2], points[3]))
		return nullptr;
	if(sphere.Radius() > m_maxSphereRadius)
		return nullptr;
	return std::make_shared<SpherePrimitiveShape>(sphere);
}

std::shared_ptr<PrimitiveShape> SpherePrimitiveShapeConstructor::Construct(
	const MiscLib::Vector< Vec3f > &samples) const
{
	Sphere sphere;
	if(!sphere.Init(samples))
		return nullptr;
	return std::make_shared<SpherePrimitiveShape>(sphere);
}

std::shared_ptr<PrimitiveShape> SpherePrimitiveShapeConstructor::Deserialize(std::istream *i,
	bool binary) const
{
	std::shared_ptr<SpherePrimitiveShape> shape(new SpherePrimitiveShape());
	shape->Deserialize(i, binary);
	return shape;
}

size_t SpherePrimitiveShapeConstructor::SerializedSize() const
{
	return Sphere::SerializedSize()
		+ SpherePrimitiveShape::ParametrizationType::SerializedSize();
}
