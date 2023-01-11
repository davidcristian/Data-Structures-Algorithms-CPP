# Hashtable
Implement the given container (ADT) in C++ using a given representation and a hashtable with a given collision resolution (separate chaining, coalesced chaining, open addressing) as a data structure. You are not allowed to use any container or data structure from STL or from any other library.

Do not implement a separate class for the hashtable (or dynamic array, or anything), implement the container directly!

The hashtable has to be dynamic: no matter what collision resolution has to be used, set a threshold for α and resize and rehash the table when the actual load factor is higher than α.

### 28. ADT MultiMap
 - Using a hashtable with separate chaining in which (key,  value) pairs are stored. If a key has multiple values, it appears in multiple pairs.
