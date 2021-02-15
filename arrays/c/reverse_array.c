#include <stdlib.h>
#include <stdio.h>

#define ARR_SIZE(x) (sizeof(x)/sizeof(x[0]))

/* Forward declaration */
static void printArray_testArrayArg(int array[], int size);
static void printArray(int *array, int size);


static void printArray_testArrayArg(int array[], int size)
{
  printArray(array, size);
}

static void printArray(int *array, int size)
{
  printf("{");
  for(int i = 0; i < size - 1; i++)
  {
    printf("%d, ", *array);
    array++;
  }
  printf("%d}\n", *array);
}

int main(int argc, char** argv)
{
  int array[] = {1,2,3,4,5};

  printf("Array size = %lu\n", ARR_SIZE(array));

  printArray(array, ARR_SIZE(array));
  printArray_testArrayArg(array, ARR_SIZE(array));

  for(int i = 0; i < ARR_SIZE(array) / 2; i++)
  {
    int tmp;

    tmp = array[i];
    array[i] = array[ARR_SIZE(array) - 1 - i];
    array[ARR_SIZE(array) - 1 - i] = tmp;
  }

  printArray(array, ARR_SIZE(array));

  return 0;
}
