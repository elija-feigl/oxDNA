/*
 * python_glm.h
 *
 *  Created on: Mar 28, 2019
 *      Author: lorenzo
 *
 * See https://stackoverflow.com/questions/42645228/cast-numpy-array-to-from-custom-c-matrix-class-using-pybind11
 */

#ifndef PYTHON_PYTHON_GLM_H_
#define PYTHON_PYTHON_GLM_H_

#include <pybind11/numpy.h>
#include <Utilities/LR_vector.h>
#include <Utilities/LR_matrix.h>

namespace pybind11 {
namespace detail {

using std::cout;
using std::endl;

template<>
struct type_caster<LR_vector> {
public:

PYBIND11_TYPE_CASTER(LR_vector, _("LR_vector"));

	// Python -> c++ conversion
	bool load(handle src, bool convert) {
		if(!convert and !array_t<number>::check_(src)) {
			return false;
		}

		auto buf = array_t<number, array::c_style | array::forcecast>::ensure(src);
		if(!buf) {
			return false;
		}

		if(buf.ndim() != 1) {
			return false;
		}

		if(buf.shape(0) != 3) {
			return false;
		}

		value = LR_vector(buf.data()[0], buf.data()[1], buf.data()[2]);

		return true;
	}

	// c++ -> Python conversion
	static handle cast(const LR_vector &src, return_value_policy /* policy */, handle /* parent */) {
		number data[3] = {src.x, src.y, src.z};
		return array(3, data).release();
	}
};

template<>
struct type_caster<LR_matrix> {
public:

PYBIND11_TYPE_CASTER(LR_matrix, _("LR_matrix"));

	// Python -> c++ conversion
	bool load(handle src, bool convert) {
		if(!convert and !array_t<number>::check_(src)) {
			return false;
		}

		auto buf = array_t<number, array::c_style | array::forcecast>::ensure(src);
		if(!buf) {
			return false;
		}

		if(buf.ndim() != 1) {
			return false;
		}

		if(buf.shape(0) != 9) {
			return false;
		}

		value = LR_matrix(
				buf.data()[0], buf.data()[1], buf.data()[2],
				buf.data()[3], buf.data()[4], buf.data()[5],
				buf.data()[6], buf.data()[7], buf.data()[8]
		);

		return true;
	}

	// c++ -> Python conversion
	static handle cast(const LR_matrix &src, return_value_policy /* policy */, handle /* parent */) {
		number data[9] = {
			src.v1.x, src.v1.y, src.v1.z,
			src.v2.x, src.v2.y, src.v2.z,
			src.v3.x, src.v3.y, src.v3.z};
		return array(9, data).release();
	}
};

}
/* namespace detail */
} /* namespace pybind11 */

#endif /* PYTHON_PYTHON_GLM_H_ */
