#ifndef TORUSPRIMITIVESHAPECONSTRUCTOR_HEADER
#define TORUSPRIMITIVESHAPECONSTRUCTOR_HEADER
#include "PrimitiveShapeConstructor.h"

#ifndef DLL_LINKAGE
#define DLL_LINKAGE
#endif

class DLL_LINKAGE TorusPrimitiveShapeConstructor
: public PrimitiveShapeConstructor
{
public:
	size_t Identifier() const;
	unsigned int RequiredSamples() const;
	std::shared_ptr<PrimitiveShape> Construct(const MiscLib::Vector< Vec3f > &points,
		const MiscLib::Vector< Vec3f > &normals) const;
	std::shared_ptr<PrimitiveShape> Construct(const MiscLib::Vector< Vec3f > &samples) const;
	std::shared_ptr<PrimitiveShape> Deserialize(std::istream *i, bool binary = true) const;
	size_t SerializedSize() const;
};

#endif
