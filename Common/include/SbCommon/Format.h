#pragma once

#include <iostream>
#include <string>

namespace sb_com
{
	struct Arg
	{
		enum Kind
		{
			Integer, Double, Char, Cstr
		};
		const Kind kind;
		union
		{
			int vi;
			double vd;
			char vc;
			const char* cstr;
		};
		Arg(int v) : vi{ v }, kind{ Integer }
		{
		}
		Arg(double v) : vd{ v }, kind{ Double }
		{
		}
		Arg(char v) : vc{ v }, kind{ Char }
		{
		}
		Arg(const char* v) : cstr{ v }, kind{ Cstr }
		{
		}
	};

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
		const static C t = static_cast<C>('t');
		const static C L = static_cast<C>('L');
		const static C star = static_cast<C>('*');
	};

	template <typename S, typename C = S::char_type>
	void format2(S & out, const C * fmt)
	{
		// todo
		int g2 = 0;
	}

	template <typename S, typename C = S::char_type, typename L = Literals<C>, typename... Args>
	void format2(S& out, const C* fmt, Args...args)
	{
		if (!fmt)
		{
			return;
		}

		enum Flags : char
		{
			None = 0, LeftJustify = 1, ForceSign = 2, Space = 4, Dash = 8, PadWithZeroes = 16
		};

		const size_t size = sizeof...(Args);
		Arg av[] = { args... };
		int avIdx = 0;
		while (*fmt)
		{
			// We need to search passed format string for 'format specifier' of the form:
			// %[flags][width][.precision][length]specifier 
			// note that two consequtive %%'s are a prefixed single char '%' that should be put to output.
			char flags = None;
			if (*fmt == L::percent && *++fmt != L::percent)
			{
				// Read flags
				while (*fmt)
				{
					const C ch = *fmt;
					if (ch == L::minus)
					{
						flags |= LeftJustify;
					}
					else if (ch == L::plus)
					{
						flags |= ForceSign;
					}
					else if (ch == L::space)
					{
						flags |= Space;
					}
					else if (ch == L::hash)
					{
						flags |= Dash;
					}
					else if (ch == L::zero)
					{
						flags |= PadWithZeroes;
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
					width = av[avIdx++].vi;
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
						precision = av[avIdx++].vi;
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
				if (ch)
				{
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
				}

				// Read specifier
				ch = *fmt++;
				if (ch)
				{
					if (width > 0)
					{
						out.width(width);
					}
					if (precision > 0)
					{
						out.precision(precision);
					}
					out.fill(flags & PadWithZeroes ? L::zero : L::space);

					switch (ch)
					{
					case L::d:
					case L::i:
						out << std::dec << av[avIdx++].vi;
						break;

					case L::F:
						out.setf(std::ios_base::uppercase);
					case L::f:
						out << std::fixed << av[avIdx++].vd;
						break;

					case L::E:
						out.setf(std::ios_base::uppercase);
					case L::e:
						out << std::scientific << av[avIdx++].vd;
						break;

					default:
						throw format_error("Unknown specifier: " + std::to_string(ch));
					}
				}

				// Format argument(s) accordingly and write to output
			}
			out.put(*fmt++);
		}
	}
}