//========================================================================
// Copyright (c) 2003-2011 Anael Seghezzi <www.maratis3d.com>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================


#ifndef __TEXTURES_ANIM_REF_H
#define __TEXTURES_ANIM_REF_H

namespace Neo
{
// Textures Anim ref
class NEO_ENGINE_EXPORT TexturesAnimRef : public DataRef
{
private:

	// data
	TexturesAnim * m_texturesAnim;

public:

	// constructor / destructor
	TexturesAnimRef(TexturesAnim * texturesAnim, const char * filename);
	~TexturesAnimRef(void);

	// clear / destroy
	void clear(void);
	void destroy(void);

	// get new
	static TexturesAnimRef * getNew(TexturesAnim * texturesAnim, const char * filename);

public:

	// update
	void update(void);

	// type
	int getType(void){ return M_REF_TEXTURES_ANIM; }

	// get data
	inline TexturesAnim * getTexturesAnim(void){ return m_texturesAnim; }
};
}
#endif
