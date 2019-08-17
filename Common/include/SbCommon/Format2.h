#pragma once

#include <stdexcept>
#include <functional>
#include <string>


namespace sb_com
{
	class format_error : public std::runtime_error
	{
	public:
		format_error(const char* msg) : std::runtime_error(msg)
		{
		}
		format_error(const std::string& msg) : std::runtime_error(msg)
		{
		}
	};

	namespace detail
	{
		template <typename C>
		struct Literals
		{
			const static C ocbrace = static_cast<C>('{');
			const static C ccbrace = static_cast<C>('}');
			const static C squote = static_cast<C>('\'');
			const static C colon = static_cast<C>(':');
			const static C minus = static_cast<C>('-');
			const static C plus = static_cast<C>('+');
			const static C space = static_cast<C>(' ');
			const static C hash = static_cast<C>('#');
			const static C zero = static_cast<C>('0');
			const static C nine = static_cast<C>('9');
			const static C dot = static_cast<C>('.');
			const static C a = static_cast<C>('a');
			const static C A = static_cast<C>('A');
			const static C e = static_cast<C>('e');
			const static C E = static_cast<C>('E');
			const static C f = static_cast<C>('f');
			const static C F = static_cast<C>('F');
			const static C o = static_cast<C>('o');
			const static C x = static_cast<C>('x');
			const static C X = static_cast<C>('X');
			const static C star = static_cast<C>('*');
		};

		template <typename... Tail>
		struct Arguments
		{
			template <typename Op>
			auto map(int index, Op op) const
			{
				throw std::out_of_range("No args!");
				return op(0);
			}
		};

		template <typename T, typename... Tail>
		struct Arguments<T, Tail...> : private Arguments<Tail...>
		{
			using Base = Arguments<Tail...>;

			Arguments(T v, Tail...tail) : value{ v }, Base{ tail... }
			{
			}

			template <typename Op>
			auto map(int index, Op op) const
			{
				if (index == 0)
				{
					return op(value);
				}
				return Base::map(index - 1, op);
			}

		private:
			const T value;
		};

		enum Flags : int
		{
			None = 0, /*LeftJustify = 1, ForceSign = 2, Space = 4,*/ Hash = 8//, PadWithZeroes = 16
		};

		template <typename V, typename std::enable_if_t<!std::is_integral_v<V>, int> = 0>
		int toInteger(V value)
		{
			throw format_error("Not integral type!");
		}

		template <typename V, typename std::enable_if_t<std::is_integral_v<V>, int> = 0>
		int toInteger(V value)
		{
			return static_cast<int>(value);
		}

	}

	template <typename S, typename C = S::char_type>
	void format(S & out, const C * fmt)
	{
		if (fmt)
		{
			format(out, fmt, new detail::Arguments<int>(0), 0);
		}
	}

	template <typename S, typename C = S::char_type, typename L = detail::Literals<C>, typename... Args>
	void format(S& out, const C* fmt, Args...args)
	{
		if (!fmt)
		{
			return;
		}

		const detail::Arguments<Args...> av(args...);

		format(out, fmt, av, sizeof...(Args));
	}

	template <typename S, typename... A, typename C = S::char_type, typename L = detail::Literals<C>>
	void format(S & out, const C * fmt, const detail::Arguments<A...> & av, size_t length)
	{
		if (!fmt)
		{
			return;
		}

		int argumentNumber = 0, indexToUse = 0;
		bool quoted = false;
		while (*fmt)
		{
			int flags = detail::None, width = 0, precision = 0;
			C padding = L::space;

			// We need to search passed format string for placeholders of the form 
			// {[index[:[flags][width][.precision][specifier]]]}
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

				if (*fmt == L::colon)
				{
					fmt++;

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
							flags |= detail::Hash;
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
					if (*fmt == L::star)
					{
						// todo ?????? width = av.map(avIdx++, detail::toInteger);
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
					if (*fmt == L::dot)
					{
						fmt++;
						if (*fmt == L::star)
						{
							// todo precision = av.map(avIdx++, detail::toInteger);
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

					// Format argument(s) accordingly and write to output
					switch (*fmt)
					{
					case L::A:
						out.setf(std::ios_base::uppercase);
					case L::a:
						out.setf(std::ios_base::fixed | std::ios_base::scientific, std::ios_base::floatfield);
						break;

					case L::o:
						out.setf(std::ios_base::oct, std::ios_base::basefield);
						break;

					case L::X:
						out.setf(std::ios_base::uppercase);
					case L::x:
						out.setf(std::ios_base::hex, std::ios_base::basefield);
						if (flags & detail::Hash)
						{
							out << "0x";
						}
						break;

					case L::F:
						out.setf(std::ios_base::uppercase);
					case L::f:
						out.setf(std::ios_base::fixed, std::ios_base::floatfield);
						break;

					case L::E:
						out.setf(std::ios_base::uppercase);
					case L::e:
						out.setf(std::ios_base::scientific, std::ios_base::floatfield);
						break;

					default:
						throw format_error("Unknown specifier: " + std::to_string(*fmt));
					}
					fmt++;
				}

				// Ok, now we should be at closing '}'
				if (*fmt != L::ccbrace)
				{
					throw format_error("Unclosed placeholder!");
				}

				// Print argument
				out.width(width);
				out.precision(precision > 0 ? precision : 6);
				out.fill(padding);

				av.map(indexToUse, [&](auto v) -> int { out << v; return 0;  });

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