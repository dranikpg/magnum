/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019,
                2020, 2021 Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include <Corrade/Containers/Array.h>
#include <Corrade/Containers/Pair.h>

#include "Magnum/Math/Matrix4.h"
#include "Magnum/SceneTools/OrderClusterParents.h"
#include "Magnum/Trade/SceneData.h"

#define DOXYGEN_ELLIPSIS(...) __VA_ARGS__

using namespace Magnum;

int main() {
{
/* [orderClusterParents-transformations] */
Trade::SceneData scene = DOXYGEN_ELLIPSIS(Trade::SceneData{{}, 0, nullptr, {}});

/* Put all transformations into an array indexed by object ID. Objects
   implicitly have an identity transformation, first element is reserved for
   the global transformation. */
Containers::Array<Matrix4> transformations{std::size_t(scene.mappingBound() + 1)};
for(const Containers::Pair<UnsignedInt, Matrix4>& transformation:
    scene.transformations3DAsArray())
{
    transformations[transformation.first() + 1] = transformation.second();
}

/* Go through ordered parents and compose absolute transformations for all
   nodes in the hierarchy, objects in the root use transformations[0]. The
   function ensures that the parent transformation is already calculated when
   referenced by child nodes. */
for(const Containers::Pair<UnsignedInt, Int>& parent:
    SceneTools::orderClusterParents(scene))
{
    transformations[parent.first() + 1] =
        transformations[parent.second() + 1]*
        transformations[parent.first() + 1];
}
/* [orderClusterParents-transformations] */
}
}
