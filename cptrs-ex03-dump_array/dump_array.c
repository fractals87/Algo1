/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void dump_array(const void *base, size_t num_elem, size_t elem_size, void (*dump_element)(const void *, FILE *), FILE *fp);
static void dump_int(const void *p, FILE *fp);
static void dump_string(const void *p, FILE *fp);


void dump_array(const void *base, size_t num_elem, size_t elem_size, void (*dump_element)(const void *, FILE *), FILE *fp)
{
    assert( base != NULL );
    assert( fp != NULL );
    const unsigned char *pcb = base;
    for(size_t i=0;i<num_elem;i++){
        //printf("--%d\n",*(int*)(base + (i * elem_size )));
        const void *elem = pcb + i*elem_size;
        dump_element(elem,fp);
    }

}

void dump_int(const void *p, FILE *fp)
{
    assert( p != NULL );
    assert( fp != NULL );

    //printf("--%d\n",*(int*)(p));
    fp = fopen("int.txt","a+");
    fprintf(fp,"--%d\n",*(int*)(p));
    fclose(fp);
}    

void dump_string(const void *p, FILE *fp)
{
    assert( p != NULL );
    assert( fp != NULL );
    
    fp = fopen("string.txt","a+");
    fprintf(fp,"--%s\n",*(char**)(p));
    fclose(fp);
}

int main()
{
    int iary[] = {1, 20, 25, 32, 76, 123};
    const char *sary[] = {"e01","e02","e03","e04","e05","e06"};
    FILE *fp = stdout;

    dump_array(iary, sizeof iary/sizeof iary[0], sizeof iary[0], dump_int, fp);
    fputc('\n', fp);
    dump_array(sary, sizeof sary/sizeof sary[0], sizeof sary[0], dump_string, fp);
    fputc('\n', fp);

    return 0;
}
