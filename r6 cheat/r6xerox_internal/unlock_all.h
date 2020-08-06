#pragma once
#include <cstdint>
#include <atomic>

namespace unlock_all {

	inline std::atomic<bool> unlock_all_enabled = false;

	class unlock_all {
	
	public:
		unlock_all();
		void input_interface(bool toggle);

	private:
		void enable();
		void disable();

		const uint8_t unlock_all_enable_bytes[4] = {
			0xC6,
			0x47,
			0x38,
			0x00
		};

		const uint8_t unlock_all_disable_bytes[4] = {
			0xC6,
			0x47,
			0x38,
			0x01
		};

	};

}