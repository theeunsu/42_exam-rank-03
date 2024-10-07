#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	print_c(char c, int i)
{
	write(1, &c, 1);
	i++;
	return (i);
}

int	print_s(char *s, int i)
{
	if (!s)
		i = print_s("(null)", i);
	else
	{
		while (*s)
		{
			i = print_c(*s, i);
			s++;
		}
	}
	return (i);
}

int	print_d(int d, int i)
{
	if (d == -2147483648)
	{
		write(1, "-2147483648", 11);
		i = i + 11;
	}
	else if (d < 0)
	{
		i = print_c('-', i);
		i = print_d(-d, i);
	}
	else if (d >= 0 && d < 10)
		i = print_c(d + '0', i);
	else
	{
		i = print_d(d / 10, i);
		i = print_c(d % 10 + '0', i);
	}
	return (i);
}

int	print_x(unsigned int x, int i)
{
	if (x == 0)
		i = print_c('0', i);
	else if (x >= 16)
	{
		i = print_x(x / 16, i);
		i = print_x(x % 16, i);
	}
	else
	{
		if (x < 10)
			i = print_c(x + '0', i);
		else
			i = print_c(x + 87, i);
	}
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		j;

	i = 0;
	j = 0;
	va_start(ap, format);
	while (format[j])
	{
		if (format[j] == '%')
		{
			j++;
			if (format[j] == 's')
				i = print_s(va_arg(ap, char *), i);
			if (format[j] == 'd')
				i = print_d(va_arg(ap, int), i);
			if (format[j] == 'x')
				i = print_x(va_arg(ap, unsigned int), i);
		}
		else
			i = print_c(format[j], i);
		j++;
	}
	va_end(ap);
	return (i);
}

// #include <limits.h>

// int	main(void)
// {
// 	int	i;

// 	i = INT_MIN;
// 	ft_printf("MIN number: %d\n", i);
// 	printf("MIN number: %d\n", i);
// 	i = ft_printf("printf --> Hello 42! \n s: %s, d: %d, x: %x\n", "toto", 42,
// 			42);
// 	ft_printf("i: %d\n", i);
// 	i = printf("printf --> Hello 42! \n s: %s, d: %d, x: %x\n", "toto", 42, 42);
// 	printf("i: %d\n", i);
// 	ft_printf("%s\n", "toto");
// 	printf("%s\n", "toto");
// 	ft_printf("Magic %s is %d", "number", 42);
// 	printf("Magic %s is %d", "number", 42);
// 	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
// 	printf("Hexadecimal for %d is %x\n", 42, 42);
// }
