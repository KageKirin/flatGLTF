#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFapi.hpp"

#include "glTFinternal.hpp"

#define KHUTILS_ASSERTION_INLINE

#include "khutils/assertion.hpp"
#include "khutils/runtime_exceptions.hpp"

namespace glTF_2_0
{
	//-------------------------------------------------------------------------

	SamplerT* const createSampler_withDefaults(Document* const doc)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto sam = createSampler(doc);
		KHUTILS_ASSERT_PTR(sam);

		sam->magFilter = SamplerFilter::LINEAR;
		sam->minFilter = SamplerFilter::LINEAR;
		sam->wrapS	 = WrapMode::CLAMP_TO_EDGE;
		sam->wrapT	 = WrapMode::CLAMP_TO_EDGE;

		return sam;
	}

	//---

	TextureT* const createTexture(Document* const doc, ImageT* const image)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(image);

		auto tex = createTexture(doc, (image->uri + "tex").c_str());
		KHUTILS_ASSERT_PTR(tex);
		tex->source = getId(doc, image);

		return tex;
	}

	//---

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
