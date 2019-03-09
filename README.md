# UnixV6

  This is code from the origianl Unix V6 package
  
  But only include usr/sys and  usr/source
  
  they are used to build kernel and tools
  
# After First Commit
  
  This project is used to learn how to create a new tool in Linux system.
  
  So __ALL__ Unix code will be __Modified__ to suit Linux compilers.
  
# 吐槽

  骚操作真多。不用结构体，直接把stat取出的数据导入到一个int型数组中，然后从数组中取下标来取原始，真牛逼。
  直接申请256字节内存来存放两个文件的stat，而不是申请两个结构体，用自己强行写的50这个数字来区分空间。
