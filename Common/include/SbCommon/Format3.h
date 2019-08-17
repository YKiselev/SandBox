#pragma once

#include <stdexcept>
#include <string>
#include <type_traits>

namespace sb_com3
{
	class format_error : public std::runtime_error
	{
	public:
		using _MyBase = std::runtime_error;

		format_error(const char* msg) : _MyBase(msg)
		{
		}
		format_error(const std::string& msg) : _MyBase(msg)
		{
		}
	};

	template <typename... Tail>
	struct Arguments
	{
		template <typename S>
		void put(S& out, int index) const
		{
			throw format_error("Insufficient number of arguments!");
		}

		template <typename S>
		void putUnsigned(S& out, int index) const
		{
			throw format_error("Insufficient number of arguments!");
		}

		int getInteger(int index) const
		{
			throw format_error("Insufficient number of arguments!");
		}
	};

	template <typename T, typename... Tail>
	struct Arguments<T, Tail...> : private Arguments<Tail...>
	{
		using Base = Arguments<Tail...>;

		Arguments(T v, Tail...tail) : value{ v }, Base{ tail... }
		{
		}

		template <typename S>
		void put(S& out, int index)
		{
			if (index == 0)
			{
				out << value;
			}
			else
			{
				Base::put(out, index - 1);
			}
		}

		template <typename S>
		void putUnsigned(S& out, int index)
		{
			if (index == 0)
			{
				putAsUnsigned(out, value);
			}
			else
			{
				Base::putUnsigned(out, index - 1);
			}
		}

		int getInteger(int index) const
		{
			if (index == 0)
			{
				return asInteger(value);
			}
			else
			{
				return Base::getInteger(index - 1);
			}
		}

	private:
		const T value;

		template <typename V, typename std::enable_if_t<!std::is_integral_v<V>, int> = 0>
		static int asInteger(V value)
		{
			throw format_error("Not integral type!");
		}

		template <typename V, typename std::enable_if_t<std::is_integral_v<V>, int> = 0>
		static int asInteger(V value)
		{
			return static_cast<int>(value);
		}

		template <typename S, typename V, typename std::enable_if_t<!std::is_integral_v<V>, int> = 0>
		static void putAsUnsigned(S & out, V value)
		{
			throw format_error("Not integral type!");
		}

		template <typename S, typename V, typename std::enable_if_t<std::is_integral_v<V>, int> = 0>
		static void putAsUnsigned(S & out, V value)
		{
			out << static_cast<typename std::make_unsigned<V>::type>(value);
		}
	};

	template <typename C>
	struct Literals
	{
		const static C percent = static_cast<C>('%');
		const static C minus = static_cast<C>('-');
		const static C plus = static_cast<C>('+');
		const static C space = static_cast<C>(' ');
		const static C hash = static_cast<C>('#');
		const static C zero = static_cast<C>('0');
		const static C nine = static_cast<C>('9');
		const static C dot = static_cast<C>('.');
		const static C a = static_cast<C>('a');
		const static C A = static_cast<C>('A');
		const static C c = static_cast<C>('c');
		const static C d = static_cast<C>('d');
		const static C e = static_cast<C>('e');
		const static C E = static_cast<C>('E');
		const static C f = static_cast<C>('f');
		const static C F = static_cast<C>('F');
		const static C i = static_cast<C>('i');
		const static C h = static_cast<C>('h');
		const static C l = static_cast<C>('l');
		const static C j = static_cast<C>('j');
		const static C z = static_cast<C>('z');
		const static C s = static_cast<C>('s');
		const static C t = static_cast<C>('t');
		const static C p = static_cast<C>('p');
		const static C L = static_cast<C>('L');
		const static C u = static_cast<C>('u');
		const static C o = static_cast<C>('o');
		const static C x = static_cast<C>('x');
		const static C X = static_cast<C>('X');
		const static C star = static_cast<C>('*');
	};

	template <typename S, typename C = S::char_type>
	void format(S & out, const C * fmt)
	{
		if (fmt)
		{
			out << fmt;
		}
	}

	template <typename S, typename C = S::char_type, typename L = Literals<C>, typename... Args>
	void format(S& out, const C* fmt, Args...args)
	{
		if (!fmt)
		{
			return;
		}

		_format(out, fmt, Arguments<Args...>(args...));
	}

	enum Flags : int
	{
		None = 0, /*LeftJustify = 1, ForceSign = 2, Space = 4,*/ Hash = 8//, PadWithZeroes = 16
	};

	template <typename S, typename... Args, typename C = S::char_type, typename L = Literals<C>>
	void _format(S & out, const C * fmt, Arguments<Args...> & av)
	{
		if (!fmt)
		{
			return;
		}

		int avIdx = 0;
		while (*fmt)
		{
			// We need to search passed format string for 'format specifier' of the form:
			// %[flags][width][.precision][length]specifier 
			// note that two consequtive %%'s are a prefixed single char '%' that should be put to output.
			int flags = None;
			if (*fmt == L::percent && *++fmt != L::percent)
			{
				C padding = L::space;

				// Reset stream flags
				out.flags(std::ios_base::dec | std::ios_base::internal | std::ios_base::fixed);

				// Read flags
				while (*fmt)
				{
					const C ch = *fmt;
					if (ch == L::minus)
					{
						out.setf(std::ios_base::left, std::ios_base::adjustfield);
					}
					else if (ch == L::plus)
					{
						out.setf(std::ios_base::showpos);
					}
					else if (ch == L::space)
					{
						//flags |= Space; // not supported?
					}
					else if (ch == L::hash)
					{
						flags |= Hash;
					}
					else if (ch == L::zero)
					{
						padding = L::zero;
					}
					else
					{
						break; // no more flags
					}
					fmt++;
				}

				// Read width
				int width = 0;
				if (*fmt == L::star)
				{
					width = av.getInteger(avIdx++);
					fmt++;
				}
				else
				{
					if (width == 0 && *fmt == L::zero)
					{
						throw format_error("Wrong width!");
					}
					while (*fmt)
					{
						const C ch = *fmt;
						if (ch < L::zero || ch > L::nine)
						{
							break;
						}
						width = 10 * width + static_cast<int>(ch - L::zero);
						fmt++;
					}
				}

				// Read precision
				int precision = 0;
				if (*fmt == L::dot)
				{
					fmt++;
					if (*fmt == L::star)
					{
						precision = av.getInteger(avIdx++);
						fmt++;
					}
					else
					{
						while (*fmt)
						{
							const C ch = *fmt;
							if (precision == 0 && ch == L::zero)
							{
								throw format_error("Wrong precision!");
							}
							if (ch < L::zero || ch > L::nine)
							{
								break;
							}
							precision = 10 * precision + static_cast<int>(ch - L::zero);
							fmt++;
						}
					}
				}

				// Read length
				C ch = *fmt;
				if (ch == L::h)
				{
					if (*++fmt == L::h)
					{
						// hh
						fmt++;
					}
					else
					{
						// h
					}
				}
				else if (ch == L::l)
				{
					if (*++fmt == L::l)
					{
						// ll
						fmt++;
					}
					else
					{
						// l
					}
				}
				else if (ch == L::j)
				{
					// j
					fmt++;
				}
				else if (ch == L::z)
				{
					// z
					fmt++;
				}
				else if (ch == L::t)
				{
					// t
					fmt++;
				}
				else if (ch == L::L)
				{
					// L
					fmt++;
				}

				// Read specifier
				ch = *fmt;
				if (ch)
				{
					out.width(width);
					out.precision(precision > 0 ? precision : 6);
					out.fill(padding);

					// Format argument(s) accordingly and write to output
					switch (ch)
					{
					case L::d:
					case L::i:
						av.put(out, avIdx++);
						break;

					case L::u:
						av.putUnsigned(out, avIdx++);
						break;

					case L::s:
						av.put(out, avIdx++);
						break;

					case L::A:
						out.setf(std::ios_base::uppercase);
					case L::a:
						out.setf(std::ios_base::fixed | std::ios_base::scientific, std::ios_base::floatfield);
						av.put(out, avIdx++);
						break;

					case L::o:
						out.setf(std::ios_base::oct, std::ios_base::basefield);
						av.putUnsigned(out, avIdx++);
						break;

					case L::X:
						out.setf(std::ios_base::uppercase);
					case L::x:
						out.setf(std::ios_base::hex, std::ios_base::basefield);
						if (flags & Hash)
						{
							out << "0x";
						}
						av.putUnsigned(out, avIdx++);
						break;

					case L::p:
						av.put(out, avIdx++);
						break;

					case L::F:
						out.setf(std::ios_base::uppercase);
					case L::f:
						out.setf(std::ios_base::fixed, std::ios_base::floatfield);
						av.put(out, avIdx++);
						break;

					case L::E:
						out.setf(std::ios_base::uppercase);
					case L::e:
						out.setf(std::ios_base::scientific, std::ios_base::floatfield);
						av.put(out, avIdx++);
						break;

					case L::c:
						av.put(out, avIdx++);
						break;

					default:
						throw format_error("Unknown specifier: " + std::to_string(ch));
					}
				}
				else
				{
					break; // \0 encountered
				}
				fmt++;
			}
			else
			{
				out.put(*fmt++);
			}
		}
	}
}