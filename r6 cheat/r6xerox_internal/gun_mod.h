#pragma once
#include <cstdint>
#include <atomic>

//--- gun_mod namespace contains all gun mod features
namespace gun_mod
{
	inline std::atomic<bool> no_recoil_enabled{}, damage_mod_enabled;
	inline std::atomic<unsigned> lbullet_amount{};

	//--- no recoil for all weapons
	class no_recoil
	{
	public:
		no_recoil() {};
		void input_interface(bool toggle);

	private:
		void enable();
		void disable();

		const uint8_t no_recoil_disable[4] =
		{
			0x92,
			0x0A,
			0x06,
			0x3F
		};

		const uint8_t no_recoil_enable[4] =
		{
			0x0,
			0x0,
			0x0,
			0x0
		};

	};


	class damage_mod
	{

	public:
		damage_mod() {};
		void input_interface(bool toggle, int bullet_amount);

	private:
		void enable(int bullet_amount);
		void disable();

	};
}