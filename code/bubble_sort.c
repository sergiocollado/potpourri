// parameter in: pt _is the pointer to an array v[size].
// parameter in: size _is the size of the input array v[].

void BubbleSort(uint8_t *pt, uint32_t size){
   uint32_t i,j; uint8_t data,*p1,*p2;
   for(i=1; i<size; i++){
     p1 = pt; // pointer to beginning
     for(j=0; j<size-i; j++){
       p2 = p1+1; // p2 points to the element after p1
       if(*p1 > *p2){
         data = *p1; // swap
         *p1 = *p2;
         *p2 = data;
       }
      p1++; 
    }
  }
}


/* usage:

void main()
{

int v_data[100];

BubbleSort(v_data, 100);
//or
BubbleSort(&v_data[0],100);

}

*/
