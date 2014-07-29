#include "TorusPrimitiveShapeConstructor.h"
#include "TorusPrimitiveShape.h"
#include "ScoreComputer.h"
#include <GfxTL/NullClass.h>

size_t TorusPrimitiveShapeConstructor::Identifier() const
{
	return 4;
}

unsigned int TorusPrimitiveShapeConstructor::RequiredSamples() const
{
	return 4;
}

std::shared_ptr<PrimitiveShape> TorusPrimitiveShapeConstructor::Construct(
	const MiscLib::Vector< Vec3f > &points,
	const MiscLib::Vector< Vec3f > &normals) const
{
	MiscLib::Vector< Vec3f > samples;
	for(size_t i = 0; i < points.size(); ++i)
		samples.push_back(points[i]);
	for(size_t i = 0; i < normals.size(); ++i)
		samples.push_back(normals[i]);
	return Construct(samples);
}

std::shared_ptr<PrimitiveShape> TorusPrimitiveShapeConstructor::Construct(
	const MiscLib::Vector< Vec3f > &samples) const
{
	Torus torus;
	if(!torus.Init(samples))
		return NULL;
	return std::make_shared<TorusPrimitiveShape>(torus);
}

std::shared_ptr<PrimitiveShape> TorusPrimitiveShapeConstructor::Deserialize(std::istream *i,
	bool binary) const
{
	std::shared_ptr<TorusPrimitiveShape> shape(new TorusPrimitiveShape());
	shape->Deserialize(i, binary);
	return shape;
}

size_t TorusPrimitiveShapeConstructor::SerializedSize() const
{
	return Torus::SerializedSize() +
		TorusPrimitiveShape::ParametrizationType::SerializedSize();
}
