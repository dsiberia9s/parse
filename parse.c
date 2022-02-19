#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// исходная строка, разделительный символ, переменная (в которую будет записана длина массива)
char** Parse(char* src, char separator, int* length) {
  size_t charp = sizeof(char*);
  *length = 1;
  char** dst = calloc(*length, charp);
  *dst = src;
  char f = 0;
  while (*src) {
    if (*src == separator) {
      f = 1;
      dst = realloc(dst, charp * (*length + 1));
      *(dst + *length) = src + 1;
      (*length)++;
    }
    src++;
  }
  if (f)
    (*length)--;
  return dst;
}

// массив указателей на подстроки, его длина, № подстроки (которую нужно извлечь)
char* Cut(char** src, int length, int id) {
  int ss_length;
  if ((id < length) && (id != 0))
    ss_length = src[id + 1] - src[id];
  else
    ss_length = strlen(src[id]);
  char* dst = calloc(ss_length, sizeof(char));
  memcpy(dst, src[id], ss_length);
  return dst;
}

int Eatoi(char* src) {
  int dst = atoi(src);
  free(src);
  return dst;
}

double Eatof(char* src) {
  double dst = atof(src);
  free(src);
  return dst;
}

char Estoc(char* src) {
  char dst = src[0];
  free(src);
  return dst;
}

int main() {
  char* example = "$GPGSA,A,3,10,13,14,15,,,,,,,,,6.0,2.4,5.5,1*2D\r\n$GPVTG,0.00,T,,M,0.81,N,1.50,K,A*30\r\n_~\r\n";

  // парсим строку по \n
  int length_0;
  char** parse_0 = Parse(example, '\n', &length_0);

  // ---

  // парсим 0-ю подстроку по ,
  int length_1;
  char** parse_1 = Parse(Cut(parse_0, length_0, 0), ',', &length_1);

  // получаем из 0-й подстроки 1-й элемент в типе char
  printf("(char) %c\n", Estoc(Cut(parse_1, length_1, 1)));

  // получаем из 0-й подстроки 3-й элемент в типе int
  printf("(int) %d\n", Eatoi(Cut(parse_1, length_1, 3)));

  // ---

  // парсим 1-ю подстроку по ,
  int length_2;
  char** parse_2 = Parse(Cut(parse_0, length_0, 1), ',', &length_2);

  // получаем из 1-й подстроки 0-й элемент в char*
  printf("(char*) %s\n", Cut(parse_2, length_2, 0));

  // получаем из 1-й подстроки 5-й элемент в числовом типе float
  printf("(double) %f\n", Eatof(Cut(parse_2, length_2, 5)));

  // ---

  // парсим 2-ю строку по ,
  int length_3;
  char** parse_3 = Parse(Cut(parse_0, length_0, 2), ',', &length_3);

  // получаем из 2-й подстроки 0-й элемент в char*
  printf("(char*) %s\n", Cut(parse_3, length_3, 0));

  // очищаем память от парсинга строки
  free(parse_0);

  // очищаем память от парсинга 0-й подстроки
  free(parse_1);

  // очищаем память от парсинга 1-й подстроки
  free(parse_2);

  // очищаем память от парсинга 2-й подстроки
  free(parse_3);

  return 0;
}
