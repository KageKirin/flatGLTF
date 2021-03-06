#include <string>

extern const std::string flatgltf_2_0_schema; // for linker happiness
const std::string flatgltf_2_0_schema =
std::string(R"(// glTF 2.0


file_identifier "glTF";
file_extension "glf";

namespace glTF_2_0;

///----------------------------------------------------------------------------
/// The datatype of components in the attribute.
/// gltf_detailedDescription: The datatype of components in the attribute.  All valid values correspond to WebGL enums.  The corresponding typed arrays are `Int8Array`, `Uint8Array`, `Int16Array`, `Uint16Array`, `Uint32Array`, and `Float32Array`, respectively.  5125 (UNSIGNED_INT) is only allowed when the accessor contains indices, i.e., the accessor is only referenced by `primitive.indices`.
/// gltf_webgl: `vertexAttribPointer()` type parameter
enum ComponentType: int { //TODO: promote to top
	BYTE = 5120,
	UNSIGNED_BYTE = 5121,
	SHORT = 5122,
	UNSIGNED_SHORT = 5123,
	UNSIGNED_INT = 5125,
	FLOAT = 5126,
}

/// "description": "Specifies if the attribute is a scalar, vector, or matrix."
enum AccessorType: short { //string
	SCALAR,
	VEC2,
	VEC3,
	VEC4,
	MAT2,
	MAT3,
	MAT4,
	__UNSET,
}

///-- accessor.sparse.indices.schema.json
table AccessorSparseIndices {
	/// "description": "The index of the bufferView with sparse indices. Referenced bufferView can't have ARRAY_BUFFER or ELEMENT_ARRAY_BUFFER target."
	bufferView: int = -1; //glTFid

	/// "description": "The offset relative to the start of the bufferView in bytes. Must be aligned."
	byeOffset: int  = 0; //uint

	componentType: int = -1;	//ComponentType = UNSIGNED_BYTE;

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
}
///-- accessor.sparse.indices.schema.json --/

///-- accessor.sparse.values.schema.json
table AccessorSparseValues {
	/// "description": "The index of the bufferView with sparse values. Referenced bufferView can't have ARRAY_BUFFER or ELEMENT_ARRAY_BUFFER target."
	bufferView: int = -1; //glTFid

	/// "description": "The offset relative to the start of the bufferView in bytes. Must be al)") +
std::string(R"(igned."
	byteOffset: int = 0; //uint

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
}
///-- accessor.sparse.values.schema.json --/


///-- accessor.sparse.schema.json
/// Accessor Sparse
table AccessorSparse {
	/// "description": "Number of entries stored in the sparse array."
	/// "gltf_detailedDescription": "The number of attributes encoded in this sparse accessor."
	/// "minimum": 1
	count: int; //uint

	/// "description": "Index array of size `count` that points to those accessor attributes that deviate from their initialization value. Indices must strictly increase."
	indices: [AccessorSparseIndices](required);

	/// "description": "Array of size `count` times number of components, storing the displaced accessor attributes pointed by `indices`. Substituted values must have the same `componentType` and number of components as the base accessor."
	values: [AccessorSparseValues](required);

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
}
///-- accessor.sparse.schema.json --/

//-- accessor.schema.json
/// A typed view into a bufferView.  A bufferView contains raw binary data.  An accessor provides a typed view into a bufferView or a subset of a bufferView similar to how WebGL's `vertexAttribPointer()` defines an attribute in a buffer.
table Accessor 
{
	/// "description": "The index of the bufferView."
	/// "gltf_detailedDescription": "The index of the bufferView. When not defined, accessor must be initialized with zeros; `sparse` property or extensions could override zeros with actual values."    
	bufferView: int = -1; //glTFid
	
	/// "description": "The offset relative to the start of the bufferView in bytes."
	/// "gltf_detailedDescription": "The offset relative to the start of the bufferView in bytes. )") +
std::string(R"( This must be a multiple of the size of the component datatype."
	/// "gltf_webgl": "`vertexAttribPointer()` offset parameter"
	byteOffset: int = 0; //uint

	/// "description": "The datatype of components in the attribute."
	/// "gltf_detailedDescription": "The datatype of components in the attribute.  All valid values correspond to WebGL enums.  The corresponding typed arrays are `Int8Array`, `Uint8Array`, `Int16Array`, `Uint16Array`, `Uint32Array`, and `Float32Array`, respectively.  5125 (UNSIGNED_INT) is only allowed when the accessor contains indices, i.e., the accessor is only referenced by `primitive.indices`."
	/// "gltf_webgl": "`vertexAttribPointer()` type parameter"
	componentType: int = -1;	//ComponentType = UNSIGNED_BYTE;

	/// "description": "Specifies whether integer data values should be normalized."
	/// "gltf_detailedDescription": "Specifies whether integer data values should be normalized (`true`) to [0, 1] (for unsigned types) or [-1, 1] (for signed types), or converted directly (`false`) when they are accessed. This property is defined only for accessors that contain vertex attributes or animation output data."
	/// "gltf_webgl": "`vertexAttribPointer()` normalized parameter"
	normalized: bool = false;

	/// "description": "The number of attributes referenced by this accessor."
	/// "gltf_detailedDescription": "The number of attributes referenced by this accessor, not to be confused with the number of bytes or number of components."
	count: int = 1; //uint 

	/// "description": "Specifies if the attribute is a scalar, vector, or matrix."
	type: AccessorType = __UNSET;
	
	///  "description": "Maximum value of each component in this attribute."
	/// "minItems": 1,
	/// "maxItems": 16,
	/// "gltf_detailedDescription": "Maximum value of each component in this attribute.  Array elements must be treated as having the same data type as accessor's `componentType`. Both min and max arrays have the same length.  The length is determined by the value of the type property; it can be 1, 2, 3, 4, 9,)") +
std::string(R"( or 16.\n\n`normalized` property has no effect on array values: they always correspond to the actual values stored in the buffer. When accessor is sparse, this property must contain max values of accessor data with sparse substitution applied."
	max: [float]; // Number

	/// "description": "Minimum value of each component in this attribute."
	/// "minItems": 1,
	/// "maxItems": 16,
	/// "gltf_detailedDescription": "Minimum value of each component in this attribute.  Array elements must be treated as having the same data type as accessor's `componentType`. Both min and max arrays have the same length.  The length is determined by the value of the type property; it can be 1, 2, 3, 4, 9, or 16.\n\n`normalized` property has no effect on array values: they always correspond to the actual values stored in the buffer. When accessor is sparse, this property must contain min values of accessor data with sparse substitution applied."
	min: [float]; // Number
	
	/// "description": "Sparse storage of attributes that deviate from their initialization value."
	sparse: [AccessorSparse];

	///-- glTFChildOfRootProperty
	/// The user-defined name of this object.
	/// gltf_detailedDescription: The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.
	name: string;

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
	///-- glTFChildOfRootProperty --/
}
//-- accessor.schema.json --/

///----------------------------------------------------------------------------

///-- asset.schema.json
/// Asset
/// Metadata about the glTF asset.
table Asset 
{
	/// A copyright message suitable for display to credit the content creator.
	copyright: string;
	
	/// Tool that generated this glTF model.  Useful for debugging.
	generator: string;

	/// The glTF version that this asset )") +
std::string(R"(targets.
	/// pattern: "^[0-9]+\\.[0-9]+$"
	version: string(required);

	/// The minimum glTF version that this asset targets.
	/// pattern": "^[0-9]+\\.[0-9]+$
	minVersion: string;

	///-- glTFChildOfRootProperty
	/// The user-defined name of this object.
	/// gltf_detailedDescription: The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.
	name: string;

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
	///-- glTFChildOfRootProperty --/
}
///-- asset.schema.json --/

///----------------------------------------------------------------------------

///-- animation.channel.target.schema.json
/// "description": "The name of the node's TRS property to modify, or the \"weights\" of the Morph Targets it instantiates."
enum AnimationChannelTargetPath: short { //string
	translation,
	rotation,
	scale,
	weights,
}

/// Animation Channel Target
/// "description": "The index of the node and TRS property that an animation channel targets."
table AnimationChannelTarget {
	/// "description": "The index of the node to target."
	node: int = -1; //glTFid

	/// "description": "The name of the node's TRS property to modify, or the \"weights\" of the Morph Targets it instantiates."
	path: AnimationChannelTargetPath;

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
}
///-- animation.channel.target.schema.json --/


///-- animation.channel.schema.json
/// Animation Channel
/// "description": "Targets an animation's sampler at a node's property."
table AnimationChannel {
	/// "description": "The index of a sampler in this animation used to compute the value for the target."
	/// "gltf_detailedDescription": "The index)") +
std::string(R"( of a sampler in this animation used to compute the value for the target, e.g., a node's translation, rotation, or scale (TRS)."
	sampler: int = -1; //glTFid

	/// "description": "The index of the node and TRS property to target."
    target: AnimationChannelTarget(required);

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
}
///-- animation.channel.schema.json --/


///-- animation.sampler.schema.json
/// "description": "Interpolation algorithm."
/// "gltf_detailedDescription": "Interpolation algorithm."
enum AnimationSamplerInterpolationAlgorithm: short { // string
	/// "description": "The animated values are linearly interpolated between keyframes. When targeting a rotation, spherical linear interpolation (slerp) should be used to interpolate quaternions. The number output of elements must equal the number of input elements."
	LINEAR,
	/// "description": "The animated values remain constant to the output of the first keyframe, until the next keyframe. The number of output elements must equal the number of input elements."
	STEP,
	/// "description": "The animation's interpolation is computed using a uniform Catmull-Rom spline. The number of output elements must equal two more than the number of input elements. The first and last output elements represent the start and end tangents of the spline. There must be at least four keyframes when using this interpolation."
	CATMULLROMSPLINE,
	/// "description": "The animation's interpolation is computed using a cubic spline with specified tangents. The number of output elements must equal three times the number of input elements. For each input element, the output stores three elements, an in-tangent, a spline vertex, and an out-tangent. There must be at least two keyframes when using this interpolation."
	CUBICSPLINE,
}

/// Animation Sampler
/// "description": "Combines input and output accessors with an interpola)") +
std::string(R"(tion algorithm to define a keyframe graph (but not its target)."
table AnimationSampler {
	/// "description": "The index of an accessor containing keyframe input values, e.g., time."
	/// "gltf_detailedDescription": "The index of an accessor containing keyframe input values, e.g., time. That accessor must have componentType `FLOAT`. The values represent time in seconds with `time[0] >= 0.0`, and strictly increasing values, i.e., `time[n + 1] > time[n]`."
	input: int = -1; //glTFid

	/// "description": "Interpolation algorithm."
	/// "gltf_detailedDescription": "Interpolation algorithm."
	interpolation: AnimationSamplerInterpolationAlgorithm = LINEAR;

	/// "description": "The index of an accessor, containing keyframe output values."
	/// "gltf_detailedDescription": "The index of an accessor containing keyframe output values. When targeting TRS target, the `accessor.componentType` of the output values must be `FLOAT`. When targeting morph weights, the `accessor.componentType` of the output values must be `FLOAT` or normalized integer where each output element stores values with a count equal to the number of morph targets."
	output: int = -1; //glTFid

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
}
///-- animation.sampler.schema.json --/

///-- animation.schema.json
/// Animation
/// "description": "A keyframe animation."
table Animation {

	/// "description": "An array of channels, each of which targets an animation's sampler at a node's property. Different channels of the same animation can't have equal targets."
	channels: [AnimationChannel](required);

	/// "description": "An array of samplers that combines input and output accessors with an interpolation algorithm to define a keyframe graph (but not its target)."
	samplers: [AnimationSampler](required);

	///-- glTFChildOfRootProperty
	/// The user-defined name of this object.
	/// gltf_detailedDescrip)") +
std::string(R"(tion: The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.
	name: string;

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
	///-- glTFChildOfRootProperty --/
}
///-- animation.schema.json --/

///----------------------------------------------------------------------------

///-- buffer.schema.json
/// Buffer
/// "description": "A buffer points to binary geometry, animation, or skins."
table Buffer {
	/// "description": "The uri of the buffer."
	/// "format": "uriref"
	/// "gltf_detailedDescription": "The uri of the buffer.  Relative paths are relative to the .gltf file.  Instead of referencing an external file, the uri can also be a data-uri."
	/// "gltf_uriType": "application"
	uri: string;

	/// "description": "The length of the buffer in bytes."
	byteLength: int = 0; //uint

	///-- glTFChildOfRootProperty
	/// The user-defined name of this object.
	/// gltf_detailedDescription: The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.
	name: string;

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
	///-- glTFChildOfRootProperty --/
}
///-- buffer.schema.json --/

///----------------------------------------------------------------------------

///-- bufferView.schema.json

/// "description": "The target that the GPU buffer should be bound to."
/// "gltf_webgl": "`bindBuffer()`"
enum BufferViewTarget: int {
	ARRAY_BUFFER = 34962,
	ELEMENT_ARRAY_BUFFER = 34963,

	/// originally added for flatgltf
	UNIFORM_BUFFER = 35345,
}

/// Buffer View
/// "description": "A view into a buf)") +
std::string(R"(fer generally representing a subset of the buffer."
table BufferView {
	/// "description": "The index of the buffer."
	buffer: int = -1; //glTFid

	/// "description": "The offset into the buffer in bytes."
	byteOffset: int = 0; //uint

	// "description": "The length of the bufferView in bytes."
	// "minimum": 1
	byteLength: int; //uint
	
	/// "description": "The stride, in bytes."
	/// "minimum": 4
	/// "maximum": 252
	/// "multipleOf": 4
	/// "gltf_detailedDescription": "The stride, in bytes, between vertex attributes.  When this is not defined, data is tightly packed. When two or more accessors use the same bufferView, this field must be defined."
	/// "gltf_webgl": "`vertexAttribPointer()` stride parameter"
	byteStride: int; //uint
            
	/// "description": "The target that the GPU buffer should be bound to."
	/// "gltf_webgl": "`bindBuffer()`"     
    target: int = -1; // BufferViewTarget = UNIFORM_BUFFER;

	///-- glTFChildOfRootProperty
	/// The user-defined name of this object.
	/// gltf_detailedDescription: The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.
	name: string;

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
	///-- glTFChildOfRootProperty --/
}
///-- bufferView.schema.json --/

///----------------------------------------------------------------------------

///-- camera.orthographic.schema.json
/// Camera Orthographic
/// "description": "An orthographic camera containing properties to create an orthographic projection matrix."
table CameraOrthographic {
	/// "description": "The floating-point horizontal magnification of the view. Must not be zero."
	xmag: float;  // Number

	/// "description": "The floating-point vertical magnification of the view. Must not be zero."
    ymag: float; // Number

	/// "descripti)") +
std::string(R"(on": "The floating-point distance to the far clipping plane. `zfar` must be greater than `znear`."
    zfar: float; // Number

	/// "description": "The floating-point distance to the near clipping plane."
    znear: float; // Number

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
}
///-- camera.orthographic.schema.json --/

///-- camera.perspective.schema.json
/// Camera Perspective
/// "description": "A perspective camera containing properties to create a perspective projection matrix."
table CameraPerspective {
	/// "description": "The floating-point aspect ratio of the field of view."
	/// "gltf_detailedDescription": "The floating-point aspect ratio of the field of view. When this is undefined, the aspect ratio of the canvas is used."
	aspectRatio: float; // Number

	/// "description": "The floating-point vertical field of view in radians."
	yfov: float; // Number

	/// "description": "The floating-point distance to the far clipping plane."
	/// "gltf_detailedDescription": "The floating-point distance to the far clipping plane. When defined, `zfar` must be greater than `znear`. If `zfar` is undefined, runtime must use infinite projection matrix."
	zfar: float; // Number

	/// "description": "The floating-point distance to the near clipping plane."
	/// "gltf_detailedDescription": "The floating-point distance to the near clipping plane."
	znear: float; // Number

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
}
///-- camera.perspective.schema.json --/

///-- camera.schema.json
/// "description": "Specifies if the camera uses a perspective or orthographic projection."
/// "gltf_detailedDescription": "Specifies if the camera uses a perspective or orthographic projection.  Based on this, either the camera's `per)") +
std::string(R"(spective` or `orthographic` property will be defined."
enum CameraType: short {//string
	perspective,
	orthographic,
}

table Camera {
	/// "description": "An orthographic camera containing properties to create an orthographic projection matrix."
	orthographic: CameraOrthographic;

	/// "description": "A perspective camera containing properties to create a perspective projection matrix."
	perspective: CameraPerspective;

	/// "description": "Specifies if the camera uses a perspective or orthographic projection."
	/// "gltf_detailedDescription": "Specifies if the camera uses a perspective or orthographic projection.  Based on this, either the camera's `perspective` or `orthographic` property will be defined."
	type: CameraType;

	///-- glTFChildOfRootProperty
	/// The user-defined name of this object.
	/// gltf_detailedDescription: The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.
	name: string;

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
	///-- glTFChildOfRootProperty --/
}
///-- camera.schema.json --/

///----------------------------------------------------------------------------

///-- image.schema.json
/// Image
/// "description": "Image data used to create a texture. Image can be referenced by URI or `bufferView` index. `mimeType` is required in the latter case."
table Image {
	/// "description": "The uri of the image."
	/// "gltf_detailedDescription": "The uri of the image.  Relative paths are relative to the .gltf file.  Instead of referencing an external file, the uri can also be a data-uri.  The image format must be jpg or png."
	/// "gltf_uriType": "image"
	/// "format": "uriref"
	uri: string;

	/// "description": "The image's MIME type."
	/// NOTE: JsonSchema states enum { "image/jpeg" "image/png" }, but this type of va)") +
std::string(R"(riables are not possible with flatbuffers, hence keeping the mimeType as string
	mimeType: string;

	/// "description": "The index of the bufferView that contains the image. Use this instead of the image's uri property."
	bufferView: int = -1; //glTFid

	///-- glTFChildOfRootProperty
	/// The user-defined name of this object.
	/// gltf_detailedDescription: The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.
	name: string;

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
	///-- glTFChildOfRootProperty --/
}
///-- image.schema.json --/

///----------------------------------------------------------------------------

///-- textureInfo.schema.json
/// Texture Info
/// "description": "Reference to a texture."
table TextureInfo {
	/// "description": "The index of the texture."
	index: int = -1; //glTFId

	/// "description": "The set index of texture's TEXCOORD attribute used for texture coordinate mapping."
	/// "gltf_detailedDescription": "This integer value is used to construct a string in the format TEXCOORD_<set index> which is a reference to a key in mesh.primitives.attributes (e.g. A value of 0 corresponds to TEXCOORD_0)."
	texCoord: int; //uint

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
}
///-- textureInfo.schema.json --/

///----------------------------------------------------------------------------

///-- material.normalTextureInfo.schema.json
/// Material Normal Texture Info
table MaterialNormalTextureInfo {
    /// "description": "The scalar multiplier applied to each normal vector of the normal texture."
	/// "gltf_detailedDescription": "The scalar multiplier applied to each nor)") +
std::string(R"(mal vector of the texture. This value scales the normal vector using the formula: `scaledNormal =  normalize((normalize(<sampled normal texture value>) * 2.0 - 1.0) * vec3(<normal scale>, <normal scale>, 1.0))`. This value is ignored if normalTexture is not specified. This value is linear."
	scale: float = 1.0; // Number

	///-- TextureInfo
	/// "description": "The index of the texture."
	index: int = -1; //glTFId

	/// "description": "The set index of texture's TEXCOORD attribute used for texture coordinate mapping."
	/// "gltf_detailedDescription": "This integer value is used to construct a string in the format TEXCOORD_<set index> which is a reference to a key in mesh.primitives.attributes (e.g. A value of 0 corresponds to TEXCOORD_0)."
	texCoord: int; //uint

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
	///-- TextureInfo --/
}
///-- material.normalTextureInfo.schema.json --/

///-- material.occlusionTextureInfo.schema.json
/// Material Occlusion Texture Info
table MaterialOcclusionTextureInfo {
    /// "description": "A scalar multiplier controlling the amount of occlusion applied."
	/// "gltf_detailedDescription": "A scalar multiplier controlling the amount of occlusion applied. A value of 0.0 means no occlusion. A value of 1.0 means full occlusion. This value affects the resulting color using the formula: `occludedColor = lerp(color, color * <sampled occlusion texture value>, <occlusion strength>)`. This value is ignored if the corresponding texture is not specified. This value is linear.
	strength: float = 1.0; // Number

	///-- TextureInfo
	/// "description": "The index of the texture."
	index: int = -1; //glTFId

	/// "description": "The set index of texture's TEXCOORD attribute used for texture coordinate mapping."
	/// "gltf_detailedDescription": "This integer value is used to construct a string in the format TEXCOORD_<set index> which is a ref)") +
std::string(R"(erence to a key in mesh.primitives.attributes (e.g. A value of 0 corresponds to TEXCOORD_0)."
	texCoord: int; //uint

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
	///-- TextureInfo --/
}
///-- material.occlusionTextureInfo.schema.json --/

///-- material.pbrMetallicRoughness.schema.json
/// Material PBR Metallic Roughness
/// "description": "A set of parameter values that are used to define the metallic-roughness material model from Physically-Based Rendering (PBR) methodology."
table MaterialPbrMetallicRoughness {
	/// "description": "The material's base color factor."
	/// "gltf_detailedDescription": "The RGBA components of the base color of the material. The fourth component (A) is the alpha coverage of the material. The `alphaMode` property specifies how alpha is interpreted. These values are linear. If a baseColorTexture is specified, this value is multiplied with the texel values."
	/// "minItems": 4
	/// "maxItems": 4
	/// "default": [ 1.0, 1.0, 1.0, 1.0 ]
	baseColorFactor: [float]; // Number

	/// "description": "The base color texture."
	/// "gltf_detailedDescription": "The base color texture. This texture contains RGB(A) components in sRGB color space. The first three components (RGB) specify the base color of the material. If the fourth component (A) is present, it represents the alpha coverage of the material. Otherwise, an alpha of 1.0 is assumed. The `alphaMode` property specifies how alpha is interpreted. The stored texels must not be premultiplied."
	baseColorTexture: TextureInfo;
	
	/// "description": "The metalness of the material."
	/// "gltf_detailedDescription": "The metalness of the material. A value of 1.0 means the material is a metal. A value of 0.0 means the material is a dielectric. Values in between are for blending between metals and dielectrics such as dirty metallic surfaces. This value is linear. If a metallicRoughnessTextu)") +
std::string(R"(re is specified, this value is multiplied with the metallic texel values."
	// "minimum": 0.0
	// "maximum": 1.0
	// "default": 1.0
	metallicFactor: float = 1.0; // Number

	/// "description": "The roughness of the material."
	/// "gltf_detailedDescription": "The roughness of the material. A value of 1.0 means the material is completely rough. A value of 0.0 means the material is completely smooth. This value is linear. If a metallicRoughnessTexture is specified, this value is multiplied with the roughness texel values."
	/// "minimum": 0.0
	/// "maximum": 1.0
	/// "default": 1.0
	roughnessFactor: float = 1.0; // Number
	
	/// "description": "The metallic-roughness texture."
	/// "gltf_detailedDescription": "The metallic-roughness texture. The metalness values are sampled from the B channel. The roughness values are sampled from the G channel. These values are linear. If other channels are present (R or A), they are ignored for metallic-roughness calculations."
	metallicRoughnessTexture: TextureInfo;

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
}
///-- material.pbrMetallicRoughness.schema.json --/

///-- material.schema.json
/// "description": "The alpha rendering mode of the material."
/// "gltf_detailedDescription": "The material's alpha rendering mode enumeration specifying the interpretation of the alpha value of the main factor and texture."
enum MaterialAlphaMode: short {
	/// "description": "The alpha value is ignored and the rendered output is fully opaque."
	OPAQUE,
	
	/// "description": "The rendered output is either fully opaque or fully transparent depending on the alpha value and the specified alpha cutoff value."
	MASK,
	
	/// "description": "The alpha value is used to composite the source and destination areas. The rendered output is combined with the background using the normal painting operation (i.e. the Porter and Duff over operator)."
)") +
std::string(R"(	BLEND,
}

/// Material
/// "description": "The material appearance of a primitive."
table Material {
	/// "description": "A set of parameter values that are used to define the metallic-roughness material model from Physically-Based Rendering (PBR) methodology. When not specified, all the default values of `pbrMetallicRoughness` apply."
	pbrMetallicRoughness: MaterialPbrMetallicRoughness;

	/// "description": "The normal map texture."
	/// "gltf_detailedDescription": "A tangent space normal map. The texture contains RGB components in linear space. Each texel represents the XYZ components of a normal vector in tangent space. Red [0 to 255] maps to X [-1 to 1]. Green [0 to 255] maps to Y [-1 to 1]. Blue [128 to 255] maps to Z [1/255 to 1]. The normal vectors use OpenGL conventions where +X is right and +Y is up. +Z points toward the viewer. In GLSL, this vector would be unpacked like so: `float3 normalVector = tex2D(<sampled normal map texture value>, texCoord) * 2 - 1`."
	normalTexture: MaterialNormalTextureInfo;
	
	/// "description": "The occlusion map texture."
	/// "gltf_detailedDescription": "The occlusion map texture. The occlusion values are sampled from the R channel. Higher values indicate areas that should receive full indirect lighting and lower values indicate no indirect lighting. These values are linear. If other channels are present (GBA), they are ignored for occlusion calculations."
	occlusionTexture: MaterialOcclusionTextureInfo;

	/// "description": "The emissive map texture."
	/// "gltf_detailedDescription": "The emissive map controls the color and intensity of the light being emitted by the material. This texture contains RGB components in sRGB color space. If a fourth component (A) is present, it is ignored."
	emissiveTexture: TextureInfo;

	/// "description": "The emissive color of the material."
	/// "gltf_detailedDescription": "The RGB components of the emissive color of the material. These values are linear. If an emissiveTexture is specified, this value is multiplied with the texe)") +
std::string(R"(l values."
	/// "minItems": 3,
	/// "maxItems": 3,
	/// "default": [ 0.0, 0.0, 0.0 ],
	emissiveFactor: [float]; // Number
	
	/// "description": "The alpha rendering mode of the material."
	/// "gltf_detailedDescription": "The material's alpha rendering mode enumeration specifying the interpretation of the alpha value of the main factor and texture."
	alphaMode: MaterialAlphaMode = OPAQUE;

	/// "description": "The alpha cutoff value of the material."
	/// "gltf_detailedDescription": "Specifies the cutoff threshold when in `MASK` mode. If the alpha value is greater than or equal to this value then it is rendered as fully opaque, otherwise, it is rendered as fully transparent. A value greater than 1.0 will render the entire material as fully transparent. This value is ignored for other modes."
	alphaCutoff: float = 0.5; // Number

	/// "description": "Specifies whether the material is double sided."
	/// "gltf_detailedDescription": "Specifies whether the material is double sided. When this value is false, back-face culling is enabled. When this value is true, back-face culling is disabled and double sided lighting is enabled. The back-face must have its normals reversed before the lighting equation is evaluated."
	doubleSided: bool = false;

	///-- glTFChildOfRootProperty
	/// The user-defined name of this object.
	/// gltf_detailedDescription: The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.
	name: string;

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
	///-- glTFChildOfRootProperty --/
}
///-- material.schema.json --/

///----------------------------------------------------------------------------

///-- mesh.primitive.schema.json
enum MeshPrimitiveMode: ubyte {
	POINTS = 0,
	LINES = 1,
	LINE_LOOP = 2,
	LINE_STRIP = 3,
	TRIANGLES = )") +
std::string(R"(4,
	TRIANGLE_STRIP = 5,
	TRIANGLE_FAN = 6,
}

table MeshPrimitiveAttribute {
	id: string(key);
	value: int = -1; //glTFid
}

/// Mesh Primitive
/// "description": "Geometry to be rendered with the given material."
/// "gltf_webgl": "`drawElements()` and `drawArrays()`"
table MeshPrimitive {
	/// "description": "A dictionary object, where each key corresponds to mesh attribute semantic and each value is the index of the accessor containing attribute's data."
	///! NOTE: dictionary objects are not possible with flatbuffers (yet), hence this workaround
	attributes: [ubyte](flexbuffer, required);

	/// "description": "The index of the accessor that contains the indices."
	/// "gltf_detailedDescription": "The index of the accessor that contains mesh indices.  When this is not defined, the primitives should be rendered without indices using `drawArrays()`.  When defined, the accessor must contain indices: the `bufferView` referenced by the accessor should have a `target` equal to 34963 (ELEMENT_ARRAY_BUFFER); `componentType` must be 5121 (UNSIGNED_BYTE), 5123 (UNSIGNED_SHORT) or 5125 (UNSIGNED_INT), the latter may require enabling additional hardware support; `type` must be `\"SCALAR\"`. For triangle primitives, the front face has a counter-clockwise (CCW) winding order."
	indices: int = -1; //glTFid

	/// "description": "The index of the material to apply to this primitive when rendering."
	material: int = -1; //glTFid

	/// "description": "The type of primitives to render."
	/// "gltf_detailedDescription": "The type of primitives to render. All valid values correspond to WebGL enums."
	mode: MeshPrimitiveMode = TRIANGLES;

	/// "description": "An array of Morph Targets, each  Morph Target is a dictionary mapping attributes (only `POSITION`, `NORMAL`, and `TANGENT` supported) to their deviations in the Morph Target."
	/// "description": "A dictionary object specifying attributes displacements in a Morph Target, where each key corresponds to one of the three supported attribute semantic (`POSITION`, `NORMAL`, o)") +
std::string(R"(r `TANGENT`) and each value is the index of the accessor containing the attribute displacements' data."
	targets: [ubyte](flexbuffer);

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
}
///-- mesh.primitive.schema.json --/

///-- mesh.schema.json
/// Mesh
/// "description": "A set of primitives to be rendered.  A node can contain one mesh.  A node's transform places the mesh in the scene."
table Mesh {
	/// "description": "An array of primitives, each defining geometry to be rendered with a material."
	primitives: [MeshPrimitive](required);
	
	/// "description": "Array of weights to be applied to the Morph Targets."
	weights: [float]; // Number

	///-- glTFChildOfRootProperty
	/// The user-defined name of this object.
	/// gltf_detailedDescription: The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.
	name: string;

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
	///-- glTFChildOfRootProperty --/
}
///-- mesh.schema.json --/

///----------------------------------------------------------------------------

///-- node.schema.json
/// Node
/// "description": "A node in the node hierarchy.  When the node contains `skin`, all `mesh.primitives` must contain `JOINTS_0` and `WEIGHTS_0` attributes.  A node can have either a `matrix` or any combination of `translation`/`rotation`/`scale` (TRS) properties. TRS properties are converted to matrices and postmultiplied in the `T * R * S` order to compose the transformation matrix; first the scale is applied to the vertices, then the rotation, and then the translation. If none are provided, the transform is the identity. When a node is targeted for animatio)") +
std::string(R"(n (referenced by an animation.channel.target), only TRS properties may be present; `matrix` will not be present."
table Node {
	/// "description": "The index of the camera referenced by this node."
	camera: int = -1; //glTFid
	
	/// "description": "The indices of this node's children."
	children: [int]; //glTFid
	
	/// "description": "The index of the skin referenced by this node."
	skin: int = -1; //glTFid

	/// "description": "A floating-point 4x4 transformation matrix stored in column-major order."
	/// "gltf_detailedDescription": "A floating-point 4x4 transformation matrix stored in column-major order."
	/// "gltf_webgl": "`uniformMatrix4fv()` with the transpose parameter equal to false"
	/// "minItems": 16
	/// "maxItems": 16
	/// "default": [ 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 ],
	matrix: [float]; // Number
	
	/// "description": "The index of the mesh in this node."
	mesh: int = -1; //glTFid
	
	/// "description": "The node's unit quaternion rotation in the order (x, y, z, w), where w is the scalar."
	/// "minimum": -1.0
	/// "maximum": 1.0
	/// "minItems": 4
	/// "maxItems": 4
	/// "default": [ 0.0, 0.0, 0.0, 1.0 ]
	rotation: [float]; // Number
	
	/// "description": "The node's non-uniform scale."
	/// "minItems": 3
	/// "maxItems": 3
	/// "default": [ 1.0, 1.0, 1.0 ]
	scale: [float]; // Number
	
	/// "description": "The node's translation."
	/// "minItems": 3
	/// "maxItems": 3
	/// "default": [ 0.0, 0.0, 0.0 ]
	translation: [float]; // Number

	/// "description": "The weights of the instantiated Morph Target. Number of elements must match number of Morph Targets of used mesh."
	/// "minItems": 1
	weights: [float]; // Number
	
	///-- glTFChildOfRootProperty
	/// The user-defined name of this object.
	/// gltf_detailedDescription: The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.
	name: string;

	///-- glTFProperty
	/// Dictionary o)") +
std::string(R"(bject with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
	///-- glTFChildOfRootProperty --/
}
///-- node.schema.json --/

///----------------------------------------------------------------------------

///-- scene.schema.json
/// Scene
/// "description": "The root nodes of a scene."
table Scene {
	/// "description": "The indices of each root node."
	nodes: [int]; //glTFid

	///-- glTFChildOfRootProperty
	/// The user-defined name of this object.
	/// gltf_detailedDescription: The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.
	name: string;

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
	///-- glTFChildOfRootProperty --/
}
///-- scene.schema.json --/

///----------------------------------------------------------------------------

///-- sampler.schema.
/// "gltf_detailedDescription": "All valid values correspond to WebGL enums."
enum SamplerFilter: int {
	NEAREST = 9728,
	LINEAR = 9729,
	NEAREST_MIPMAP_NEAREST = 9984,
	LINEAR_MIPMAP_NEAREST = 9985,
	NEAREST_MIPMAP_LINEAR = 9986,
	LINEAR_MIPMAP_LINEAR = 9987,
}

/// "gltf_detailedDescription": "All valid values correspond to WebGL enums."
enum WrapMode: int {
	REPEAT = 10497,
	CLAMP_TO_EDGE = 33071,
	MIRRORED_REPEAT = 33648,
}

/// Sampler
/// "description": "Texture sampler properties for filtering and wrapping modes."
/// "gltf_webgl": "`texParameterf()`"
table Sampler {
	/// "description": "Magnification filter."
	/// "gltf_detailedDescription": "Magnification filter.  Valid values correspond to WebGL enums: `9728` (NEAREST) and `9729` (LINEAR)."
	/// "gltf_webgl": "`texParameterf()` with pname equal to TEXTURE_MAG_FILTER"
	magFilter: SamplerFilter = NEAREST;

	/// "description": )") +
std::string(R"("Minification filter."
	/// "gltf_detailedDescription": "Minification filter.  All valid values correspond to WebGL enums."
	/// "gltf_webgl": "`texParameterf()` with pname equal to TEXTURE_MIN_FILTER"
	minFilter: SamplerFilter = NEAREST;

	/// "description": "s wrapping mode."
	/// "gltf_detailedDescription": "s wrapping mode.  All valid values correspond to WebGL enums."
	/// "gltf_webgl": "`texParameterf()` with pname equal to TEXTURE_WRAP_S"
	wrapS: WrapMode = REPEAT;

	/// "description": "t wrapping mode."
	/// "gltf_detailedDescription": "t wrapping mode.  All valid values correspond to WebGL enums."
	/// "gltf_webgl": "`texParameterf()` with pname equal to TEXTURE_WRAP_T"
	wrapT: WrapMode = REPEAT;

	///-- glTFChildOfRootProperty
	/// The user-defined name of this object.
	/// gltf_detailedDescription: The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.
	name: string;

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
	///-- glTFChildOfRootProperty --/
}

///-- sampler.schema.json --/

///----------------------------------------------------------------------------

///-- texture.schema.json
/// Texture
/// "description": "A texture and its sampler."
/// "gltf_webgl": "`createTexture()`, `deleteTexture()`, `bindTexture()`, `texImage2D()`, and `texParameterf()`"
table Texture {
	/// "description": "The index of the sampler used by this texture. When undefined, a sampler with repeat wrapping and auto filtering should be used."
	sampler: int = -1; //glTFid

	/// "description": "The index of the image used by this texture."
	source: int = -1; //glTFid

	///-- glTFChildOfRootProperty
	/// The user-defined name of this object.
	/// gltf_detailedDescription: The user-defined name of this object.  This is not necessarily unique, e.g., an acc)") +
std::string(R"(essor and a buffer could have the same name, or two accessors could even have the same name.
	name: string;

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
	///-- glTFChildOfRootProperty --/
}

///-- texture.schema.json --/

///----------------------------------------------------------------------------

///-- skin.schema.json
/// Skin
/// "description": "Joints and matrices defining a skin."
table Skin {
	/// "description": "The index of the accessor containing the floating-point 4x4 inverse-bind matrices.  The default is that each matrix is a 4x4 identity matrix, which implies that inverse-bind matrices were pre-applied."
	inverseBindMatrices: int = -1; //glTFid

	/// "description": "The index of the node used as a skeleton root. When undefined, joints transforms resolve to scene root."
	skeleton: int = -1; //glTFid

	/// "description": "Indices of skeleton nodes, used as joints in this skin."
	/// "gltf_detailedDescription": "Indices of skeleton nodes, used as joints in this skin.  The array length must be the same as the `count` property of the `inverseBindMatrices` accessor (when defined)."
	joints: [int](required); //glTFid

	///-- glTFChildOfRootProperty
	/// The user-defined name of this object.
	/// gltf_detailedDescription: The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.
	name: string;

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific data.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/
	///-- glTFChildOfRootProperty --/
}    
///-- skin.schema.json --/

///----------------------------------------------------------------------------

///-- glTF.schema.json
/// The root object for a glTF asset.
table Root {
	/// Names of glTF exte)") +
std::string(R"(nsions used somewhere in this asset.
	extensionsUsed: [string];
   
	/// Names of glTF extensions required to properly load this asset.
	extensionsRequired: [string];

	/// An array of accessors.
	/// gltf_detailedDescription: An array of accessors.  An accessor is a typed view into a bufferView.
	accessors: [Accessor];

	/// An array of keyframe animations.
	animations: [Animation];

	/// Metadata about the glTF asset.
	asset: Asset(required);

	/// An array of buffers.
	/// gltf_detailedDescription: An array of buffers.  A buffer points to binary geometry, animation, or skins.
	buffers: [Buffer];

	/// An array of bufferViews.
	/// gltf_detailedDescription: An array of bufferViews.  A bufferView is a view into a buffer generally representing a subset of the buffer.
	bufferViews: [BufferView];

	/// An array of cameras.
	/// gltf_detailedDescription: An array of cameras.  A camera defines a projection matrix.
	cameras: [Camera];

	/// An array of images.
	/// gltf_detailedDescription: An array of images.  An image defines data used to create a texture.
	images: [Image];

	/// An array of materials.
	/// gltf_detailedDescription: An array of materials.  A material defines the appearance of a primitive.
	materials: [Material];

	/// An array of meshes.
	/// gltf_detailedDescription: An array of meshes.  A mesh is a set of primitives to be rendered.
	meshes: [Mesh];
	
	/// An array of nodes.
	nodes: [Node];
	
	/// An array of samplers.
	/// gltf_detailedDescription: An array of samplers.  A sampler contains properties for texture filtering and wrapping modes.
	samplers: [Sampler];

	/// The index of the default scene.
	scene: int = -1; //glTFid

	/// An array of scenes.
	scenes: [Scene];

	/// An array of skins.
	/// gltf_detailedDescription: An array of skins.  A skin is defined by joints and matrices.
	skins: [Skin];

	/// An array of textures.
	textures: [Texture];

	///-- glTFProperty
	/// Dictionary object with extension-specific objects.
	extensions: [ubyte](flexbuffer);

	/// Application-specific dat)") +
std::string(R"(a.
	extras: [ubyte](flexbuffer);
	///-- glTFProperty --/

}
///-- glTF.schema.json --/

root_type Root;

///----------------------------------------------------------------------------

///-- glTF-binary
/// enums for glTF-binary/GLB files
enum GLBConstant: uint {
	/// version indicates the version of the Binary glTF container format. This specification defines version 2.
	version = 2,

	/// chunkType equals 0x004E4942	, ASCII string 'BIN'	
	binary = 0x004E4942,

	/// magic equals 0x46546C67. It is ASCII string 'glTF', and can be used to identify data as Binary glTF.
	magic = 0x46546C67,

	/// chunkType equals 0x4E4F534A, ASCII string 'JSON'
	json = 0x4E4F534A,
}
///-- glTF-binary --/


///----------------------------------------------------------------------------
)") +
"";
