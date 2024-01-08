//#include <stdlib.h>
//void get_bin_value(unsigned char v){
//  for (int i = 0; i < 8; i++) {
//    printf("%c", (v & 0x80) ? '1' : '0');
//    v <<= 1;
//  }
//  printf("\n");
//  return 0;
//}
//
//void getSize(){
////    int mad[13] = {303,[11] =900};
////    size_t size_mad = sizeof(mad);
////    printf("size  = %d\n", size_mad);
////    for(int i = 0; i< 13; ++i){
////        printf("i = %d, value= %d\n", i, *(mad+i));
////    }
//}

//void array
//
//    float func_1[100] = {1.2,4.56,9.13};
//    float func_2[50];
//    int size_1 = sizeof(func_1)/sizeof(func_1[0]);
//    int size_2 = sizeof(func_2)/sizeof(func_2[0]);
//    int size = (size_1 < size_2) ? size_1: size_2;
//    printf("sixe = %d\n", size);
//    for (int i = 0; i < size; ++i){
//        func_2[i] = func_1[i];
//    }
//
//    for(int i = 0; i < size; ++i){
//        printf("%.2f   ", func_2[i]);
//    }


//void* append(short* data, size_t *length, size_t *capacity, short value){
//    if(*length >= *capacity){
//        short *ar = malloc(sizeof(short) * 2 **capacity);
//        if(ar == NULL)
//            return data;
//
//        (*capacity) *=2;
//        for(int i=0; i<*length; ++i){
//            ar[i] = data[i];
//        }
//        free(data);
//        data = ar;
//    }
//        data[*length] = value;
//        (*length)++;
//        return data;
//}
//
//int main(void){
//    size_t capacity = 10;
//    size_t length = 0;
//
//    short *data = malloc(sizeof(short) * capacity);
//    for(int i = 0; i < 22; ++i){
//        data = append(data, &length, &capacity, (short) i);
//    }
//    printf("capacity = %u, length = %u\n", capacity, length);
//
//    for(int i = 0; i <length; ++i){
//        printf("%d", data[i]);
//    }
//
//    return 0;
//}
