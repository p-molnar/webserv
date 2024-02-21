/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   infin_mult.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 12:59:48 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/11/28 10:10:44 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int ft_strlen(char *str)
{
    int i = 0;

    while (str[i])
        i++;
    return (i);
}

char    *infin_mult(char *num1, char *num2)
{
    int len1 = ft_strlen(num1);
    int len2 = ft_strlen(num2);

    int maxlen = len1 + len2 + 1;
    char *result = (char *)malloc(maxlen);
    if (!result)
        exit(EXIT_FAILURE);
    for (int i = 0; i < maxlen - 1; i++)
        result[i] = '0';
    
    for (int i = len1 - 1; i >= 0; i--)
    {
        for (int j = len2 - 1; j >= 0; j--)
        {
            int res = (num1[i] - '0') * (num2[j] - '0') + (result[i + j + 1] - '0'); 
            result[i + j + 1] = (res % 10) + '0';
            result[i + j] += res / 10;
        }
    }
    int start = 0;
    while (start < maxlen - 1 && result[start] == '0') {
        start++;
    }
    return (&result[start]);
}

int main(int argc, char **argv) {

    if (!argv || argc == 0)
        return (EXIT_FAILURE);
    if (argv[1][0] == '0' || argv[2][0] == '0')
        write(1, "0\n", 3);
    else 
    {
        char *result = infin_mult(argv[1], argv[2]);
        printf("%s\n", result);
    }
}