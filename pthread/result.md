Result 
===

## platform
- CPU: Intel(R) Xeon(R) Gold 6126 CPU @ 2.60GHz
- number of core: 4
- RAM: 16G
- cache size: 19712 KB

## Result
### version 1
- description: make gernerator thread local (consume more memory)
- result:
    - thread 1 100000000: 12.200s
    - thread 2 100000000:  6.172s (efficiency: 98.8%)
    - thread 4 100000000:  4.100s (efficiency: 74.4%)

### version 1.1
- description: use 2 global sum to seperate mutex overhead
- result:
    - thread 1 100000000: 12.086s
    - thread 2 100000000:  6.098s (efficiency: 99.1%)
    - thread 4 100000000:  3.140s (efficiency: 96.22%)
