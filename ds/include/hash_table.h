#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stddef.h> /* size_t */

typedef struct hash_table ht_t;
/*
    typedef struct pair
    {
        void *key;
        void *value;
    } pair_t;
    
    struct hash_table
    {
        sll_t **ht_items; // array of sll of pair_t
        int (*is_match)(const void *key1, const void *key2);
        size_t (*hash_func)(void *key);
        size_t size;
    }
*/

/*
 * Description: The function creates an instance of hash table.
 * Parameters: @hash_func pointer to the hash function
 * Return: instance of hash table
 * Complexity: 0(1)
 */
ht_t *HTCreate(size_t (*hash_func)(const void *key),
			   size_t size,
			   int (*is_match)(const void *key1, const void *key2));

/*
 * Description: The function destroys an instance of hash table.
 * Parameters: @ht is an instance of hash table which should be destroyed.
 * Return: Nothing
 * Complexity:
 *  WC: O(n)
 *  AVR: O(n)
 */
void HTDestroy(ht_t *ht);

/*
 * Description: The function inserts a key-value pair into the hash table.
 * If data at the key passed already exists, it will be overwritten.
 * Parameters: 
 *  @ht is an istance of hash table.
 *  @key is a pointer to the key.
 *  @value is a pointer to the data.
 * Return: @int is a status: 0 on SUCCESS and non-zero on FAIL
 * Complexity:
 *  WC: O(n)
 *  AVR: O(1)
 */
int HTInsert(ht_t *ht, const void *key, void *value);

/*
 * Description: The function removes a key-value pair from the hash table.
 * Parameters: 
 *  @ht is an istance of hash table.
 *  @key is a pointer to the key.
 * Return: Nothing.
 * Complexity:
 *  WC: O(n)
 *  AVR: O(1)
 */
void HTRemove(ht_t *ht, const void *key);

/*
 * Description: The function searching value by @key.
 * Parameters: 
 *  @ht is an istance of hash table.
 *  @key is a pointer to the key.
 * Return: 
 *  @void* is a pointer to the value which was found by @key.
 *  @NULL is a NULL pointer, if @key was not found.
 * Complexity:
 *  WC: O(n)
 *  AVR: O(1)
 */
void *HTFind(const ht_t *ht, const void *key);

/*
 * Description: The function returns number of pairs in the hash table.
 * Parameters: @ht is an instance of hash table.
 * Return: @size_t is number of pairs in the hash table.
 * Complexity: O(1)
 */
size_t HTSize(const ht_t *ht);

/*
 * Description: The function allows to check whether the instance of hash table is empty or not.
 * Parameters: @ht is an instance of hash table.
 * Return: @int is a value between 0 and 1
 *  @1, if the instance of hash table is empty.
 *  @0, if the instance of hash table is not empty.
 * Complexity: O(n)
 */
int HTIsEmpty(const ht_t *ht);


/*
 * Description: The function allows to apply any function to each @value
 * in key-value pair in the hash table.
 * Parameters: 
 *  @ht is an instance of hash table.
 *  @action_func is a function which performs some action to each @value
 *  in key-value pair in the hash table.
 *  @params is a params required for function action.
 * Return: @int
 *  @1, if the function is SUCCESS.
 *  @0, if the function is FAILED.
 * Complexity: O(n)
 */
 int HTForEach(ht_t *ht, int (*action_func)(void *data, void *params), void *params);
 
#endif /* __HASH_TABLE_H__ */
