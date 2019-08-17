#pragma once

#include <stdexcept>
#include <string>

namespace sb_com1
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

	template <typename C>
	struct Arg
	{
		enum Kind
		{
			None, Integer, UnsignedInteger, Long, UnsignedLong, LongLong, UnsignedLongLong, Double, LongDouble, Float, Char, Cstr, Pointer
		};
		const Kind kind;

		Arg(int v) : i{ v }, kind{ Integer }
		{
		}
		Arg(unsigned int v) : ui{ v }, kind{ UnsignedInteger }
		{
		}
		Arg(long v) : l{ v }, kind{ Long }
		{
		}
		Arg(unsigned long v) : ul{ v }, kind{ UnsignedLong }
		{
		}
		Arg(long long v) : ll{ v }, kind{ LongLong }
		{
		}
		Arg(unsigned long long v) : ull{ v }, kind{ UnsignedLongLong }
		{
		}
		Arg(double v) : vd{ v }, kind{ Double }
		{
		}
		Arg(long double v) : vld{ v }, kind{ LongDouble }
		{
		}
		Arg(float v) : vf{ v }, kind{ Float }
		{
		}
		Arg(C v) : vc{ v }, kind{ Char }
		{
		}
		Arg(const C* v) : cstr{ v }, kind{ Cstr }
		{
		}
		Arg(void* v) : ptr{ v }, kind{ Pointer }
		{
		}

		int getInteger() const
		{
			switch (kind)
			{
			case Integer:
				return i;

			case UnsignedInteger:
				return static_cast<int>(ui);

			case Long:
				return static_cast<int>(l);

			case UnsignedLong:
				return static_cast<int>(ul);

			case LongLong:
				return static_cast<int>(ll);

			case UnsignedLongLong:
				return static_cast<int>(ull);

			default:
				throw format_error("Not an integer: " + std::to_string(kind));
			}
		}

		template <typename S>
		void put(S& out) const
		{
			switch (kind)
			{
			case Integer:
				out << i;
				break;

			case UnsignedInteger:
				out << ui;
				break;

			case Long:
				out << l;
				break;

			case UnsignedLong:
				out << ul;
				break;

			case LongLong:
				out << ll;
				break;

			case UnsignedLongLong:
				out << ull;
				break;

			case Double:
				out << vd;
				break;

			case LongDouble:
				out << vld;
				break;

			case Float:
				out << vf;
				break;

			case Char:
				out << vc;
				break;

			case Cstr:
				out << cstr;
				break;

			case Pointer:
				out << ptr;
				break;

			default:
				throw format_error("Unsupported value!");
			}
		}

		template <typename S>
		void putUnsigned(S& out) const
		{
			switch (kind)
			{
			case Integer:
				out << static_cast<unsigned>(i);
				break;

			case UnsignedInteger:
				out << ui;
				break;

			case Long:
				out << static_cast<unsigned long>(l);
				break;

			case UnsignedLong:
				out << ul;
				break;

			case LongLong:
				out << static_cast<unsigned long long>(ll);
				break;

			case UnsignedLongLong:
				out << ull;
				break;

			case Double:
				out << static_cast<uintmax_t>(vd);
				break;

			case LongDouble:
				out << static_cast<uintmax_t>(vld);
				break;

			case Float:
				out << static_cast<uintmax_t>(vf);
				break;

			case Char:
				out << static_cast<unsigned>(vc);
				break;

			case Pointer:
				out << ptr;
				break;

			default:
				throw format_error("Not a number!");
			}
		}
	private:
		union
		{
			int i;
			unsigned ui;
			long l;
			unsigned long ul;
			long long ll;
			unsigned long long ull;
			float vf;
			double vd;
			long double vld;
			C vc;
			const C* cstr;
			void* ptr;
		};
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

		Arg<C> av[] = { args... };

		format(out, fmt, av);
	}

	enum Flags : int
	{
		None = 0, /*LeftJustify = 1, ForceSign = 2, Space = 4,*/ Hash = 8//, PadWithZeroes = 16
	};

	template <typename S, typename C = S::char_type, typename L = Literals<C>, size_t N>
	void format(S& out, const C* fmt, const Arg<C>(&av)[N])
	{
		if (!fmt)
		{
			return;
		}

		auto argument = [&](int index) -> const Arg<C> & {
			if (index >= N)
			{
				throw format_error("Index is out of range: " + std::to_string(index));
			}
			return av[index];
		};

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
					width = argument(avIdx++).getInteger();
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
						precision = argument(avIdx++).getInteger();
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
					const Arg<C>& a = argument(avIdx++);
					switch (ch)
					{
					case L::d:
					case L::i:
						a.put(out);
						break;

					case L::u:
						a.putUnsigned(out);
						break;

					case L::s:
						a.put(out);
						break;

					case L::A:
						out.setf(std::ios_base::uppercase);
					case L::a:
						out.setf(std::ios_base::fixed | std::ios_base::scientific, std::ios_base::floatfield);
						a.put(out);
						break;

					case L::o:
						out.setf(std::ios_base::oct, std::ios_base::basefield);
						a.putUnsigned(out);
						break;

					case L::X:
						out.setf(std::ios_base::uppercase);
					case L::x:
						out.setf(std::ios_base::hex, std::ios_base::basefield);
						if (flags & Hash)
						{
							out << "0x";
						}
						a.putUnsigned(out);
						break;

					case L::p:
						a.put(out);
						break;

					case L::F:
						out.setf(std::ios_base::uppercase);
					case L::f:
						out.setf(std::ios_base::fixed, std::ios_base::floatfield);
						a.put(out);
						break;

					case L::E:
						out.setf(std::ios_base::uppercase);
					case L::e:
						out.setf(std::ios_base::scientific, std::ios_base::floatfield);
						a.put(out);
						break;

					case L::c:
						a.put(out);
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