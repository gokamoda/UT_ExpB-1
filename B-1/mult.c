#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 2進数化
int binary_byte(int *array, int n);

// 配列のメモリの動的確保
int *func_mallocation_(const int N);

// 配列の表示
void print_array_(const int *const array);

// 右シフト
int srl_(int *array);

// 左シフ(0in, cfout)
int sla_(int *array);

// 左ローテーション
int rla_(int *array, int cf);

// 10進数可
int decimal_byte_(int *array);

// 1バイト同士の足し算
int add_byte_(int* ans, int* array, int cf);

int main()
{

  printf("\n This program multiplies 2 positive integers.\n Both multiplicand and multiplier should be smaller than 255\n\n");
  // 被乗数
  int multiplicand;
  int *bi_multiplicand = func_mallocation_(8);

  // 乗数
  int multiplier;
  int *bi_multiplier = func_mallocation_(8);

  // 被乗数と乗数の読み込み
  printf("multiplicand:");
  scanf("%d", &multiplicand);
  printf("multiplier:");
  scanf("%d", &multiplier);

  // 乗数と被乗数の2進数表現
  binary_byte(bi_multiplicand, multiplicand);
  binary_byte(bi_multiplier, multiplier);
  printf("\nbinary expression\n");
  printf("multiplicand:\n");
  print_array_(bi_multiplicand);
  printf("multiplier:\n");
  print_array_(bi_multiplier);

  // ワーク領域の確保
  int *bi_work0 = func_mallocation_(8);
  int *bi_work1 = func_mallocation_(8);

  //ワーク領域に被乗数を格納
  binary_byte(bi_work0, multiplicand);
  binary_byte(bi_work1, 0);
  printf("work area:\n");
  print_array_(bi_work1);
  print_array_(bi_work0);

  // 回答領域の確保
  int *bi_ans0 = func_mallocation_(8);
  int *bi_ans1 = func_mallocation_(8);

  // 回答領域の初期化
  binary_byte(bi_ans0, 0);
  binary_byte(bi_ans1, 0);
  printf("ans area:\n");
  print_array_(bi_ans1);
  print_array_(bi_ans0);

  // 前処理終了，計算開始
  printf("\nbegin calculation \n\n");
  printf("--------------------\n");

  // carry flag
  int cf;

  while (decimal_byte_(bi_multiplier) != 0)
  {
    // 乗数の最下位ビットをcfに格納
    cf = srl_(bi_multiplier);
    printf("cf: %d\n", cf);

    // cfが1の時のみ掛算（足し算）を実行
    if(cf == 1){
      cf = 0;
      cf = add_byte_(bi_ans0, bi_work0, cf);
      cf = add_byte_(bi_ans1, bi_work1, cf);
    }

    // 次の位の計算で足しこむ数を準備
    cf = sla_(bi_work0);
    cf = rla_(bi_work1, cf);

    // debugのための表示
    printf("ans area:\n");
    print_array_(bi_ans1);
    print_array_(bi_ans0);
    printf("\n");

    printf("work area:\n");
    print_array_(bi_work1);
    print_array_(bi_work0);
    printf("\n");

    printf("bi_multiplier area:\n");
    print_array_(bi_multiplier);
    printf("\n");

  }
  printf("--------------------\n");

  // 積の表示
  printf("FINAL ANSWER: %d x %d = %d\n", multiplicand, multiplier, decimal_byte_(bi_ans1)*256 + decimal_byte_(bi_ans0));

  //メモリの開放
  free(bi_multiplicand);
  free(bi_multiplier);
  free(bi_ans0);
  free(bi_ans1);
  free(bi_work0);
  free(bi_work1);
  return 0;
}

// 2進数化
int binary_byte(int *array, int n)
{
  int remainder;
  for (int i = 1; i <= 8; i++)
  {
    remainder = n % 2;
    n /= 2;
    array[8 - i] = remainder;
  }
}

// 配列のメモリの動的確保
int *func_mallocation_(const int N)
{
  int *data = (int *)malloc(N * sizeof(int));
  if (data == NULL)
  {
    printf("Can not allocate memory. 'data' is NULL.\n");
    exit(EXIT_FAILURE);
  }
  return data;
}

// 配列の表示
void print_array_(const int *const array)
{
  for (int i = 0; i < 8; ++i)
  {
    printf(" %2d", array[i]);
  }
  printf("\n");
}

// 右シフト
int srl_(int *array)
{
  int cf = array[7];
  for (int i = 6; i >= 0; i--)
  {
    array[i + 1] = array[i];
  }
  array[0] = 0;
  return cf;
}

// 左シフ(0in, cfout)
int sla_(int *array){
  int cf = array[0];
  for(int i=0; i<=6; i++){
    array[i] = array[i+1];
  }
  array[7] = 0;
  return cf;
}

// 左ローテーション
int rla_(int *array, int cf){
  int cf_tmp;
  for(int i=0; i<=6; i++){
    array[i] = array[i+1];
  }
  array[7] = cf;
  return cf;
}

// 10進数化
int decimal_byte_(int *array)
{
  int decimal = 0;
  for (int i = 0; i <= 7; i++)
  {
    decimal += (int)pow(2, i) * array[8 - i - 1];
  }
  return decimal;
}

// 1バイト同士の足し算（cf含める）
int add_byte_(int* ans, int* array, int cf){
  int sum;
  for(int i=7; i>=0; i--){
    sum = ans[i] + array[i] + cf;
    cf =  sum / 2;
    ans[i] = sum % 2;
  }
  return cf;
}



