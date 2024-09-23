/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:01:52 by rapcampo          #+#    #+#             */
/*   Updated: 2024/09/23 15:17:33 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

int	ft_print_nbr(long long n, const char *base)
{
	int printed = 0;
	long long base_len = 0;
	if (base[0] == '-' && n < 0)
	{
		n = -n;
		printed += write(1, "-", 1);
		base++;
	}
	else if (base[0] == '-')
		base++;
	while (base[base_len])
		base_len++;
	if (n >= base_len)
		printed += ft_print_nbr(n / base_len, base);
	printed +=  write(1, &base[n % base_len], 1);
	return (printed);
}

int	ft_string(char *str)
{
	int printed = 0;
	if (!str)
		return (write(1, "(null)", 6), printed += 6);
	while (*str)
		printed += write(1, &*str++, 1);
	return (printed);
}

int check_print(char function, va_list ap)
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

int	ft_printf(char *arg, ...)
{
	va_list ap;
	int	printed = 0;
	int err = 0;
	va_start(ap, arg);
	while (*arg)
	{
		if (*arg == '%')
			printed += check_print(*(++arg), ap);
		else
			printed += write(1, arg, 1);
		++arg;
	}
	return (va_end(ap), printed);
}
/*
int main(int argc, char **argv)
{
	(void)argc;
	ft_printf("%s\n", "toto");
	ft_printf("magic %s is %d\n", "number", 42);
	ft_printf("hexadecimal for %d is %x\n", 42, 42);
	if (argv[1])
		ft_printf("%s", argv[1]);
	return (0);
}*/
