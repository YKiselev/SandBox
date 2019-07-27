#pragma once

namespace sb::common
{
	class OnScopeExit
	{
	public:
		using Runnable = void(*)();

		OnScopeExit(Runnable runnable) : runnable{ runnable }
		{
		}

		~OnScopeExit()
		{
			runnable();
		}

	private:
		const Runnable runnable;
	};
}
