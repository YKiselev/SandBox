#pragma once

namespace sb_com
{
	template <typename R>
	class OnScopeExit
	{
	public:
		OnScopeExit(R& runnable) : runnable{ runnable }
		{
		}

		~OnScopeExit()
		{
			runnable();
		}

	private:
		const R& runnable;
	};
}
