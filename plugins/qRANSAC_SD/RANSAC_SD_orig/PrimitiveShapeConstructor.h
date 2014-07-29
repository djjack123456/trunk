#ifndef PRIMITIVESHAPECONSTRUCTOR_HEADER
#define PRIMITIVESHAPECONSTRUCTOR_HEADER
#include "PrimitiveShape.h"
#include "PointCloud.h"
#include <MiscLib/Vector.h>
#include <istream>
#include <stdio.h>
#include <memory>

#ifndef DLL_LINKAGE
#define DLL_LINKAGE
#endif

#ifdef WIN32
#ifndef DEPRECATED
#define DEPRECATED __declspec(deprecated)
#endif
#else
#define DEPRECATED
#endif

class DLL_LINKAGE PrimitiveShapeConstructor
{
	public:
		virtual size_t Identifier() const = 0;
		virtual unsigned int RequiredSamples() const = 0;
		virtual std::shared_ptr<PrimitiveShape> Construct(const MiscLib::Vector< Vec3f > &points,
			const MiscLib::Vector< Vec3f > &normals) const = 0;
		virtual std::shared_ptr<PrimitiveShape> Construct(
			const MiscLib::Vector< Vec3f > &samples) const = 0;
		virtual std::shared_ptr<PrimitiveShape> Deserialize(std::istream *i,
			bool binary = true) const = 0;
		virtual size_t SerializedSize() const = 0; // returns the serialized size excluding the identifier byte
};

#endif
