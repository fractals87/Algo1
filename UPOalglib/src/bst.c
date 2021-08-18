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

#include "bst_private.h"
#include <stdio.h>
#include <stdlib.h>


/**** EXERCISE #1 - BEGIN of FUNDAMENTAL OPERATIONS ****/


upo_bst_t upo_bst_create(upo_bst_comparator_t key_cmp)
{
    upo_bst_t tree = malloc(sizeof(struct upo_bst_s));
    if (tree == NULL)
    {
        perror("Unable to create a binary search tree");
        abort();
    }

    tree->root = NULL;
    tree->key_cmp = key_cmp;

    return tree;
}

void upo_bst_destroy(upo_bst_t tree, int destroy_data)
{
    if (tree != NULL)
    {
        upo_bst_clear(tree, destroy_data);
        free(tree);
    }
}

void upo_bst_clear_impl(upo_bst_node_t *node, int destroy_data)
{
    if (node != NULL)
    {
        upo_bst_clear_impl(node->left, destroy_data);
        upo_bst_clear_impl(node->right, destroy_data);

        if (destroy_data)
        {
            free(node->key);
            free(node->value);
        }

        free(node);
    }
}

void upo_bst_clear(upo_bst_t tree, int destroy_data)
{
    if (tree != NULL)
    {
        upo_bst_clear_impl(tree->root, destroy_data);
        tree->root = NULL;
    }
}

upo_bst_node_t* upo_bst_node_create(void* k, void* v){
    upo_bst_node_t* node = (upo_bst_node_t*) malloc(sizeof(upo_bst_node_t));
    node->key = k;
    node->value = v;
    node->left = NULL;
    node->right = NULL;
    
    return node;
}

upo_bst_node_t* upo_bst_put_impl(upo_bst_node_t* n, void *key, void *value, void* oldValue, upo_bst_comparator_t cmp)
{
    oldValue = NULL;
    if(n == NULL){
        return upo_bst_node_create(key,value);
    }else if(cmp(key,n->key)<0){
        n->left = upo_bst_put_impl(n->left, key, value, oldValue, cmp);
    }else if(cmp(key,n->key)>0){
        n->right = upo_bst_put_impl(n->right, key, value, oldValue, cmp);
    }else{
        oldValue = n->value;
        n->value = value;
    }
    return n;
}

void* upo_bst_put(upo_bst_t tree, void *key, void *value)
{
    void* oldValue = NULL;
    tree->root = upo_bst_put_impl(tree->root, key, value, oldValue, tree->key_cmp);
}

upo_bst_node_t* upo_bst_insert_impl(upo_bst_node_t* n, void *key, void *value, void* oldValue, upo_bst_comparator_t cmp)
{
    oldValue = NULL;
    if(n == NULL){
        return upo_bst_node_create(key,value);
    }else if(cmp(key,n->key)<0){
        n->left = upo_bst_insert_impl(n->left, key, value, oldValue, cmp);
    }else if(cmp(key,n->key)>0){
        n->right = upo_bst_insert_impl(n->right, key, value, oldValue, cmp);
    }
    return n;
}

void upo_bst_insert(upo_bst_t tree, void *key, void *value)
{
    void* oldValue = NULL;
    tree->root = upo_bst_insert_impl(tree->root, key, value, oldValue, tree->key_cmp);
}

upo_bst_node_t* upo_bst_get_impl(upo_bst_node_t* node,const void *key, upo_bst_comparator_t cmp)
{
    if(node==NULL){
        return NULL;
    }
    if(cmp(key,node->key)<0){
        return upo_bst_get_impl(node->left, key, cmp);
    }else if(cmp(key,node->key)>0){
        return upo_bst_get_impl(node->right, key, cmp);
    }else{
        return node;
    }
}

void* upo_bst_get(const upo_bst_t tree, const void *key)
{
    upo_bst_node_t* node = NULL;
    node = upo_bst_get_impl(tree->root, key, tree->key_cmp);
    if(node != NULL){
        return node->value;
    }else{
        return NULL;
    }
}

int upo_bst_contains(const upo_bst_t tree, const void *key)
{
    if(upo_bst_get(tree, key)!=NULL){
        return 1;
    }else{
        return 0;
    }
}

upo_bst_node_t* upo_bst_delete_1c_impl(upo_bst_node_t* node, int destroy_data){
    /*printf("CANCELLO %d==%d\n",*(int*)node->key,*(int*)node->value);    
    fflush(stdout);abort();  */
    upo_bst_node_t* nodeTmp = node;
    if(node->left!=NULL){
        node = node->left;
    }else{
        node = node->right;
    }
    if (destroy_data!=0)
    {
        free(node->key);
        free(node->value);
    }

    free(nodeTmp);
    return node;
}

upo_bst_node_t* upo_bst_delete_2c_max_impl(upo_bst_node_t* node){
    if(node==NULL)
        return NULL;
    else if(node->right!=NULL)
        return upo_bst_delete_2c_max_impl(node->right);
    else
        return node;
}


upo_bst_node_t* upo_bst_delete_2c_impl(upo_bst_node_t* node,upo_bst_comparator_t cmp, int destroy_data){
    upo_bst_node_t* nodeTmp = upo_bst_delete_2c_max_impl(node->left);
    node->key = nodeTmp->key;
    node->value = nodeTmp->value;
    node->left = upo_bst_delete_impl(node->left, nodeTmp->key, cmp, destroy_data);
    return node;
}

upo_bst_node_t* upo_bst_delete_impl(upo_bst_node_t* node, const void *key, upo_bst_comparator_t cmp, int destroy_data)
{
    /*if(node == NULL){
        printf("NULL");    
        //printf("%d==%d\n",*(int*)node->key,*(int *)key);    
        fflush(stdout);abort();  
    }
    if(node == NULL)
        return NULL;

        printf(" CANCELLO %d==%d COMPARO %d\n",*(int*)node->key,*(int *)key,cmp(node->key,key));    
        fflush(stdout);abort();          
     */   
    if(cmp(key,node->key)<0){
        node->left = upo_bst_delete_impl(node->left,key,cmp,destroy_data);
    }else if(cmp(key,node->key)>0){
        node->right = upo_bst_delete_impl(node->right,key,cmp,destroy_data);       
    }else if(node->left != NULL && node->right != NULL){
    //printf("MIN = %d",*(int*)node->key);fflush(stdout);abort();
        node = upo_bst_delete_2c_impl(node,cmp,destroy_data);
    }else{
        //printf("1C %d==%d\n",*(int*)node->key,*(int *)key); fflush(stdout);abort(); 
        node = upo_bst_delete_1c_impl(node,destroy_data);
    }
    return node;    
}

void upo_bst_delete(upo_bst_t tree, const void *key, int destroy_data)
{
    /*if(tree->root==NULL)
        printf("NULL ROOT\n");
    else
        printf("NOT NULL ROOT\n");
    fflush(stdout);abort();*/ 
    if(tree!=NULL)
        tree->root = upo_bst_delete_impl(tree->root,key,tree->key_cmp,destroy_data);
}

size_t upo_bst_size_impl(upo_bst_node_t* node)
{
    if(node==NULL)
    {
        return 0;
    }
    return 1 + upo_bst_size_impl(node->left) + upo_bst_size_impl(node->right);
}

size_t upo_bst_size(const upo_bst_t tree)
{
    if(tree==NULL)
        return 0;
    else    
        return upo_bst_size_impl(tree->root);
}

int upo_bst_isleaf_imp(upo_bst_node_t* node)
{
    if(node->left == NULL && node->right == NULL)
        return 1;
    else
        return 0;
}

size_t upo_bst_max_impl(size_t left, size_t right)
{
    if(left > right)
        return left;
    else
        return right;

}

size_t upo_bst_height_impl(upo_bst_node_t* node)
{
    if(node == NULL || upo_bst_isleaf_imp(node))
    {
        return 0;
    } 
    return 1 + upo_bst_max_impl(upo_bst_height_impl(node->left), upo_bst_height_impl(node->right));
}

size_t upo_bst_height(const upo_bst_t tree)
{
    return upo_bst_height_impl(tree->root);
}

void upo_bst_traverse_in_order_impl(upo_bst_node_t* node, upo_bst_visitor_t visit, void *visit_context)
{
    if(node!=NULL){
        upo_bst_traverse_in_order_impl(node->left, visit, visit_context);
        visit(node->key, node->value, visit_context);
        upo_bst_traverse_in_order_impl(node->right, visit, visit_context);
    }
}

void upo_bst_traverse_in_order(const upo_bst_t tree, upo_bst_visitor_t visit, void *visit_context)
{
    upo_bst_traverse_in_order_impl(tree->root, visit, visit_context);
}

int upo_bst_is_empty(const upo_bst_t tree)
{
    if(tree == NULL){
        return 1;
    }else{
        if(tree->root == NULL)
            return 1;
        else
            return 0;
    }
}


/**** EXERCISE #1 - END of FUNDAMENTAL OPERATIONS ****/


/**** EXERCISE #2 - BEGIN of EXTRA OPERATIONS ****/

upo_bst_node_t* upo_bst_min_impl(upo_bst_node_t* node)
{
    if(node->left == NULL)
        return node->key;
    else
        return upo_bst_min_impl(node->left);
}

void* upo_bst_min(const upo_bst_t tree)
{
    if(tree==NULL)
        return NULL;
    if(tree->root == NULL)
        return NULL;
    return upo_bst_min_impl(tree->root);
}

upo_bst_node_t* upo_bst_max_impl2(upo_bst_node_t* node)
{
    if(node==NULL) return NULL; 
    if(node->right == NULL)
        return node->key;
    else
        return upo_bst_max_impl2(node->right);
}

void* upo_bst_max(const upo_bst_t tree)
{
    if(tree==NULL)
        return NULL;
    if(tree->root == NULL)
        return NULL;
    return upo_bst_max_impl2(tree->root);
}

void upo_bst_delete_min(upo_bst_t tree, int destroy_data)
{
    if(tree==NULL)
        return;
    if(tree->root == NULL)
        return;
    const void* min_key = upo_bst_min(tree);
    upo_bst_delete(tree,min_key,destroy_data);
    
}

void upo_bst_delete_max(upo_bst_t tree, int destroy_data)
{
    if(tree==NULL)
        return;
    if(tree->root == NULL)
        return;
    const void* max_key = upo_bst_max(tree);
    upo_bst_delete(tree,max_key,destroy_data);
}

void* upo_bst_floor_impl(upo_bst_node_t* node, const void *key,upo_bst_comparator_t key_cmp){
    /*if(node==NULL)
        return NULL;
    if(key_cmp(key,node->key)<0){
        if(node->left!=NULL)
            return upo_bst_floor_impl(node->left,key,key_cmp);
        else
            return NULL;
    }
    
    if(key_cmp(key,node->key)>0){
        void* floor=upo_bst_floor_impl(node->right,key,key_cmp);
        if(floor!=NULL)
            return floor;
        else
            return node->key;
    }else{
        return node->key;
    }*/
    if(node==NULL)
        return NULL;
    if(key_cmp(node->key,key)==0)
        return node->key;
    if(key_cmp(node->key,key)>0)
        return upo_bst_floor_impl(node->left,key,key_cmp);    
        
    void* floor = upo_bst_floor_impl(node->right, key,key_cmp);
    if(floor==NULL)
        return node->key;
    if(key_cmp(key,floor)>=0)
        return floor;
    else
        return node->key;
}

void* upo_bst_floor(const upo_bst_t tree, const void *key)
{
    if(tree==NULL)
        return NULL;
    if(tree->root == NULL)
        return NULL;
    return upo_bst_floor_impl(tree->root, key,tree->key_cmp);
}

void* upo_bst_ceiling_impl(upo_bst_node_t* node, const void *key,upo_bst_comparator_t key_cmp){
    /*if(node==NULL)
        return NULL;
    if(key_cmp(key,node->key)<0){
        void* ceil=upo_bst_floor_impl(node->left,key,key_cmp);
        if(ceil!=NULL)
            return ceil;
        else
            return node->key;                
    }
    
    if(key_cmp(key,node->key)>0){
        if(node->right!=NULL)
            return upo_bst_floor_impl(node->right,key,key_cmp);
        else
            return NULL;
    }else{
        return node->key;
    }*/
    if(node==NULL)
        return NULL;
    
    //printf("ESAMINO : %d\n", *(int*)node->key);fflush(stdout);

    //if(*(int*)node->key== 0)
    //    printf("res cmp : %d\n", key_cmp(key, node->key) );fflush(stdout);
   
    if(key_cmp(key, node->key)==0)
        return node->key;
    if(key_cmp(key, node->key)>0)
        return upo_bst_ceiling_impl(node->right, key, key_cmp);
        
    void* ceil = upo_bst_ceiling_impl(node->left, key, key_cmp);
    /*if(*(int*)node->key== 0){
        if(ceil==NULL){
        printf("CEIL NULL");fflush(stdout);
        }
    }*/
    if(ceil == NULL)
        return node->key;
    if(key_cmp(ceil,key)>=0)
        return ceil;
    else
        return node->key;
}

void* upo_bst_ceiling(const upo_bst_t tree, const void *key)
{
    if(tree==NULL)
        return NULL;
    if(tree->root == NULL)
        return NULL;
    return upo_bst_ceiling_impl(tree->root, key,tree->key_cmp);
}

void upo_bst_keys_range_impl(upo_bst_node_t* node, const void* low_key, const void *high_key, upo_bst_key_list_t* list, upo_bst_comparator_t key_cmp)
{
    if(node==NULL)
        return;
    if(key_cmp(node->key, low_key)>=0)
        upo_bst_keys_range_impl(node->left, low_key, high_key, list, key_cmp);
    if(key_cmp(node->key, low_key)>=0 && (key_cmp(node->key, high_key)<=0))
    {
        upo_bst_key_list_t keynode = malloc(sizeof(upo_bst_key_list_t));
        keynode->key = node->key;
        keynode->next = *list;
        *list = keynode;
    }
    if(key_cmp(node->key, low_key)<=0)
        upo_bst_keys_range_impl(node->right, low_key, high_key, list, key_cmp);
}

upo_bst_key_list_t upo_bst_keys_range(const upo_bst_t tree, const void *low_key, const void *high_key)
{
    if(tree==NULL)
        return NULL;
    if(tree->root == NULL)
        return NULL;

    upo_bst_key_list_t list = NULL;
    upo_bst_keys_range_impl(tree->root, low_key, high_key, &list, tree->key_cmp);
    
    return list;
}

void upo_bst_keys_impl(upo_bst_node_t* node, upo_bst_key_list_t* list)
{
    if(node!=NULL)
    {
        upo_bst_keys_impl(node->left, list);
        
        upo_bst_key_list_t keynode = malloc(sizeof(upo_bst_key_list_t));
        keynode->key = node->key;
        keynode->next = *list;
        *list = keynode;
        
        upo_bst_keys_impl(node->right, list);
    }
}

upo_bst_key_list_t upo_bst_keys(const upo_bst_t tree)
{
    if(tree==NULL)
        return NULL;
    if(tree->root == NULL)
        return NULL;
        
    upo_bst_key_list_t list = NULL;
    upo_bst_keys_impl(tree->root,&list);
    
    return list;        
}

int upo_bst_is_bst_impl(upo_bst_node_t* node, const void *min_key, const void *max_key, upo_bst_comparator_t key_cmp)
{
    if(node==NULL)
        return 1;
    if(node->left != NULL){

        //printf("LEFT %d<%d RES %d\n",*(int*)node->key, *(int*)node->left->key,key_cmp(node->key, node->left->key) );    
        if(key_cmp(node->key, node->left->key)<0){
            return 0;
        }
    }
    if(node->right != NULL){
    //printf("LEFT %d<%d RES %d\n\n",*(int*)node->key, *(int*)node->right->key,key_cmp(node->key, node->left->key) );
        if(key_cmp(node->key, node->right->key)>0){
            return 0;
        }
    }

                
    if(key_cmp(node->key, min_key)<=0 || key_cmp(node->key, max_key)>=0)
        return 0;
    return upo_bst_is_bst_impl(node->left,min_key,max_key,key_cmp) && upo_bst_is_bst_impl(node->right,min_key,max_key,key_cmp);
 return 1;       
}

int upo_bst_is_bst(const upo_bst_t tree, const void *min_key, const void *max_key)
{
    if(tree==NULL)
        return NULL;
    /*if(tree->root == NULL)
        return NULL;*/
    //return 1;  
    return upo_bst_is_bst_impl(tree->root, min_key, max_key, tree->key_cmp);
}


/**** EXERCISE #2 - END of EXTRA OPERATIONS ****/


upo_bst_comparator_t upo_bst_get_comparator(const upo_bst_t tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    return tree->key_cmp;
}
