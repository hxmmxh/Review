





```c
/*把存储区 str1 和存储区 str2 的前 n 个字节进行比较
 *如果返回值 < 0，则表示 str1 小于 str2。
 *如果返回值 > 0，则表示 str2 小于 str1。
 *如果返回值 = 0，则表示 str1 等于 str2*/
int memcmp(const void *str1, const void *str2, size_t n));
```




## memmove 和 memcpy的区别

```c
#include <string.h>
void *memcpy(void *dst, const void *src, size_t count);
void *memmove(void *dst, const void *src, size_t count); 
```
- 作用都是拷贝一定长度的内存的内容
- 当内存发生局部重叠的时候，memmove保证拷贝的结果是正确的，memcpy不保证拷贝的结果的正确
- memmove的处理措施：
  - 当源内存的首地址等于目标内存的首地址时，不进行任何拷贝
  - 当源内存的首地址大于目标内存的首地址时，实行正向拷贝
  - 当源内存的首地址小于目标内存的首地址时，实行反向拷贝

```c
void *memcpy(void *dest, const void *src, size_t n)
{
    char *d = (char *)dest;
    const char *s = (const char *)src;
    while (n -–)
        *d++ = *s++;
    return dest;
}

void *memmove(void *dest, const void *src, size_t n)
{
    char *d = (char *)dest;
    const char *s = (const char *)src;

    if (s > d)
    {
        // start at beginning of s
        while (n--)
            *d++ = *s++;
    }
    else if (s < d)
    {
        // start at end of s
        d = d + n - 1;
        s = s + n - 1;

        while (n--)
            *d-- = *s--;
    }
    return dest;
}
```

