#pragma once

namespace sb_com
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
		Runnable runnable;
	};

}
