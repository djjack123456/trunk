#include "ConePrimitiveShapeConstructor.h"
#include "ConePrimitiveShape.h"
#include "Cone.h"
#include "ScoreComputer.h"
#include <GfxTL/NullClass.h>

size_t ConePrimitiveShapeConstructor::Identifier() const
{
	return 3;
}

unsigned int ConePrimitiveShapeConstructor::RequiredSamples() const
{
	return 3;
}

std::shared_ptr<PrimitiveShape> ConePrimitiveShapeConstructor::Construct(
	const MiscLib::Vector< Vec3f > &points,
	const MiscLib::Vector< Vec3f > &normals) const
{
	Cone cone;
	if(!cone.Init(points[0], points[1], points[2], normals[0], normals[1],
		normals[2]))
		return nullptr;
	if(cone.Angle() > 1.4835298641951801403851371532153)
		// do not allow cones with an opening angle of more than 85 degrees
		return nullptr;
	return std::make_shared<ConePrimitiveShape>(cone);
}

std::shared_ptr<PrimitiveShape> ConePrimitiveShapeConstructor::Construct(
	const MiscLib::Vector< Vec3f > &samples) const
{
	Cone cone;
	if(!cone.Init(samples))
		return nullptr;
	return std::make_shared<ConePrimitiveShape>(cone);
}

std::shared_ptr<PrimitiveShape> ConePrimitiveShapeConstructor::Deserialize(std::istream *i,
	bool binary) const
{
	Cone cone;
	cone.Init(binary, i);
	std::shared_ptr<ConePrimitiveShape> shape(new ConePrimitiveShape(cone));
	return shape;
}

size_t ConePrimitiveShapeConstructor::SerializedSize() const
{
	return Cone::SerializedSize();
}
