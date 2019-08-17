#pragma once

#include <stdexcept>
#include <functional>
#include <string>


namespace sb_com
{
	class format_error2 : public std::runtime_error
	{
	public:
		format_error2(const char* msg) : std::runtime_error(msg)
		{
		}
		format_error2(const std::string& msg) : std::runtime_error(msg)
		{
		}
	};

	template <typename C>
	struct Literals
	{
		const static C percent = static_cast<C>('%');
		const static C ocbrace = static_cast<C>('{');
		const static C ccbrace = static_cast<C>('}');
		const static C squote = static_cast<C>('\'');
		const static C zero = static_cast<C>('0');
		const static C nine = static_cast<C>('9');
	};

	template <typename S>
	struct Modifiers
	{
		template <typename Integral>
		static std::function<void(S&)> oct(Integral value)
		{
			return [=](S& out) { out << std::oct << value; };
		}

		static std::function<void(S&)> w(int width, int precision, std::function<void(S&)> delegate)
		{
			return [=](S& out) {
				out.width(width);
				out.precision(precision > 0 ? precision : 6);
				delegate(out);
			};
		}

		template <typename V>
		static std::function<void(S&)> w(int width, int precision, V value)
		{
			return w(width, precision, std::function<void(S&)>([=](S& out) { out << value; }));
		}

		template <typename V>
		static std::function<void(S&)> hex(V value, bool upperCase, bool prefix)
		{
			return [=](S& out) {
				out.setf(std::ios_base::hex, std::ios_base::basefield);
				if (upperCase)
				{
					out.setf(std::ios_base::uppercase);
				}
				if (prefix)
				{
					out << "0x";
				}
				out << value;
			};
		}

		template <typename V>
		static std::function<void(S&)> fhex(V value, bool upperCase)
		{
			return [=](S& out) {
				out.setf(std::ios_base::fixed | std::ios_base::scientific, std::ios_base::floatfield);
				if (upperCase)
				{
					out.setf(std::ios_base::uppercase);
				}
				out << value;
			};
		}

		template <typename V>
		static std::function<void(S&)> fixed(V value, bool upperCase)
		{
			return [=](S& out) {
				out.setf(std::ios_base::fixed, std::ios_base::floatfield);
				if (upperCase)
				{
					out.setf(std::ios_base::uppercase);
				}
				out << value;
			};
		}

		template <typename V>
		static std::function<void(S&)> f(V value)
		{
			return fixed(value, false);
		}

		template <typename V>
		static std::function<void(S&)> F(V value)
		{
			return fixed(value, true);
		}

		template <typename V>
		static std::function<void(S&)> x(V value)
		{
			return hex(value, false, false);
		}

		template <typename V>
		static std::function<void(S&)> zx(V value)
		{
			return hex(value, false, true);
		}

		template <typename V>
		static std::function<void(S&)> X(V value)
		{
			return hex(value, true, false);
		}

		template <typename V>
		static std::function<void(S&)> ZX(V value)
		{
			return hex(value, true, true);
		}

		template <typename V>
		static std::function<void(S&)> a(V value)
		{
			return fhex(value, false);
		}

		template <typename V>
		static std::function<void(S&)> A(V value)
		{
			return fhex(value, true);
		}
	};

	template <typename S>
	struct Arg
	{
		using Consumer = std::function<void(S&)>;

		Arg(const Consumer& c) : consumer{ c }
		{
		}
		Arg(Consumer&& c) : consumer{ std::move(c) }
		{
		}
		Arg(Arg&& a) : consumer{ std::move(a.consumer) }
		{
			a.consumer = nullptr;
		}
		template <typename V>
		Arg(V x) : consumer{ [=](S& out) { out << x; } }
		{
		}

		void print(S& out) const
		{
			consumer(out);
		}

	private:
		Consumer consumer;
	};

	template <typename S>
	using Getter = std::function<const Arg<S>& (int)>;

	template <typename S, typename C = S::char_type>
	void format2(S & out, const C * fmt)
	{
		if (fmt)
		{
			format3(out, fmt, static_cast<const Arg<S>*>(nullptr), 0);
		}
	}

	template <typename S, typename C = S::char_type, typename L = Literals<C>, typename... Args>
	void format2(S& out, const C* fmt, Args...args)
	{
		if (!fmt)
		{
			return;
		}

		const Arg<S> av[] = { args... };

		format3(out, fmt, av, sizeof...(Args));
	}

	template <typename S>
	inline const Arg<S>& get(const Arg<S>* av, size_t length, int index) {
		if (index >= length)
		{
			throw format_error2("Index is out of range: " + std::to_string(index));
		}
		return av[index];
	};

	template <typename S, typename C = S::char_type, typename L = Literals<C>>
	void format3(S & out, const C * fmt, const Arg<S> * av, size_t length)
	{
		if (!fmt)
		{
			return;
		}

		int argumentNumber = 0, indexToUse = 0;
		bool quoted = false;
		while (*fmt)
		{
			// We need to search passed format string for placeholders of the form {[index]}
			// any characters inside single quotes '{abc}' are treated as text (not a placeholder). 
			// Any two consecutive single quotes is an escaped single quote.
			if (*fmt == L::squote && *++fmt != L::squote)
			{
				quoted = !quoted;
			}

			if (quoted)
			{
				out.put(*fmt++);
				continue;
			}

			if (*fmt == L::ocbrace)
			{
				fmt++;

				// Reset stream flags
				out.flags(std::ios_base::dec | std::ios_base::internal | std::ios_base::fixed);

				// Read index
				int index = 0, digits = 0;
				while (*fmt)
				{
					const C ch = *fmt;
					if (ch < L::zero || ch > L::nine)
					{
						break;
					}
					index = 10 * index + static_cast<int>(ch - L::zero);
					digits++;
					fmt++;
				}
				if (digits == 0)
				{
					indexToUse = argumentNumber;
				}
				else
				{
					indexToUse = index;
				}

				// Ok, now we should be at closing '}'
				if (*fmt != L::ccbrace)
				{
					throw format_error2("Unclosed placeholder!");
				}

				// Print argument
				get(av, length, indexToUse).print(out);

				argumentNumber++;
				fmt++;
			}
			else if (!*fmt)
			{
				break; // \0 reached
			}
			else
			{
				out.put(*fmt++);
			}
		}
	}
}