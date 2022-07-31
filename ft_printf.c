#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

//// Ainda falta desenvolver um return value = ao numero de caracteres escritos na consola
//// Finalizar e melhorar o Pointer Printer
//// Fazer o makefile

//// ITO START

static void	*ft_itod(char *ret, int cnt, long int a, long int len)
{
	int	i;

	i = 0;
	ret[cnt + 1] = '\0';
	while (i < len)
	{
		ret[cnt] = (a % 10) + 48;
		a = a / 10;
		cnt--;
		i++;
	}
	return (ret);
}

int	norm_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

static long int	ft_getlen(int n)
{
	long int					len;

	len = 0;
	if (n < 0 && n != -2147483648)
		len = 1;
	if (n == 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = (n - (n % 10)) / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long int	cnt;
	long int	len;
	long int	a;
	char		*ret;

	a = (long int) n;
	len = ft_getlen(a);
	if (a == -2147483648)
		len++;
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	if (a >= 0)
		cnt = len - 1;
	else
	{
		a = a * -1;
		len = ft_getlen(a);
		cnt = len;
		ret[0] = '-';
	}
	return (ft_itod(ret, cnt, a, len));
}

char	*ft_uitoa(unsigned int n)
{
	long int	cnt;
	long int	len;
	long int	a;
	char		*ret;

	if (n < 0)
		n = n * -1;
	a = (long int) n;
	len = ft_getlen(a);
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	if (a >= 0)
		cnt = len - 1;
	return (ft_itod(ret, cnt, a, len));
}

char *reverse_printer(char * str)
{
	int len;
	int finalen;
	int i;
	char *swapper;

	i = 0;
	len = norm_strlen(str) - 1;
	finalen = len;
	swapper = malloc(len);
	while (i <= finalen)
	{
		swapper[i] = str[len];
		i++;
		len--;
	}
	return(swapper);
}

int	ft_gethexsize(long	int i)
{
	int	size;

	size = 0;
	while (i != 0)
	{
		size++;
		i = i / 16;
	}
	return (size);
}




char *ft_itobighex(unsigned int n)
{
	long int	len;
	char	*printer;
	int	i = 0;
	len = ft_gethexsize(n);
	printer = malloc(len + 1);

	while (n / 16 != 0)
	{
		if(n % 16 < 10)
			printer[i] = n % 16 + '0';
		else
			printer[i] = (n % 16) - 10 + 'A'; /// Fazer uma copia com 'A'
		n = n / 16;
		i++;
	}
	if(n % 16 < 10)					/// Mete o ultimo numero
			printer[i] = n % 16 + '0';
	else
			printer[i] = (n % 16) - 10 + 'A'; 
	i++;
	printer[i] = '\0';
	printer = reverse_printer(printer); /// STILL NOT WORKING UNNBUG
	return(printer);	
}

char	*ft_itohex(unsigned long int n)
{
	// Estava aqui - Já tens as intruções para continuares

	// Presisas de encontrar a lenght
	/// Ir Dividindo por 16 e passar valor dos restos
	//// Formatar valores > 9
	///// Passar valor para um char * no lenght invertido 


	//////// Passar os 10 para 16 até funcionar prov vais precisar de um malloc
	long int	len;
	char	*printer;
	int	i = 0;
	len = ft_gethexsize(n);
	printer = malloc(len + 1);

	while (n / 16 != 0)
	{
		if(n % 16 < 10)
			printer[i] = n % 16 + '0';
		else
			printer[i] = (n % 16) - 10 + 'a'; /// Fazer uma copia com 'A'
		n = n / 16;
		i++;
	}
	if(n % 16 < 10)					/// Mete o ultimo numero
			printer[i] = n % 16 + '0';
	else
			printer[i] = (n % 16) - 10 + 'a'; 
	i++;
	printer[i] = '\0';
	//
	printer = reverse_printer(printer); /// STILL NOT WORKING UNNBUG
	return(printer);
}

//// ITO END





/// UTILS

void	print_string(char *str)
{

	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	print_int(int i)
{
	char *printer = ft_itoa(i);
	print_string(printer);
	free(printer); ///malloc é feito no itoa
}

void	print_uint(unsigned int i)
{
	char *printer = ft_uitoa(i);
	print_string(printer);
	free(printer); ///malloc é feito no itoa
}

void	print_hex(int i, char x_size)
{
	char *printer;
	if(x_size == 'x')
		printer = ft_itohex(i);
	else if(x_size == 'X')
		printer = ft_itobighex(i); ///Este vai ser uma copia do outro
	// else if(x_size == 'p')
	// {
	// 	/// Arranjar forma de adicionar aqui o 0x no principio do printer
	// 	printer = ft_itohex(i);
	// }
	print_string(printer);
	free(printer);
}

char	*ft_addprefix(char *printer)
{
	int	len;
	int	i;
	char *swapper;

	len = norm_strlen(printer);
	swapper = malloc(len + 3);
	swapper[0] = '0';
	swapper[1] = 'x';
	i = 2;
	while (i <= len + 3)
	{
		swapper[i] = printer[i - 2];
		i++;
	}
	free(printer);
	return(swapper);
}

void	print_pointer(unsigned long n)
{
	char *printer;

	printer = ft_itohex(n);
	printer = ft_addprefix(printer);
	print_string(printer);
	free(printer);
}

void	print_char(int i)
{
	write(1, &i, 1);
}






//// MAIN FUNCTION

int	ft_printf(const char *var, ...)
{
	va_list args;
	int print_size = 0;
	int i = 0;
	va_start(args, var); // abre a lista de argumentos
	while (var[i] != '\0')
	{
		if (var[i] == '%') // encontra a flag
		{
			/// Looks for flag kind cspdiuxX%
			if(var[i + 1] == 'c')
				print_char(va_arg(args, int));
			if(var[i + 1] == 's')
				print_string(va_arg(args, char *));
			if(var[i + 1] == 'p')   /// Imprime um Pointer
				print_pointer(va_arg(args, unsigned long)); // muito fixe mas não funciona, o valor não está a aparecer incompleto tens de debuggar para perceber mas a melhor soluçãp será fazer mais uma função que funcione com void*... Talvez essa função funcione em todos os hex e mais
			if(var[i + 1] == 'd' || var[i + 1] == 'i') // Leva um int 
				print_int(va_arg(args, int));
			if(var[i + 1] == 'u')
				print_uint(va_arg(args, unsigned int));
			if(var[i + 1] == 'x' || var[i + 1] == 'X')  /// faz um hexa 
				print_hex(va_arg(args, unsigned int), var[i + 1]);
			if(var[i + 1] == '%')
				print_char('%');
			i += 2;
		}
		else               // imprime sem encontrar a flag
		{
			print_char(var[i]);
			print_size++;
			i++;
		}
	}
	va_end(args);  // fecha a lista dos argumentos
	return(print_size);
}



int	main()
{
	char *yes = "oh yeah\n";
	char *no = "not\n";
	char c = 'U';
	int i = 230567;

	////My PrintF
	ft_printf("\n My Tester \n");

	ft_printf("Teste Pointer to char * : %p \n", &yes);
	ft_printf("Teste Pointer to char: %p \n", &c);
	ft_printf("Teste Pointer to int: %p \n", &i);

	

	///Real PrintF this printf is being wrongly used
	printf("\n Real Printf Tester \n");

	printf("Teste Pointer to char * : %p \n", &yes);
	printf("Teste Pointer to char: %p \n", &c);
	printf("Teste Pointer to int: %p \n", &i);




	// ///Real Hex Values
	// ft_printf("\n Real Hex Values \n");
	// ft_printf("Real hex int Value: %x \n", i);
	// ft_printf("Real hex char Value: %x \n", c);



	/// Hex print TESTER
	// long int i = -30;

	// ft_printf("hex, %X  \n", i);
	// printf("hex, %X  \n", i);
	// ft_printf("real int, %i  \n", i);
	// ft_printf("---\n");


	// i = -10;

	// ft_printf("hex, %X  \n", i);
	// printf("hex, %X  \n", i);
	// ft_printf("real int, %i  \n", i);
	// ft_printf("---\n");


	// i = -1;

	// ft_printf("hex, %X  \n", i);
	// printf("hex, %X  \n", i);
	// ft_printf("real int, %i  \n", i);
	// ft_printf("---\n");

	// i = 0;

	// ft_printf("hex, %X  \n", i);
	// printf("hex, %X  \n", i);
	// ft_printf("real int, %i  \n", i);
	// ft_printf("---\n");

}