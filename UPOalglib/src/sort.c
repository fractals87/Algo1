/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/*
 * Copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 * This file is part of UPOalglib.
 *
 * UPOalglib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * UPOalglib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include "sort_private.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define CUTOFF 3

void swap(void* elem1, void* elem2, size_t size ){
    unsigned char* temp = malloc(size);
    memmove(temp, elem1, size);
    memmove(elem1, elem2, size);
    memmove(elem2, temp, size);
    free(temp);
}

void upo_insertion_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    unsigned char* base_ptr = (unsigned char*) base;
    void* temp = malloc(size);
    for(size_t i=1; i<n; i++){
        size_t j=i;
        while(j>0 && cmp(base_ptr + j*size, base_ptr + (j-1)*size)<0 ){
            //printf("INS %f\n ",*((double*)(base_ptr+j*size)));fflush(stdout);
            memmove(temp,base_ptr + (j-1) * size, size);
            memmove(base_ptr + (j-1)*size,base_ptr +j*size,size);
            memmove(base_ptr + j*size,temp,size);
            j--;
        }
    }
    free(temp);
}

void upo_merge(void* base, size_t lo, size_t mid, size_t hi, size_t size, upo_sort_comparator_t cmp){
    size_t i=0;
    size_t j=mid +1-lo;
    size_t nElem = hi-lo+1;
    
    unsigned char* trackAux= (unsigned char*) malloc(nElem*size);
    unsigned char* trackBase = (unsigned char*)base;
    for(size_t index=0; index<nElem; index++){
        memcpy(trackAux+index*size, trackBase+(index+lo)*size,size);    
    }
    
    for(size_t k=lo; k<=hi; k++){
        if(i>(mid-lo)){
            memcpy(trackBase+k*size,trackAux+j*size,size);
            j++;
        }else if(j>(hi-lo)){
            memcpy(trackBase+k*size,trackAux+i*size,size);
            i++;
        }else if(cmp(trackAux+j*size,trackAux+i*size)<0){
            memcpy(trackBase+k*size,trackAux+j*size,size);
            j++;
        }else{
           memcpy(trackBase+k*size,trackAux+i*size,size);
           i++;
        }
    }
    
    free(trackAux);
}

void upo_merge_sort_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp){
    if(lo>=hi) return;
    size_t mid = (lo+hi)/2;
    upo_merge_sort_rec(base,lo,mid,size,cmp);
    upo_merge_sort_rec(base,mid+1,hi,size,cmp);
    upo_merge(base,lo,mid,hi,size,cmp);
}

void upo_merge_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    upo_merge_sort_rec(base,0,n-1,size,cmp);
}

size_t partition (void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp){
    
    unsigned char* base_ptr = (unsigned char*) base;
    size_t p,i,j;
    p=lo;
    i=lo;
    j=hi+1;

    while(1){
    do{i++;}while(!((i>=hi) || cmp(base_ptr + i*size, base_ptr + p*size)>=0));
    do{j--;}while(!((j<=lo) || cmp(base_ptr + j*size, base_ptr + p*size)<=0));
    if(i>=j)
        break;
    swap(base_ptr + i*size, base_ptr +j*size, size);
    }

   swap(base_ptr + p*size, base_ptr +j*size, size); 
   return j;

}

void upo_quick_sort_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp){

    if(lo>=hi)
        return;

    size_t j = partition(base,lo,hi,size,cmp);
    if(j>0)
        upo_quick_sort_rec(base, lo, j-1, size, cmp);
    upo_quick_sort_rec(base,j+1,hi,size,cmp);

}

void upo_quick_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
   upo_quick_sort_rec(base, 0, n-1, size, cmp);
}





void pivotSwitch(void *base, size_t lo,size_t mid, size_t hi, size_t size, upo_sort_comparator_t cmp){

    unsigned char* base_ptr = (unsigned char*) base;

    unsigned char* a = base_ptr + lo*size;
    unsigned char* b = base_ptr + mid*size;
    unsigned char* c = base_ptr + hi*size;

    printf("prima: ");
    printf(" %s ",*((char**)(a)));
    printf(" %s ",*((char**)(b)));
    printf(" %s ",*((char**)(c)));

    if(cmp(a,b)<0){

        if(cmp(b,c)<0)
            return;
        
        else{
            
            if(cmp(a,c)<0)
                swap(b,c,size);
            
            else{
                
                swap(a,c,size);
                swap(b,c,size);
            }
        }
    }

    else{

        if(cmp(b,c)>0){
            swap(a,c,size);
            return;
        }

        else{

            if(cmp(a,c)<0)
                swap(a,b,size);

            else{

                swap(a,b,size);
                swap(b,c,size);
            }
        }

    }   

    printf("dopo: ");
    printf(" %s ",*((char**)(a)));
    printf(" %s ",*((char**)(b)));
    printf(" %s ",*((char**)(c)));
}



size_t upo_partition_median_3(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp){

    unsigned char* base_ptr = (unsigned char*) base;

    size_t mid = (lo+hi)/2;
    
    pivotSwitch(base,lo,mid,hi,size,cmp);

    swap(base_ptr + (lo+1)*size, base_ptr + mid*size, size);

    size_t j = partition(base,lo+1,hi-1,size,cmp);

    printf("MEDIAN %s ",*((char**)(base_ptr+j*size)));
    fflush(stdout);

    return j;

    

}

void upo_quick_sort_median3_cutoff_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp){

    if(lo>=hi)
        return;

    if(hi-lo+1 <= CUTOFF)
        upo_insertion_sort(base,hi-lo+1,size,cmp);

    else{

        size_t j= upo_partition_median_3(base,lo,hi,size,cmp);
        unsigned char* base_ptr = (unsigned char*) base;
        printf("QUICK %s \n",*((char**)(base_ptr+j*size)));
        fflush(stdout);

        if(j>0)
            upo_quick_sort_median3_cutoff_rec(base,lo,j-1,size,cmp);
        upo_quick_sort_median3_cutoff_rec(base,j+1,hi,size,cmp);

    }
}

void upo_quick_sort_median3_cutoff(void *base, size_t n, size_t size, upo_sort_comparator_t cmp){

    upo_quick_sort_median3_cutoff_rec(base,0,n-1,size,cmp);
}

void upo_odd_even(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    
    size_t i;
    char* prt = (char*)base; 
    printf("\n");
    for(i=0;i<n-1;i++){
        printf("%.2f ", *((double*)(prt+i*size))); fflush(stdout);
    }
    printf("\n");
    char* tmp = malloc(size);
    int order=0;
    while(order==0)
    {
        order=1;
        //printf("\n in order\n");fflush(stdout);
        for(i=1; i<n-1; i+=2 )
        {   
            if(cmp(prt+i*size,prt+(i+1)*size)>0)
            {
                //printf("ciao1\n");fflush(stdout);        
                memmove(tmp,prt+i*size,size);   
                //printf("ciao2\n");fflush(stdout);                        
                memmove(prt+i*size,prt+(i+1)*size,size);
                memmove(prt+(i+1)*size,tmp,size);
                //printf("ciao3\n");fflush(stdout);                        
                order=0;
            }
        }
        
        for(i=0; i<n-1; i+=2 )
        {
            if(cmp(prt+i*size,prt+(i+1)*size)>0)
            {
                memmove(tmp,prt+i*size,size);
                memmove(prt+i*size,prt+(i+1)*size,size);
                memmove(prt+(i+1)*size,tmp,size);
                order=0;                
            }
        }
    }

    for(i=0;i<n-1;i++){
        printf("%.2f ", *((double*)(prt+i*size))); fflush(stdout);
    }
    printf("\n");

    

    /*
    int sorted = 0;
    unsigned char* base_ptr = (unsigned char*) base;
    //printf("NELEM : %zu\n",n);
    //printf("SIZE : %d\n",size);    
    //printf("FIRST %f\n ",*((double*)(base_ptr)));fflush(stdout);
    //PRINT 
    for(size_t i=0; i<n-1; i++){
        //printf(" %.2f ",*((double*)(base_ptr+i*size)));
        fflush(stdout);
    }
    //printf("\n");
    while(sorted == 0)
    {
        sorted = 1;
        for(size_t i=1; i<n-1; i+=2){
            //printf("CMP %.2f -- %.2f\n  ",*((double*)(base_ptr+i*size)),*((double*)(base_ptr+(i+1)*size)));
            if(cmp(base_ptr + i*size,base_ptr + (i+1)*size)>0)
            {
                //swap(base_ptr + i*size,base_ptr + (i+1)*size,size);
                char *temp = malloc(size);
                memmove(temp,base_ptr+i*size,size);
                memmove(base_ptr+i*size,base_ptr+(i+1)*size,size);
                memmove(base_ptr+(i+1)*size,temp,size);
                sorted=0;                
            }
        }
        for(size_t i=0; i<n-1; i+=2){
            if(cmp(base_ptr + i*size,base_ptr + (i+1)*size)>0)
            {
                swap(base_ptr + i*size,base_ptr + (i+1)*size,size);
                sorted = 0;                
            }
        }
    }
    //PRINT 
    for(size_t i=0; i<n-1; i++){
        //printf(" %.2f ",*((double*)(base_ptr+i*size)));
        fflush(stdout);
    }
    */
}
