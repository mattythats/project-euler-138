#include <stdio.h>
#include <math.h> //sqrt, pow
#include <stdint.h> //int64_t

int main(){
  int64_t found = 0, base = 16, leg = 17, totalLegLen = 0;
  long double height;
  while(found < 12){
   height = sqrt(pow(leg,2) - pow(base/2,2));
   if(height == base-1 || height == base+1){
     found++;
     printf("Triangle %i found!\tB: %i\tL: %i\tH: %i\n", found, base, leg, (int)height);
     base+=2;
     totalLegLen+=leg;
     leg = (int)sqrt(pow(base-1,2)+pow(base/2,2))-1;
   } else if(height > base+1){
     base+=2;
     leg = (int)sqrt(pow(base-1,2)+pow(base/2,2))-1;
   }
   leg++;
  }
  printf("Total Leg Len: %i\n", totalLegLen);
  return 0;
}
