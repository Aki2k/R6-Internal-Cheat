#pragma once
#include <atomic>

#include "rainbowsix.h"

namespace esp {

	inline std::atomic<bool> spotted_enabled{}, outline_enabled{};

	class spotted {

	public:

		spotted();
		inline void input_interface(bool toggle);
	private:
		inline void enable();
		inline void disable();

		const uint8_t spotted_enable_icon_bytes[7] = {
			0x80,
			0xB9,
			0x31,
			0x05,
			0x00,
			0x00,
			0x00
		};

		const uint8_t spotted_disable_icon_bytes[7] = {
			0x80,
			0xB9,
			0x31,
			0x05,
			0x00,
			0x00,
			0x00
		};

		const uint8_t spotted_enable_name_bytes[7] = {
			0x80,
			0xBB,
			0x31,
			0x05,
			0x00,
			0x00,
			0x01
		};

		const uint8_t spotted_disable_name_bytes[7] = {
			0x80,
			0xBB,
			0x31,
			0x05,
			0x00,
			0x00,
			0x00
		};

	};

}