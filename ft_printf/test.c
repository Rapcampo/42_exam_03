/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 00:42:35 by rapcampo          #+#    #+#             */
/*   Updated: 2024/09/27 01:05:51 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

int ft_print_nbr(long long nbr, char *base)
{
	int printed = 0;
	long long base_len = 0;
	if (base[0] == '-' && nbr < 0)
	{
		nbr = -nbr;
		printed += write(1, "-", 1);
		base++;
	}
	else if (base[0] == '-')
		base++;
	while (base[base_len])
		base_len++;
	if (nbr >= base_len)
		printed += ft_print_nbr(nbr / base_len, base);
	printed += write(1, &base[nbr % base_len], 1);
	return (printed);
}

int	ft_string(char *str)
{
	int printed = 0;
	if (!str)
		return (write(1, "(null)", 6), printed += 6);
	while (*str)
		printed += write(1, str++, 1);
	return (printed);
}

int	check_print(char function, va_list ap)
{
	int printed = 0;
	if (function == 's')
		printed += ft_string(va_arg(ap, char *));
	else if (function == 'd')
		printed += ft_print_nbr(va_arg(ap, int), "-0123456789");
	else if (function == 'x')
		printed += ft_print_nbr(va_arg(ap, unsigned int), "0123456789abcdef");
	else
		printed += write(1, &function, 1);
	return (printed);
}

int	ft_printf(char *format, ...)
{
	va_list ap;
	int	printed = 0;
	va_start(ap, format);
	while(*format)
	{
		if (*format == '%')
			printed += check_print(*(++format), ap);
		else
			printed += write(1, format, 1);
		++format;
	}
	return (va_end(ap), printed);
}

int main(int argc, char **argv)
{
	(void)argc;
	ft_printf("%s\n", "toto");
	ft_printf("magic %s is %d\n", "number", 42);
	ft_printf("hexadecimal for %d is %x\n", 42, 42);
	if (argv[0])
		ft_printf("this is a test");
	return (0);
}
