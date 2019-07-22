#pragma once

namespace pg::commons
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
