#pragma once

namespace IMAGE {
	enum class AlphaBehaviorType {
		ONE_MINUS_ALPHA = 0, // default
		ONE,
	};
	enum class SamplingModeType {
		SAMPLING_CENTER = 0, // default
		SAMPLING_2x2, // TODO
		SAMPLING_3x3, // TODO
		SAMPLING_EXACTLY, // TODO : Is it possible when we use circle?
	};
} /* namespace IMAGE */