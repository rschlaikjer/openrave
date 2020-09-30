#ifndef OPENRAVE_OSGLODLABEL_H
#define OPENRAVE_OSGLODLABEL_H

#include "qtosg.h"

namespace qtosgrave {
	/// \brief OSG text label that scales by camera distance and also disappears if far away enough
	class OSGLODLabel : public osg::LOD
	{
	public:
	    OSGLODLabel(const std::string& label, osg::ref_ptr<osgText::Font> font=0);
	    ~OSGLODLabel();
	    void traverse(osg::NodeVisitor& nv);
        static void SetFont(osgText::Font* font);
    private:
        /// \brief fallback font for LOD label if set
        static osg::ref_ptr<osgText::Font> OSG_FONT;
	};
}

#endif
